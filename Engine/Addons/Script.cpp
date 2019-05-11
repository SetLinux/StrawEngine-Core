#include "../Game/Entity.h"
#include "Script.h"
Script::Script(const std::string &path) {
  m_path = path;
}
void Script::OnCreate(){
  sol::load_result loadresult = ScriptingSystem::LoadFile(m_path);
  if(!loadresult.valid()){
    sol::error err = loadresult;
    std::cout << err.what() << std::endl;
    assert(0);
  }
  
  sol::table tbl = loadresult();
  
  std::cout << "Okay Loaded " << std::endl;
  create = tbl["OnCreate"];
  update = tbl["OnUpdate"];
  fixedupdate = tbl["OnFixedUpdate"];
  ScriptingSystem::luastate["owner"] = this->owner;
  sol::protected_function_result result = create();
  
  if(!result.valid()){
    sol::error err = result;
    std::cout << "ERROR Create: " << err.what() << std::endl;
  }
    
};

void Script::OnUpdate(float dt , float alpha) {
  ScriptingSystem::luastate["owner"] = this->owner;
  sol::protected_function_result result = update();
  
  if(!result.valid()){
    sol::error err = result;
    std::cout << "ERROR Update: " << err.what() << std::endl;
  }
  
}
void Script::OnFixedUpdate(float dt) {
  ScriptingSystem::luastate["owner"] = this->owner;  
  sol::protected_function_result result = fixedupdate();
  
  if(!result.valid()){
    sol::error err = result;
    std::cout << "ERROR FixedUpdate: " << err.what() << std::endl;
  }
  
}
