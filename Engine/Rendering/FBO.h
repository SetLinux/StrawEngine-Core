#include <GL/glew.h>

class FBO{
public:
    void CreateFBO();
    void BindFBO();
    void UnBindFBO();
    unsigned int renderedTexture;
private:
unsigned int FBOID;

};