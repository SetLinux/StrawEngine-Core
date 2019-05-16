#include "Game.h"
#include <thread>

Game::Game() {
  shdr = new Shader("/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Engine/"
                    "Shaders/base.frag",
                    "/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Engine/"
                    "Shaders/base.vert");
}

Game::~Game() {}

std::shared_ptr<Entity> Game::MakeSprite(X_Vector pos, X_Vector scale) {
  EntityHandler ent = InnerMakeSprite(pos, scale);
  ent->AddAddon<Physics>();
  defaultBatch.mySprites.push_back(ent);
  std::weak_ptr<Entity> weaker = ent;
  return weaker.lock();
}
void Game::AddToPhysicsQueue(std::function<void()> input) {
  FixedPhysicsQueue.push_back(input);
}
void Game::AddToUpdateQueue(std::function<void()> input) {
  UpdateQueue.push_back(input);
}
std::shared_ptr<Entity> Game::MakeSprite(X_Vector pos, X_Vector scale,
                                         bool ePhysics) {
  EntityHandler ent = InnerMakeSprite(pos, scale);
  if (ePhysics)
    ent->AddAddon<Physics>();
  defaultBatch.mySprites.push_back(ent);
  std::weak_ptr<Entity> weaker = ent;
  return weaker.lock();
}
std::shared_ptr<Entity> Game::MakeEntity(X_Vector position) {
  IDCoutner++;
  std::shared_ptr<Entity> ent = std::make_shared<Entity>();
  ent->ID = IDCoutner;
  ent->position = position;
  defaultBatch.mySprites.push_back(ent);
  return ent;
}
std::shared_ptr<Entity> Game::MakeSprite(X_Vector pos, X_Vector scale,
                                         ShaderBatch *batch) {
  EntityHandler ent = InnerMakeSprite(pos, scale);
  batch->mySprites.push_back(ent);
  std::weak_ptr<Entity> weaker = ent;
  return weaker.lock();
}

ShaderBatch *Game::MakeShaderBatch(Shader *shdr, SortOrder ordr) {
  ShaderBatch *sb = new ShaderBatch();

  sb->shdr = (Shader *)shdr;
  if (ordr == SortOrder::FrontOrder) {
    shdrBatches.push_back(sb);
  } else {
    shdrBatches.insert(shdrBatches.begin(), sb);
  }
  return sb;
}
void Game::DeleteEntity(std::shared_ptr<Entity> e) {
  bool found = false;
  for (int i = 0; i < shdrBatches.size() && !found; i++) {
    for (int f = 0; f < shdrBatches[i]->mySprites.size(); f++) {
      if (shdrBatches[i]->mySprites[f]->ID == e->ID) {
        shdrBatches[i]->mySprites.erase(shdrBatches[i]->mySprites.begin() + f);
        found = true;
        e.reset();
        std::cout << e.use_count() << std::endl;
        break;
      }
    }
  }
}

void Game::Start() {}

void Game::Update(float dt) {}

void Game::FixedUpdate(float dt) {}

void Game::OnGUI() {}

void Game::InnerInit() {
  PhysicsSystem::Init();
  ScriptingSystem::Init();
  SetUpLuaBinding();
  GUI::Init(this, "/home/mohamedmedhat/Desktop/StrawEngine/GUI");

  GUI::LoadScheme("WindowsLook.scheme");
  GUI::SetFont("DejaVuSans-10");
  // button->setText("BABY");
  // button->subscribeEvent(CEGUI::PushButton::EventClicked,
  //                     CEGUI::Event::Subscriber([](const CEGUI::EventArgs& e)
  //                     {std::cout << "CLICKDE" << std::endl; return true;}));
  renderer.Init();
  shdr->Init();
  shdrBatches.push_back(&defaultBatch);
  defaultBatch.shdr = shdr;
  shdr->use();
  Start();
}
void Game::InnerUpdate(float dt, float alpha) {
  Update(dt);

  glEnable(GL_MULTISAMPLE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 1, 1, 1);

  for (int i = 0; i < shdrBatches.size(); i++) {
    glUseProgram(shdrBatches[i]->shdr->ID);
    if (shdrBatches[i]->batch) {
      renderer.Begin();
      for (int f = 0; f < shdrBatches[i]->mySprites.size(); f++) {
        if (shdrBatches[i]->mySprites[f]) {
          for (int y = 0; y < shdrBatches[i]->mySprites[f]->m_Addons.size();
               y++) {
            shdrBatches[i]->mySprites[f]->m_Addons[y]->OnUpdate(dt, alpha);
          }
          if (shdrBatches[i]->mySprites[f])
            if (shdrBatches[i]->mySprites[f]->HasAddon<Sprite>())
              renderer.Submit(
                  (shdrBatches[i]->mySprites[f]->GetAddon<Sprite>().get()));
        }
      }
      renderer.End();
    }
  }
  GUI::BeginRender(dt);
  OnGUI();
  GUI::EndRender();
}

void Game::InnerFixedUpdate(float dt) {
  FixedUpdate(dt);
  for (int i = 0; i < shdrBatches.size(); i++) {
    for (int f = 0; f < shdrBatches[i]->mySprites.size(); f++) {
      for (auto &it : shdrBatches[i]->mySprites[f]->m_Addons) {
        it->OnFixedUpdate(dt);
      }
    }
  }

  for (auto &it : FixedPhysicsQueue) {
    it();
  }
  FixedPhysicsQueue.clear();

  PhysicsSystem::UpdateWorld(dt);
}
std::shared_ptr<Texture> Game::GetTexture(std::string path) {
  if (m_TexturesList[path]) {
    return m_TexturesList[path];
  }
  std::shared_ptr<Texture> tex = std::make_shared<Texture>(path);
  m_TexturesList[path] = tex;
  tex->Init();
  LOG("[*] Loaded a Texture Succefully : " + path);
  return tex;
}
std::shared_ptr<Entity> Game::InnerMakeSprite(X_Vector pos, X_Vector scale) {
  IDCoutner++;
  std::shared_ptr<Entity> ent = std::make_shared<Entity>();
  ent->ID = IDCoutner;
  ent->position = pos;
  ent->scale = scale;
  ent->AddAddon<Sprite>();
  return ent;
}

bool Game::IsKeyDown(int key) {
  return glfwGetKey(m_Window->m_window, key) == GLFW_PRESS;
}
void Game::SetUpLuaBinding() {
  ScriptingSystem::LuaRegisterClass<X_Vector>(
      "X_Vector",
      sol::constructors<X_Vector(float, float),
                        X_Vector(float, float, float)>(),
      "x", &X_Vector::x, "y", &X_Vector::y);
  ScriptingSystem::LuaRegisterClass<Texture>("Texture", sol::constructors<>(),
                                             "init", &Texture::Init);
  ScriptingSystem::LuaRegisterClass<Sprite>(
      "Sprite", sol::constructors<>(), "Texture", &Sprite::tex, "setTexCoords",
      &Sprite::SetTexBound);
  ScriptingSystem::LuaRegisterClass<Physics>(
      "Physics", sol::constructors<>(), "gravity",
      sol::property(&Physics::GetGravityScale, &Physics::SetGravity),
      "position",
      sol::property(&Physics::GetBodyPosition, &Physics::SetBodyPosition),
      "veloctiy", sol::property(&Physics::getVeloctiy, &Physics::SetVeloctiy));

  ScriptingSystem::luastate["GetTexture"] = [this](const std::string &path) {
    return this->GetTexture(path);
  };

  ScriptingSystem::AddMember(
      "X_Vector", sol::meta_method::addition,
      sol::overload([](const X_Vector &self,
                       const X_Vector &other) { return self + other; },
                    [](const X_Vector &self, const float other) {
                      return self + other;
                    }));
  ScriptingSystem::AddMember(
      "X_Vector", sol::meta_method::subtraction,
      sol::overload([](const X_Vector &self,
                       const X_Vector &other) { return self - other; },
                    [](const X_Vector &self, const float other) {
                      return self - other;
                    }));
  ScriptingSystem::AddMember(
      "X_Vector", sol::meta_method::multiplication,
      sol::overload([](const X_Vector &self,
                       const X_Vector &other) { return self * other; },
                    [](const X_Vector &self, const float other) {
                      return self * other;
                    }));
  ScriptingSystem::AddMember(
      "X_Vector", sol::meta_method::division,
      sol::overload([](const X_Vector &self,
                       const X_Vector &other) { return self / other; },
                    [](const X_Vector &self, const float other) {
                      return self / other;
                    }));
  ScriptingSystem::luastate["getKey"] = [this](int key) {
    return glfwGetKey(this->m_Window->m_window, key) == GLFW_PRESS;
  };

  ScriptingSystem::luastate["createEntity"] =
      sol::overload([&](const X_Vector &pos, const X_Vector &scale) {
        this->MakeSprite(pos, scale, false);
      });

  ScriptingSystem::LuaRegisterClass<Entity>(
      "Entity", sol::constructors<>(), "position", &Entity::position, "scale",
      &Entity::scale, "rotation", &Entity::Rotation);
  ScriptingSystem::AddMember("Entity", "getSpriteAddon", [](Entity &self) {
    return self.GetAddon<Sprite>();
  });

  ScriptingSystem::AddMember("Entity", "getPhysicsAddon", [](Entity &self) {
    return self.GetAddon<Physics>();});
}
