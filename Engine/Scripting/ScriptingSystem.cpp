#include "ScriptingSystem.h"
sol::state ScriptingSystem::luastate;
void ScriptingSystem::Init() {
  
  luastate.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string,
                          sol::lib::io,sol::lib::math);
}
sol::load_result ScriptingSystem::LoadFile(const std::string &path) {
  sol::load_result x = luastate.load_file(path);
  return x;
}
