#ifndef TESTENTITY_H
#define TESTENTITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "Entity.h"

class TestEntity : public Entity {
  public:
    TestEntity();
    void update(double delta);

    std::vector<GLuint*>* data = new std::vector<GLuint*>*{
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
    };
};

#endif
