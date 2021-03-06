#ifndef GLCACHE_H 
#define GLCACHE_H

#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <common/shader.hpp>
#include <map>
#include <string>


/**
 * The GLCache class caches assets or values of OpenGL calls so that they can be easily accessed with minimal overhead
 */
class GLCache {
  private:
    std::map<std::string, GLuint> texMap;
    std::map<GLuint,std::map<std::string, GLuint>> uniformMap;
  public:
    GLCache();
    ~GLCache();
    
    void loadAssets();
    GLuint getTextureID(std::string);
    GLuint getUniformLocation(GLuint,std::string);
    GLuint DEFAULT_SHADER = 0;
};

#endif
