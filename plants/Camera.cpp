#include "Camera.h"
#include <iostream>

// Constructor
Camera::Camera(EventManager* evtmgr){
  this->evtmgr = evtmgr;
}

// Initialise camera
void Camera::init(int x, int y, int z){
  evtmgr->enableCallback(new Callback<Camera>(this, EVT_MOUSESCROLL, &Camera::scrollCallback));
  evtmgr->enableCallback(new Callback<Camera>(this, EVT_KEY, &Camera::keyCallback));
  eyeX = x;
  eyeY = y;
  eyeZ = z;
  centreX = centreY = centreZ = 0;
  moveVelX = moveVelY = moveVelZ = 0;
  moveNorth = moveEast = moveSouth = moveWest = false;
}

glm::mat4 Camera::view(){
  return glm::lookAt(
    glm::vec3(eyeX, eyeY, eyeZ),
    glm::vec3(centreX, centreY, centreZ),
    glm::vec3(0, 1, 0)
    );
}

void Camera::scrollCallback(Event evt){
  eyeZ += evt.data[1];
}

void Camera::keyCallback(Event evt){
  int key = evt.data[0];
  int scancode = evt.data[1];
  int action = evt.data[2];
  int mods = evt.data[3];
  
  switch(action){
    case GLFW_REPEAT:
    case GLFW_PRESS:
      switch(key){
        case GLFW_KEY_A: moveWest = true; break;
        case GLFW_KEY_D: moveEast= true; break;
        case GLFW_KEY_W: moveNorth = true; break;
        case GLFW_KEY_S: moveSouth = true; break;
      }
    break;
    
    case GLFW_RELEASE: 
      switch(key){
        case GLFW_KEY_A: moveWest = false; break;
        case GLFW_KEY_D: moveEast= false; break;
        case GLFW_KEY_W: moveNorth = false; break;
        case GLFW_KEY_S: moveSouth = false; break;
      }
    break;
  }       
}

// Update camera
void Camera::update(double delta) {
  double factor = (double) 1/32;
  double max = factor*8;
  double slow = factor/8;

  // Increase velocity
  if(moveNorth) 
    moveVelY += factor;
  if(moveEast)
    moveVelX += factor;
  if(moveSouth)
    moveVelY -= factor;
  if(moveWest)
    moveVelX -= factor;

  // Reduce velocity
  if(!moveNorth)
    if(moveVelY > 0) moveVelY -= slow;

  if(!moveEast)
    if(moveVelX > 0) moveVelX -= slow;

  if(!moveSouth)
    if(moveVelY < 0) moveVelY += slow;

  if(!moveWest)
    if(moveVelX < 0) moveVelX += slow;

  // Ensure velocity doesn't exceed bounds
  if(moveVelX > max) 
    moveVelX = max;
  else if(moveVelX < -max)
    moveVelX = -max;

  if(moveVelY > max) 
    moveVelY = max;
  else if(moveVelY < -max)
    moveVelY = -max;

  // Update camera position
  centreX += moveVelX;
  centreY += moveVelY;  
}


