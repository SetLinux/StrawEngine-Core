#include "../Game/Entity.h"
#include "Sprite.h"
#include "Animator.h"



Animator::Animator() : spriteHeight(0), spriteWidth(0)
{
}


Animator::~Animator()
{
}

void Animator::OnCreate() {
	
}

void Animator::OnUpdate(float dt,float alpha)
{
	if(m_anim){
		m_anim->Animate(dt);
        	SetIndex(m_anim->CurrentFrameIndex);
	}

}
void Animator::OnFixedUpdate(float dt) {

}
void Animator::SetIndex(int index)
{
if(CurrentFrameIndex != index){
	CurrentFrameIndex = index;
	const float tw = float(spriteWidth) / owner->GetAddon<Sprite>()->tex->Width;
	const float th = float(spriteHeight) / owner->GetAddon<Sprite>()->tex->Height;
	const int numPerRow = owner->GetAddon<Sprite>()->tex->Width / spriteWidth;
	const float tx = (index % numPerRow) * tw;
	const float ty = (index/ (numPerRow)) * th;
	/*
	const float texVerts[] = {
		tx, ty,
		tx + tw, ty,
		tx + tw, ty + th,
		tx, ty + th
	};
	*/
	const float texVerts[] = {
		tx + tw, ty + th,
		tx + tw, ty,
		tx, ty,
		tx, ty + th,
	};
	for (int i = 0; i < 8; i += 2)
	{
		owner->GetAddon<Sprite>()->vertices[i / 2].TexCoord = X_Vector(texVerts[i], texVerts[i + 1]);
	}
}
}
