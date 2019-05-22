#pragma once
#include "../Game/Addon.h"
#include <iostream>
class Script : public Addon {
public:
  Script(const std::string &path);
  ~Script(){};

public:
  AddonBody(AddonType::ScriptAddon);
  template <class T,class Return> Return getVariable(T index) {
    Return temp = returntable[index];
    return temp;
  }
  //Please use this with caution
  sol::table returntable;
  sol::table tbl;
private:
  sol::function create, update, fixedupdate;
  std::string m_path;
  sol::load_result loadresult;
};
