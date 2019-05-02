#pragma once
#include "../Utils/LogSystem.h"
#include "../Game/Addon.h"
#include "../Math/Math.h"
#include "../Rendering/Animation.h"
class Animator : public Addon
{
public:
	Animator();
	~Animator();
public:
	AddonBody(AddonType::AnimationAddon);
public:
	void SetIndex(int index);
	int CurrentFrameIndex = -1;
	void SetSpriteDimension(X_Vector dim) {
		spriteWidth = dim.x;
		spriteHeight = dim.y;
	}
	inline void SetAnim(Animation* anim){Animation* b = new Animation(); b->m_FramesIndexes = anim->m_FramesIndexes; b->speed = anim->speed ; m_anim = b;};
        inline bool isitcurrentrunning(Animation *anim) {return anim == m_anim;};

      private:
	float spriteWidth, spriteHeight;
	Animation* m_anim;
	
};

