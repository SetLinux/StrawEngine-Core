#pragma once
#include "../Math/Math.h"
#include "Addon.h"
#include <deque>
#include <iostream>
#include <list>
#include <vector>
class Entity {
public:
  Entity() {}
  ~Entity() {

    for (auto &it : m_Addons) {
      if (it)
        delete it;
    }
    m_Addons.clear();
  }
  // Vectors For Transformation
  X_Vector position{0, 0}, scale{0, 0};
  float Rotation{40};
  template <typename T> T *AddAddon() {
    T *x = new T();
    x->owner = (Entity *)this;
    x->OnCreate();
    m_Addons.push_back(x);
    return x;
  };

  template <typename T> T *GetAddon() {
    for (int i = 0; i < m_Addons.size(); i++) {
      if ((m_Addons[i])->myType() == T::GetType()) {
        return (T *)m_Addons[i];
      }
    }
    assert(1);
    return NULL;
  };
  std::vector<Addon *> m_Addons;
  void *Data = (void *)NULL;
  // ID mainly for sorting
  int ID = 0;

private:
};
