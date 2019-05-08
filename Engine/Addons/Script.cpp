#include "Script.h"
Script::Script(const std::string &path) {
  m_path = path;
}
void Script::OnCreate(){
  sol::table tbl =  ScriptingSystem::LoadFile(m_path)();
  Start = tbl["Start"];
  Update = tbl["Update"];
  FixedUpdate = tbl["FixedUpdate"];
  ScriptingSystem::luastate["owner"] = this->owner;
  Start();
};

void Script::OnUpdate(float dt , float alpha) {
  ScriptingSystem::luastate["owner"] = this->owner;
  Update();
}
void Script::OnFixedUpdate(float dt) {
  ScriptingSystem::luastate["owner"] = this->owner;
  FixedUpdate();
}
