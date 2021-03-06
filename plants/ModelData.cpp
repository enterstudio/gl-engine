#include "ModelData.h"
#include <common/vboindexer.hpp>

ModelData::ModelData(){
  vertices = new VertexData<glm::vec3>(GL_ARRAY_BUFFER);
  uvs = new VertexData<glm::vec2>(GL_ARRAY_BUFFER);
  normals = new VertexData<glm::vec3>(GL_ARRAY_BUFFER);
  colours = new VertexData<glm::vec3>(GL_ARRAY_BUFFER);
  indices = new VertexData<unsigned int>(GL_ELEMENT_ARRAY_BUFFER);
  is_current = false;
}

void ModelData::buildVBOIndex(){
  std::vector<glm::vec3>* indexed_vertices = new std::vector<glm::vec3>();
  std::vector<glm::vec2>* indexed_uvs = new std::vector<glm::vec2>();
  std::vector<glm::vec3>* indexed_normals = new std::vector<glm::vec3>();
  indices->setData(new std::vector<unsigned int>());
  
  indexVBO(*vertices->getData(), 
          *uvs->getData(), 
          *normals->getData(), 
          *indices->getData(), 
          *indexed_vertices, 
          *indexed_uvs, 
          *indexed_normals);

  vertices->setData(indexed_vertices);
  normals->setData(indexed_normals);
  uvs->setData(indexed_uvs);
  
}

void ModelData::setTexturePath(std::string str){
  texPath = str;
}

std::string ModelData::getTexturePath(){
  return texPath;
}

GLuint ModelData::getTexture(){
  return textureID;
}

void ModelData::setTextureID(GLuint id){
  textureID = id;
}

VertexData<glm::vec3>* ModelData::getVertices(){
  return vertices;
}

VertexData<glm::vec2>* ModelData::getUVs(){
  return uvs;
}

VertexData<glm::vec3>* ModelData::getNormals(){
  return normals;
}

VertexData<glm::vec3>* ModelData::getColours(){
  return colours;
}

VertexData<unsigned int>* ModelData::getIndices(){
  return indices;
}

void ModelData::refreshBuffers(){

  indices->refreshBuffer(); 
  vertices->refreshBuffer();
  normals->refreshBuffer();
  uvs->refreshBuffer();
}

tbb::atomic<bool> ModelData::isCurrent(){
  return is_current;
}

void ModelData::makeCurrent(){
  is_current = true;
}
