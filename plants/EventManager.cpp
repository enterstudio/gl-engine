#include "EventManager.h"
EventManager* EventManager::instance = 0;


#pragma warning( push )
#pragma warning( disable : 4101)

EventManager::EventManager(GLFWwindow* w) {
  window = w;
  instance = this;
  glfwSetKeyCallback(w, &EventManager::keyCallback);
  glfwSetScrollCallback(w, &EventManager::mouseScrollCallback);
  glfwSetMouseButtonCallback(w, &EventManager::mouseButtonCallback);
  glfwSetCursorPosCallback(w, &EventManager::mouseMoveCallback);

  for(int i = 0; i < NUM_EVTS; i++)
    callbacks.insert(
        std::pair< int,list<EvtCallback>* >(i,new list<EvtCallback>)
        );
}

#pragma warning( pop ) 

EventManager* EventManager::getInstance(){
  return instance;
}

int EventManager::enableCallback(int type, EvtCallback callback){
  if(callbacks.count(type) > 0){
    callbacks[type]->push_back(callback);
  }
}

int EventManager::disableCallback(int type, EvtCallback callback){
  if(callbacks.count(type) > 0){
    list<EvtCallback>* v = callbacks[type];
    v->remove(callback);
  }
}
void EventManager::keyCallback(GLFWwindow* w,int key,int scancode,int action,int mods){
  for(auto it = instance->callbacks[EVT_KEY]->begin(); it != instance->callbacks[EVT_KEY]->end(); ++it){
    Event evt = {key,scancode,action,mods};
    (*it)(&evt);
  } 
}
void EventManager::mouseMoveCallback(GLFWwindow* w,double xpos,double ypos){
  for(auto it = instance->callbacks[EVT_KEY]->begin(); it != instance->callbacks[EVT_KEY]->end(); ++it){
    Event evt = {xpos,ypos,0,0};
    (*it)(&evt);
  }
}
void EventManager::mouseButtonCallback(GLFWwindow* w,int button,int action,int mods){
  for(auto it = instance->callbacks[EVT_KEY]->begin(); it != instance->callbacks[EVT_KEY]->end(); ++it){
    Event evt = {button,action,mods,0};
    (*it)(&evt);
  }
}
void EventManager::mouseScrollCallback(GLFWwindow* w,double xoff,double yoff){
  for(auto it = instance->callbacks[EVT_KEY]->begin(); it != instance->callbacks[EVT_KEY]->end(); ++it){
    Event evt = {xoff, yoff, 0,0};
    (*it)(&evt);
  }
}

