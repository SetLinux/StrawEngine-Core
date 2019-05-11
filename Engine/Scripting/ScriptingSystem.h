#pragma once
#include <lua.hpp>
#include "../Utils/sol.hpp"

class ScriptingSystem {
 public:
  static void Init();
  static sol::state luastate;
  static sol::load_result LoadFile(const std::string& path);
  template <typename T,typename... Args> static void LuaRegisterClass(Args... args) {
    luastate.new_usertype<T>(args...);
  }
  template <typename T,typename B> static void AddMember(const std::string& name,B member,T value){
    luastate[name][member] = value;
  }
};
