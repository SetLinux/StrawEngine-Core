#pragma once
#include "../Addons/Physics.h"
#include "../Addons/Sprite.h"
#include "../Game/Entity.h"
#include "../Physics/PhysicsSystem.h"
#include "../Rendering/FBO.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/Shader.h"
#include "../GUI/GUISystem.h"
#include <deque>
#include <map>
#include <memory>
#include <vector>
#include <list>
#include <set>
class Window;
struct ShaderBatch {
public:
  ShaderBatch(){
    mySprites.reserve(200000);
  }
  Shader* shdr;
  std::vector<Sprite *> mySprites;
};

enum SortOrder { BackOrder, FrontOrder };
class Game {
public:
  typedef Entity *EntityHandler;
  typedef std::shared_ptr<Texture> TextureHandler;
  Game();
  ~Game();

  virtual void Start();
  virtual void Update(float dt);
  virtual void FixedUpdate(float dt);
  virtual void OnGUI();
  void InnerInit();
  void InnerUpdate(float dt, float alpha);
  void InnerFixedUpdate(float dt);
  void InnerRender(float dt,float alpha);
  // Makes texture if not loaded before if loaded before returns a reference to it
  Entity *TesterBaby(int a);
  TextureHandler defTexture;
  Window *m_Window;
  EntityHandler MakeSprite(X_Vector, X_Vector);
  EntityHandler MakeSprite(X_Vector, X_Vector, bool);
  EntityHandler MakeSprite(X_Vector, X_Vector, ShaderBatch *batch);
  void DeleteEntitiy(EntityHandler e);
  TextureHandler GetTexture(std::string path);
  std::vector<std::function<void()>> FixedPhysicsQueue;
  std::vector<std::function<void()>> UpdateQueue;
  void AddToPhysicsQueue(std::function<void()> input);
  void AddToUpdateQueue(std::function<void()> input);
  int IDCoutner = 0;
 protected:
  Shader *shdr;
  std::vector<ShaderBatch *> shdrBatches;
  Shader *screenShdr;
  FBO fbo;
  Renderer renderer;  
  ShaderBatch *MakeShaderBatch(Shader* shdr, SortOrder ordr);
  std::deque<Entity *> m_Entities;
private:
  EntityHandler InnerMakeSprite(X_Vector,X_Vector);
  unsigned int currentBoundShader = 0;
  unsigned int quadVAO, quadVBO;
  std::unordered_map<std::string, TextureHandler> m_TexturesList;
  ShaderBatch defaultBatch;
  float teset;
  
};