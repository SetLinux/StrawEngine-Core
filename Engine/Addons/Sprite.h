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
  volatile Vertex vertices[4];
  std::shared_ptr<Texture> tex;
  // Setting Position and Stuff :D
  void ApplyTransformation();
  bool Static = false;
  glm::mat4 MVP;
  bool Visible = true;
  void SetTexBound(float x,float y,float width, float height);
  static void LuaBinding();
private:
  glm::vec4 res;
  volatile  Vertex BackupVertices[4];
};
