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
    void Move();
    void Render() const;
    b2Body *GetBody();

    void SetPosition(b2Vec2 position);
    void SetVelocity(b2Vec2 velocity);
    void SetAngle(float32 angle);

    b2Vec2 GetPosition();
    b2Vec2 GetVelocity();

private:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int DOT_VEL = 1000000;

    b2Vec2 position;
    b2Vec2 velocity;
    float32 angle;

    Texture mDotTexture;

    b2Body* body;
};
