#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include "Entity.h"
#include <vector>

using namespace glm;
using namespace std;

class Renderer {
  private:
    vector<Entity*>* entities;
    int screenW, screenH;
    GLuint VertexArrayID;
    static Renderer instance;

  public:
    Renderer(int,int);
    void setEntities(vector<Entity*>* entities);
    void draw(); 
    static Renderer* getInstance();
    static void init(int width, int height);
};
#endif
