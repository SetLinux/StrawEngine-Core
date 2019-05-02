#include "Texture.h"
#include "../Utils/stb_image.h"
Texture::Texture(std::string Path) : Width(0),Height(0){
    this->_path = Path;
}
void Texture::Init(){
    glGenTextures(1,&ID);
    
    glBindTexture(GL_TEXTURE_2D,ID);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height, nrChannels;    
    unsigned char *data = stbi_load(_path.c_str(), &width, &height, &nrChannels, 0);
    stbi_set_flip_vertically_on_load(true);  
    if (data)
    {
		if (nrChannels > 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		}
		glGenerateMipmap(GL_TEXTURE_2D);
    this->Width = width;
    this->Height = height;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
      
}
void Texture::Use(){
    glBindTexture(GL_TEXTURE_2D,ID);
}
