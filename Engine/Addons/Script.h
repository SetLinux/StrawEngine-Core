#pragma once
#include <iostream>
#include "../Game/Addon.h"
class Script : public Addon{
 public:
  Script(const std::string& path);
  ~Script(){};

public:
  AddonBody(AddonType::ScriptAddon);
  
private:
  sol::function create,update,fixedupdate;
  std::string m_path;
};

  
