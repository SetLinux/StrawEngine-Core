#pragma once
#include "../Scripting/ScriptingSystem.h"
#include "../Game/Addon.h"
class Script : public Addon{
 public:
  Script(const std::string& path);
  ~Script(){};

public:
  AddonBody(AddonType::ScriptAddon);

private:
  std::string m_path;
  sol::function Start;
  sol::function Update;
  sol::function FixedUpdate;
};
