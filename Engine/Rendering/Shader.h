#pragma once
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
class Renderer;
class Shader {
public:
  Shader(std::string FPath, std::string VPath);
  ~Shader();
  void Init();
  void use();
  unsigned int ID;
  //TODO : to be implemented
  unsigned int getuniformloc(const std::string& uniformname){
    return glGetUniformLocation(ID,uniformname.c_str());
  };
  void SetFloatUniform(float value,unsigned int loc){
    glUniform1f(loc,value);
  };
  
private:
  void CompileShader(unsigned int *shdrID, const char *Source, int SXType); 

private:
  
  std::string _fragpath, _vertpath;
  char *_fragsource;
  char *_vertsource;
  unsigned int VertShdr, FragShdr;
  
};
