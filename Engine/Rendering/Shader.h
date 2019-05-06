#pragma once
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../Math/Math.h"
#include <type_traits>
class Renderer;
class Shader {
public:
  Shader(const std::string& FPath, const std::string& VPath);
  ~Shader();
  void Init();
  void use();
  unsigned int ID;
  //TODO : to be implemented
  unsigned int getuniformloc(const std::string& uniformname){
    return glGetUniformLocation(ID,uniformname.c_str());
  };
  void SetFloatUniform(const float value,const unsigned int loc){
    glUniform1f(loc,value);
  };
  void SetVectorUniform(const X_Vector &vec,const unsigned int location){
    glUniform3f(location,vec.x,vec.y,vec.z);
  };

private:
  void CompileShader(unsigned int *shdrID, const char* Source, int SXType); 

private:
  
  std::string _fragpath, _vertpath;
  char *_fragsource;
  char *_vertsource;
  unsigned int VertShdr, FragShdr;
  
};
