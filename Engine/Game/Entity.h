#pragma once
#include "../Math/Math.h"
#include "Addon.h"
#include <deque>
#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <cstdarg>
class Entity : public std::enable_shared_from_this<Entity>{
public:
  Entity() {}
  ~Entity() {  }
  // Vectors For Transformation
  X_Vector position{0, 0,0}, scale{0, 0,0};
  float Rotation{0};
  template <typename T,typename... Args> std::shared_ptr<T> AddAddon(Args... args) {
    std::shared_ptr<T> x = std::make_shared<T>(args...);
    std::shared_ptr<Entity> me = shared_from_this();
    x->owner = me;
    x->OnCreate();
    m_Addons.push_back(x);
    std::weak_ptr<T> weaker = (x);
    std::shared_ptr<T> returned = weaker.lock();
    return returned;
  };

  template <typename T> std::shared_ptr<T> GetAddon() {
    for (int i = 0; i < m_Addons.size(); i++) {
      if ((m_Addons[i])->myType() == T::GetType()) {
	std::weak_ptr<T> weaker = std::static_pointer_cast<T>(m_Addons[i]);
	std::shared_ptr<T> returned = weaker.lock();
	return returned;
      }
    }
    assert(1);
    return NULL;
  };
  std::vector<std::shared_ptr<Addon>> m_Addons;
  // ID mainly for sorting
  float ID = 0;

private:
};
