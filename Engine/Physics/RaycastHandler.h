#pragma once
#include <Box2D/Box2D.h>
#include "../Addons/Sprite.h"
#include <functional>
#include "../Game/Entity.h"
class RaycastHandler : public b2RayCastCallback
{
public:
	RaycastHandler();
	~RaycastHandler();
  std::function<void(Entity*,X_Vector normal)> CallBack;
	// Inherited via b2RayCastCallback
	virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
};

