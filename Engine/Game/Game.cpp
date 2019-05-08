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
  defaultBatch.mySprites.push_back(ent->GetAddon<Sprite>());
  std::weak_ptr<Entity> weaker = ent;
  return weaker.lock();
}
void Game::AddToPhysicsQueue(std::function<void()> input) {
  FixedPhysicsQueue.push_back(input);
}
void Game::AddToUpdateQueue(std::function<void()> input) {
  UpdateQueue.push_back(input);
}
std::shared_ptr<Entity> Game::MakeSprite(X_Vector pos, X_Vector scale, bool ePhysics) {
  EntityHandler ent = InnerMakeSprite(pos, scale);
  if (ePhysics)
    ent->AddAddon<Physics>();
  defaultBatch.mySprites.push_back(ent->GetAddon<Sprite>());
  std::weak_ptr<Entity> weaker = ent;
  return weaker.lock();
}

std::shared_ptr<Entity> Game::MakeSprite(X_Vector pos, X_Vector scale, ShaderBatch *batch) {
  EntityHandler ent = InnerMakeSprite(pos, scale);
  batch->mySprites.push_back(ent->GetAddon<Sprite>());
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
      if (shdrBatches[i]->mySprites[f]->owner->ID == e->ID) {
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
  ScriptingSystem::Init(this);
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
          for (int y = 0;
               y < shdrBatches[i]->mySprites[f]->owner->m_Addons.size(); y++) {
            shdrBatches[i]->mySprites[f]->owner->m_Addons[y]->OnUpdate(dt,
                                                                       alpha);
          }
          if (shdrBatches[i]->mySprites[f])
            renderer.Submit((shdrBatches[i]->mySprites[f].get()));
        }
      }
      renderer.End();
    } else {
      for (int f = 0; f < shdrBatches[i]->mySprites.size(); f++) {
        if (shdrBatches[i]->mySprites[f]) {
          renderer.Begin();
          for (int y = 0;
               y < shdrBatches[i]->mySprites[f]->owner->m_Addons.size(); y++) {
            shdrBatches[i]->mySprites[f]->owner->m_Addons[y]->OnUpdate(dt,
                                                                       alpha);
          }
          renderer.Submit((shdrBatches[i]->mySprites[f].get()));
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
  FixedUpdate(dt);
  for (int i = 0; i < shdrBatches.size(); i++) {
    for (int f = 0; f < shdrBatches[i]->mySprites.size(); f++) {
      for (auto &it : shdrBatches[i]->mySprites[f]->owner->m_Addons) {
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

bool Game::IsKeyDown(int key){
  return glfwGetKey(m_Window->m_window,key) == GLFW_PRESS;
}
