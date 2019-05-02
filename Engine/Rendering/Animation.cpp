#include "Animation.h"
Animation::Animation()
{
}
Animation::~Animation()
{
}
void Animation::MakeAnimation(int start, int end)
{
    for (int i = start; i < end + 1; i++)
    {
        m_FramesIndexes.push_back(i);
        LOG(i);
    }
}
void Animation::Animate(float dt)
{
    timer += dt * speed;
    if((int)(timer/timeBetweenFrames) > m_FramesIndexes.size()-1)
      timer = 0;
    CurrentFrameIndex = m_FramesIndexes[(int)(timer / timeBetweenFrames)];
}
