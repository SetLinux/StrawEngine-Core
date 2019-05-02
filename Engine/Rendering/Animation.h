#pragma once
#include "../Utils/LogSystem.h"
#include <iostream>
#include <vector>
class Animation {
public:
  Animation();
  ~Animation();
  void MakeAnimation(int start, int end);
  void Animate(float dt);
  int CurrentFrameIndex{0};
  float speed{2};
  std::vector<int> m_FramesIndexes;

private:
  float timer{0};
  float timeBetweenFrames{1.f};
};
