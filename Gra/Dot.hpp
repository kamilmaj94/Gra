#pragma once

#include "Texture.hpp"

class Dot
{
public:
    Dot();

    bool Init(b2World& world);
    void Update();
    void Render() const;

    FORCEINLINE void SetPosition(b2Vec2 position)
    {
        mBody->SetTransform(position, mAngle);
    }

    FORCEINLINE void SetAngle(float32 angle)
    {
        mAngle = angle;
    }

    // You tell the direction and value -1..1, this is scaled
    // according to DOT_VEL and accumulated for later update.
    FORCEINLINE void ApplyMoveDirection(b2Vec2 vel)
    {
        mVel.x += DOT_VEL * vel.x;
        mVel.y += DOT_VEL * vel.y;
    }

    FORCEINLINE b2Body *GetBody() const
    {
        return mBody;
    }

private:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int DOT_VEL = 100000;

    float32 mAngle;
    b2Vec2 mVel;
    Texture mDotTexture;
    b2Body* mBody;
};
