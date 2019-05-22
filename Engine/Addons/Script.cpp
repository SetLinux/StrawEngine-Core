#include "../Game/Entity.h"
#include "Script.h"
Script::Script(const std::string &path) {
  m_path = path;
}
void Script::OnCreate(){
  loadresult = ScriptingSystem::LoadFile(m_path);
  if(!loadresult.valid()){
    sol::error err = loadresult;
    std::cout << err.what() << std::endl;
    assert(0);
  }
  
  tbl = loadresult();

  std::cout << "Okay Loaded " << std::endl;
  create = tbl["OnCreate"];
  update = tbl["OnUpdate"];
  fixedupdate = tbl["OnFixedUpdate"];
  ScriptingSystem::luastate["owner"] = this->owner;
  sol::protected_function_result result = create();
  returntable = tbl;
  if(!result.valid()){
    sol::error err = result;
    std::cout << "ERROR Create(): " << err.what() << std::endl;
  }
};

void Script::OnUpdate(float dt , float alpha) {
  ScriptingSystem::luastate["owner"] = this->owner;
  sol::protected_function_result result = update(dt);
  
  if(!result.valid()){
    sol::error err = result;
    std::cout << "ERROR Update(): " << err.what() << std::endl;
  }
}
void Script::OnFixedUpdate(float dt) {
  ScriptingSystem::luastate["owner"] = this->owner;  
  sol::protected_function_result result = fixedupdate();
  
  if(!result.valid()){
    sol::error err = result;
    std::cout << "ERROR FixedUpdate(): " << err.what() << std::endl;
  }
  
}
