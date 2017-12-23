#pragma once

#include "Texture.hpp"

// The dot that will move around on the screen
// Temporary placeholder class for further development
class Dot
{
public:
    static const int DOT_VEL = 100000;

    Dot();

    bool Init(b2World& world);
    void Move();
    void Render() const;

    FORCEINLINE void SetPosition(b2Vec2 position)
    {
        mBody->SetTransform(position, mAngle);
    }

    FORCEINLINE void SetAngle(float32 angle)
    {
        mAngle = angle;
    }

    FORCEINLINE void ApplyVelocity(b2Vec2 vel)
    {
        mVel += vel;
    }

    FORCEINLINE b2Body *GetBody() const
    {
        return mBody;
    }

private:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    float32 mAngle;
    b2Vec2 mVel;
    Texture mDotTexture;
    b2Body* mBody;
};
