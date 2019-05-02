#include "FBO.h"
#include <iostream>
void FBO::CreateFBO(){
    glGenFramebuffers(1,&FBOID);
    
    glBindFramebuffer(GL_FRAMEBUFFER,FBOID);
    
    glGenTextures(1,&renderedTexture);
    glBindTexture(GL_TEXTURE_2D,renderedTexture);
    
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,1024,720,0,GL_RGB,GL_UNSIGNED_BYTE,0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GLuint rboDepthStencil;
    glGenRenderbuffers(1, &rboDepthStencil);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepthStencil);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,1024,720);

    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,renderedTexture,0);
       if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    glFramebufferRenderbuffer(
    GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepthStencil
);

    glBindFramebuffer(GL_FRAMEBUFFER,0);
}
void FBO::BindFBO(){
    glBindFramebuffer(GL_FRAMEBUFFER,FBOID);
}
