#include "Sprite.h"
#include "../Game/Entity.h"

Sprite::Sprite() {}
void Sprite::OnCreate() {
  vertices[0].position = X_Vector(-0.5f, 0.5f);
  vertices[0].TexCoord = X_Vector(0.0f, 1.0f);
  vertices[1].position = X_Vector(0.5f, 0.5f);
  vertices[1].TexCoord = X_Vector(1.0f, 1.0f);
  vertices[2].position = X_Vector(0.5f, -0.5f);
  vertices[2].TexCoord = X_Vector(1.0f, 0.0f);
  vertices[3].position = X_Vector(-0.5f, -0.5f);
  vertices[3].TexCoord = X_Vector(0.0f, 0.0f);
  BackupVertices[0].position = X_Vector(-0.5f, 0.5f);
  BackupVertices[0].TexCoord = X_Vector(0.0f, 1.0f);
  BackupVertices[1].position = X_Vector(0.5f, 0.5f);
  BackupVertices[1].TexCoord = X_Vector(1.0f, 1.0f);
  BackupVertices[2].position = X_Vector(0.5f, -0.5f);
  BackupVertices[2].TexCoord = X_Vector(1.0f, 0.0f);
  BackupVertices[3].position = X_Vector(-0.5f, -0.5f);
  BackupVertices[3].TexCoord = X_Vector(0.0f, 0.0f);
}

void Sprite::OnUpdate(float dt, float alpha) {
  if (!Static)
    ApplyTransformation();
}
void Sprite::OnFixedUpdate(float dt) {}
Sprite::~Sprite() {}

void Sprite::ApplyTransformation() {

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(
      model, X_Vector::ToVec<glm::vec3>(X_Vector(std::round(owner->position.x),
                                                 std::round(owner->position.y),
                                                 owner->position.z),
                                        true));
  // model = glm::translate(model,
  // X_Vector::ToVec<glm::vec3>(owner->position,true));
  model = glm::rotate(model,glm::radians(owner->Rotation),glm::vec3(0.0,0.0,1.0f));
  model = glm::scale(model, X_Vector::ToVec<glm::vec3>(owner->scale));

  MVP = Camera::main.Projection * Camera::main.getViewMatrix() * model;
  for (int i = 0; i < 4; i++) {
    intern =
        glm::vec4(BackupVertices[i].position.x, BackupVertices[i].position.y,
                  BackupVertices[i].position.z, 1.0f);

    res = MVP * intern;
    vertices[i].position = X_Vector::fromVec<glm::vec4>(res, true);
  }
}
void Sprite::SetTexBound(float x,float y,float w,float h){
  float texX = x / tex->Width;
  float texY = 1 - (y / tex->Height);
  float texW = w / tex->Width;
  
  float texH = h / tex->Height;
  vertices[0].TexCoord = X_Vector(texX,texY);
  vertices[1].TexCoord = X_Vector(texX + texW,texY);
  vertices[2].TexCoord = X_Vector(texX + texW, texY - texH);
  vertices[3].TexCoord = X_Vector(texX  , texY - texH);
}
