#pragma once

#include "Texture.hpp"

// The dot that will move around on the screen
// Temporary placeholder class for further development
class Dot
{
public:
    Dot();

    bool Init(b2World& world);
    void HandleEvent( SDL_Event& e );
    //void Move(SDL_Event& e);
    void Render() const;

    FORCEINLINE void SetPosition(b2Vec2 position)
    {
        mBody->SetTransform(position, angle);
    }

    FORCEINLINE void SetVelocity(b2Vec2 velocity)
    {
        mBody->SetLinearVelocity(velocity);
    }

    FORCEINLINE void SetAngle(float32 angle)
    {
        this->angle = angle;
    }

    FORCEINLINE b2Body *GetBody() const
    {
        return mBody;
    }

    FORCEINLINE b2Vec2 GetPosition() const
    {
        return position;
    }

    FORCEINLINE b2Vec2 GetVelocity() const
    {
        return velocity;
    }

private:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int DOT_VEL = 1000000;

    b2Vec2 position;
    b2Vec2 velocity;
    float32 angle;

    Texture mDotTexture;

    b2Body* mBody;
};
