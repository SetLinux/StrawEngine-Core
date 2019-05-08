#pragma once
#include <lua.hpp>
#include "../Utils/sol.hpp"
#include "../Game/Entity.h"
#include "../Addons/Script.h"
#include "../Addons/Physics.h"
#include "../Addons/Animator.h"
class Game;
class ScriptingSystem {
 public:
  static void Init(Game* game);
  static sol::state luastate;
  static sol::load_result LoadFile(const std::string& path);
  
};
