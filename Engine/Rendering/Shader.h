#pragma once
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
class Shader {
public:
  Shader(std::string FPath, std::string VPath);
  ~Shader();
  void Init();
  void use();
  unsigned int ID;
private:
  void CompileShader(unsigned int *shdrID, const char *Source, int SXType);

private:
  std::string _fragpath, _vertpath;
  char *_fragsource;
  char *_vertsource;
  unsigned int VertShdr, FragShdr;
};
