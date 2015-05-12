
#include "RunningState.h"
#include "Scene.h"
#include "TestEntity.h"
#include "Entity.h"
#include "Renderer.h"
#include "GameState.h"

// Constructor
RunningState::RunningState(EventManager* evtmgr, Renderer* renderer) {
  this->evtmgr = evtmgr;
  this->renderer = renderer;
}

void RunningState::init(){
  entities = new std::vector<Entity*>();

  for(int i = 11; i < 400; i++){
    Entity* e = new TestEntity();
    e->move((double)(677%i) , (double)(501%i), 0.0f);
    entities->push_back(e);
  }
  renderer->setEntities(entities);
}

// Update game
GameState* RunningState::update(double delta) {
 
  // Update current scene
  if(scene != 0)
    scene->update(delta);

  // Update camera
  renderer->getCamera()->update(delta);

  // Update entities
  for(auto e = entities->begin(); e != entities->end(); ++e){
   (*e)->update(delta);
  }

  return this;
}

// Free resources
void RunningState::dispose() {
  scene->dispose();
}
