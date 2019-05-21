#pragma once
#include <Box2D/Box2D.h>
#include "../Addons/Sprite.h"
#include <functional>
#include "RaycastHandler.h"
#include "ContactListener.h"
class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();
	
	static float MPP;
	static float Gravity;
	static void Init();
	static void UpdateWorld(float dt);
	static b2World* GetWorld() { return m_world; };
        static void RayCast(X_Vector pointa, X_Vector pointb,
                            std::function<void(Entity *,X_Vector normal)> clbck) {
          rch.CallBack = clbck;
          m_world->RayCast(&rch, X_Vector::ToVec<b2Vec2>(pointa / MPP),
                           X_Vector::ToVec<b2Vec2>(pointb / MPP));
        }
	static void MakeListener(std::function<void(Entity*,Entity*,b2Contact*)> CallBack);

      private:
        static b2World *m_world;
        static RaycastHandler rch;
};
