#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>

#include "EventManager.h"
using namespace glm;
using namespace std;

class Engine {
  
  private:
    GLFWwindow* window;
    int width, height, frameRate;
    string title;
    bool running;

    static void callback(Event evt);

  public:
    Engine(int _width, int _height, int _frameRate, string _title);
    void start();
    virtual void update(double delta) = 0;
};

#endif
