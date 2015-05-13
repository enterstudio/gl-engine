#ifndef ENTITY_H
#define ENTITY_H
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include "VertexData.h"
#include "GL/glew.h"

class Entity {
  protected:
    VertexData* data, *colourData;
    GLuint* shader;
    double x, y, z;
    double rotation;
    double angle;

  private:
    glm::mat4 model;
    glm::vec3 rotationAxes;
    
  public:
    Entity();
    ~Entity();
    virtual void update(double delta) = 0;
    VertexData* getData();
    VertexData* getColour();
    void setShader(GLuint* shader);
    GLuint* getShader();

    void move(double,double,double);
    void rotate(float);
    glm::mat4 getModel();

};

#endif
