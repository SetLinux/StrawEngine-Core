#include "ScriptingSystem.h"
#include "../Game/Game.h"
sol::state ScriptingSystem::luastate;
void ScriptingSystem::Init(Game* game) {
  luastate.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string,
                          sol::lib::io);
  luastate.new_usertype<X_Vector>("X_Vector",sol::constructors<X_Vector(float,float),X_Vector(float,float,float)>());
}
sol::load_result ScriptingSystem::LoadFile(const std::string &path) {
  sol::load_result x = luastate.load_file(path);
  return x;
}
