#pragma once

#include <GL/glew.h>
#include <string>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Texture{
public:
//Acting Like A Getter
inline unsigned int GetID(){return ID;};
public:
    Texture(std::string path);
    inline Texture(int ID){ this->ID = ID;};
    void Init();
    void Use();
    float Width,Height;
private:
    unsigned int ID;
    std::string _path;
};
