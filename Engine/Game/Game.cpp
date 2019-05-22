#include "Game.h"
#include "../Rendering/Animation.h"
#include "../Addons/Animator.h"
#include "../Addons/Script.h"
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
  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    } else {
      for (int f = 0; f < shdrBatches[i]->mySprites.size(); f++) {
        if (shdrBatches[i]->mySprites[f]) {
          renderer.Begin();
          for (int y = 0; y < shdrBatches[i]->mySprites[f]->m_Addons.size();
               y++) {
            shdrBatches[i]->mySprites[f]->m_Addons[y]->OnUpdate(dt, alpha);
          }
          if (shdrBatches[i]->mySprites[f]->HasAddon<Sprite>())
            renderer.Submit(
                (shdrBatches[i]->mySprites[f]->GetAddon<Sprite>().get()));
          renderer.End();
        }
      }
    }
  }

  GUI::BeginRender(dt);
  OnGUI();
  GUI::EndRender();
}

void Game::InnerFixedUpdate(float dt) {
  PhysicsSystem::UpdateWorld(dt);

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


//--------------------The notorious Lua Binding Function ------------------------
void Game::SetUpLuaBinding() {

  //----------------------- Rendering Architcture Binding --------------------------------
  ScriptingSystem::LuaRegisterClass<Texture>("Texture", sol::constructors<>(),
                                             "init", &Texture::Init);
  ScriptingSystem::luastate["GetTexture"] = [this](const std::string &path) {
					      return this->GetTexture(path);
					    };
   
  
  ScriptingSystem::LuaRegisterClass<Animation>(
      "Animation", sol::constructors<Animation()>(), "createAnimation",
      &Animation::MakeAnimation, "speed", &Animation::speed);

  ScriptingSystem::luastate["camera"] = ScriptingSystem::luastate.create_table();
  ScriptingSystem::luastate["camera"]["screentoworld"] = [&](const X_Vector& in) {return Camera::main.ScreenToWorld(in);};
  //------------------------The Humongus GIGANTIC Vector Shit :)
  //--------------------
  ScriptingSystem::LuaRegisterClass<X_Vector>(
      "X_Vector",
      sol::constructors<X_Vector(float, float),
                        X_Vector(float, float, float)>(),
      "x", &X_Vector::x, "y", &X_Vector::y, "normalize", &X_Vector::Normalize);

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
  ScriptingSystem::AddMember("X_Vector",sol::meta_method::equal_to,[](const X_Vector& self,const X_Vector& other){return (other==self);});
  ScriptingSystem::luastate["math"] = ScriptingSystem::luastate.create_table();
  ScriptingSystem::luastate["math"]["dot"] = [](X_Vector& self,X_Vector& other) {return X_Vector::Dot(self,other);};
  ScriptingSystem::luastate["math"]["distance"] = [](X_Vector& self,X_Vector& other) {return X_Vector::Distance(self,other);};
  //-------------------Internal Addons Registeration -----------------------------

  ScriptingSystem::LuaRegisterClass<Sprite>(
      "Sprite", sol::constructors<>(), "Texture", &Sprite::tex, "setTexCoords",
      &Sprite::SetTexBound);

  ScriptingSystem::LuaRegisterClass<Physics>(
      "Physics", sol::constructors<>(), "gravity",
      sol::property(&Physics::GetGravityScale, &Physics::SetGravity),
      "position",
      sol::property(&Physics::GetBodyPosition, &Physics::SetBodyPosition),
      "velocity", sol::property(&Physics::getVeloctiy, &Physics::SetVeloctiy),
      "rotation", sol::property(&Physics::GetRotation, &Physics::SetRotation),
      "density",
      sol::property(
          [](Physics &self) {
            return self.getBody()->GetFixtureList()->GetDensity();
          },
          [](Physics &self, float a) {
            self.getBody()->GetFixtureList()->SetDensity(a);
            self.getBody()->ResetMassData();
          }),
      "setBody",
      [](Physics &self, int type) {
        self.getBody()->SetType((b2BodyType)type);
      },
      "linearDamping", sol::property([](Physics& self) {return self.getBody()->GetLinearDamping();}, [](Physics& self,float in) {self.getBody()->SetLinearDamping(in);}));
  ScriptingSystem::LuaRegisterClass<Animator>("Animator",sol::constructors<>(),
					      "setAnimation",&Animator::SetAnim,
					      "setSpriteDimensions",&Animator::SetSpriteDimension);

  ScriptingSystem::LuaRegisterClass<Script>("Script",sol::constructors<>(),
					    "returntable",&Script::tbl);
 
  
  //--------------------------Input global functions -------------------------------
  ScriptingSystem::luastate["window"] = ScriptingSystem::luastate.create_table();
  ScriptingSystem::luastate["window"]["getKey"] = [this](int key) {
    return glfwGetKey(this->m_Window->m_window, key) == GLFW_PRESS;
  };
  ScriptingSystem::luastate["window"]["mousexpos"] = [&]() {return m_Window->mousexpos;};
  ScriptingSystem::luastate["window"]["mouseypos"] = [&]() {return m_Window->mouseypos;};
  //--------------------------- Physics Body Types Registeration --------------------
  ScriptingSystem::luastate["bodyType"] =
      ScriptingSystem::luastate.create_table();
  ScriptingSystem::luastate["bodyType"]["staticBody"] =
      b2BodyType::b2_staticBody;
  ScriptingSystem::luastate["bodyType"]["dynamicBody"] =
      b2BodyType::b2_dynamicBody;
  ScriptingSystem::luastate["bodyType"]["kinematicBody"] =
      b2BodyType::b2_kinematicBody;

  //----------------------------- Physics Global Function ------------------------
  ScriptingSystem::luastate["setContactListener"] = [&](sol::function func) {
						      PhysicsSystem::MakeListener([&,func](Entity *A, Entity *B, b2Contact *conc) {
      b2WorldManifold worldManifold;
      conc->GetWorldManifold(&worldManifold);
      X_Vector normal = X_Vector::fromVec(worldManifold.normal);
      func(A, B, normal);
    });
  };

  ScriptingSystem::luastate["RayCast"] =
      [](const X_Vector &pointa, const X_Vector &pointb, sol::function func) {
        PhysicsSystem::RayCast(pointa, pointb,
                               [func](Entity *A, X_Vector B) { func(A, B); });
      };
  //----------------Entity Creation----------------------------------------------
  ScriptingSystem::luastate["createEntity"] = sol::overload(
      [&](const X_Vector &pos, const X_Vector &scale) {
        return this->MakeSprite(pos, scale, false);
      },
      [&](const X_Vector &pos, const X_Vector &scale, bool physics) {
        return this->MakeSprite(pos, scale, physics);
      },
      [&](const X_Vector &pos) { return MakeEntity(pos); });

  //----------------Entity Registeration---------------------------------------------
  ScriptingSystem::LuaRegisterClass<Entity>(
      "Entity", sol::constructors<>(), "position", &Entity::position, "scale",
      &Entity::scale, "rotation", &Entity::Rotation,"tag",&Entity::tagname);
  ScriptingSystem::AddMember("Entity", "getSpriteAddon", [](Entity &self) {
    return self.GetAddon<Sprite>();
  });
  ScriptingSystem::AddMember("Entity", "getPhysicsAddon", [](Entity &self) {
    return self.GetAddon<Physics>();
  });
  ScriptingSystem::AddMember("Entity", "getAnimatorAddon", [](Entity &self) {
    return self.GetAddon<Animator>();
  });
  ScriptingSystem::AddMember("Entity", "getScriptAddon", [](Entity &self) {
    return self.GetAddon<Script>();
  });
  
  ScriptingSystem::AddMember("Entity", "createPhysicsAddon", [](Entity &self) {
    return self.AddAddon<Physics>();
  });
  ScriptingSystem::AddMember("Entity", "createSpriteAddon", [](Entity &self) {
    return self.AddAddon<Sprite>();
  });
  ScriptingSystem::AddMember("Entity", "createAnimatorAddon", [](Entity &self) {
    return self.AddAddon<Animator>();
  });
  ScriptingSystem::AddMember("Entity","createScriptAddon",[](Entity& self,const std::string& scriptPath){
    return self.AddAddon<Script>(scriptPath);
  });
}
