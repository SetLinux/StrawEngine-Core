#pragma once
#include "../Game/Addon.h"
#include "../Math/Math.h"
#include <Box2D/Box2D.h>
class Physics : public Addon{
public:
    Physics();
    ~Physics();
    AddonBody(AddonType::PhysicsAddon);
    inline X_Vector GetBodyPosition(){return X_Vector::fromVec<b2Vec2>(m_body->GetPosition());};
    inline b2Body* getBody(){
        return m_body ;
    };
    //TODO : Remove This
    int id = 10;
private:
    X_Vector prevpos;
    b2Body* m_body;
};
