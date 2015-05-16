#include "Renderer.h"
#include "AssetManager.h"

// Constructor
Renderer::Renderer(GLFWwindow* w,EventManager* evtmgr, int scrW, int scrH){
  std::cout << "Renderer init\n";
  this->screenW = scrW;
  this->screenH = scrH;
  this->window = w;  
  camera = new Camera(evtmgr);
  camera->init(0,0,64);

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  // Setup VAO
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID); 
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  // Setup perspective
  projection = glm::perspective(20.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
  view = glm::lookAt(
    glm::vec3(0,0,16), 
    glm::vec3(0,0,0), 
    glm::vec3(0,1,0)
    );

  model = glm::mat4(1.0f);
  mvp = projection*view*model; 
  entities = new vector<Entity*>();

  } 
// Set entity render list

// Add entity
void Renderer::addEntity(Entity* entity) {
  entities->push_back(entity);
}

// Render entities
void Renderer::draw(){
  // Clear the screen
  if(entities == 0){
    std::cout << "Entities not initialised";
    return;
  }
  if(entities->size() == 0){
    return;
  }
  GLuint programID = *AssetManager::assets->DEFAULT_SHADER;

  glUseProgram(programID);
  GLuint LightID, TextureID;
  if(programID){
    std::cout << "using program id" << programID << "\n";
    LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    TextureID  = glGetUniformLocation(programID, "myTextureSampler");
  }
  // Enable drawing of vertex arrays
  for(auto e = entities->begin(); e != entities->end(); e++){
    std::cout << "starting entity loop\n";
    mvp = projection * camera->view() * (*e)->getPos();
 
    GLuint texture = (*e)->getModel()->getTexture();

    glUseProgram(programID);
    GLuint mvpMatID = glGetUniformLocation(programID, "MVP");
    GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
    GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
    
    glUniformMatrix4fv(mvpMatID, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &(*e)->getPos()[0][0]);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &camera->view()[0][0]);
     
    glm::vec3 lightPos = glm::vec3(2,0,4);
    glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);   
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(TextureID, 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, *(*e)->getModel()->getVertices()->getBuffer());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, *(*e)->getModel()->getUVs()->getBuffer());
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);    
    
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, *(*e)->getModel()->getNormals()->getBuffer());
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *(*e)->getModel()->getIndices()->getBuffer());

    glDrawElements(GL_TRIANGLES, (*e)->getModel()->getIndices()->numVerts(), GL_UNSIGNED_SHORT, (void*)0); 
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    std::cout << "\n" << (*e)->getModel()->getVertices()->numVerts() << " " <<
               (*e)->getModel()->getUVs()->numVerts() << " " <<
               (*e)->getModel()->getNormals()->numVerts() << " " <<
               (*e)->getModel()->getIndices()->numVerts();
  }
}

// Return camera instance
Camera* Renderer::getCamera() {
  return camera;
}
