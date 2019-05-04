#pragma once
#include "../Game/Addon.h"
#include "../Game/Camera.h"
#include "../Math/Math.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Texture.h"
#include <Box2D/Box2D.h>
class Sprite : public Addon {
public:
  Sprite();
  ~Sprite();
  int ID = 0;

public:
  // Addon Implementations
  AddonBody(AddonType::SpriteAddon);

public:
  Vertex vertices[4];
  Texture *tex;
  // Setting Position and Stuff :D
  void ApplyTransformation();
  Shader *shdr;
  bool Static = false;
  glm::mat4 MVP;
  bool Visible = true;
  void SetTexBound(float x,float y,float width, float height);
  void SetVerticesData(void *data){
    for(int i =0; i < 4; i++){
      vertices[i].data = data;
      BackupVertices[i].data = data;
    }
  };

private:
  glm::vec4 res, intern;
  Vertex BackupVertices[4];
};