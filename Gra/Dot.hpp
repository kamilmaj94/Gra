#pragma once

#include "Texture.hpp"

// The dot that will move around on the screen
// Temporary placeholder class for further development
class Dot : Ground
{
public:
    Dot();

    bool Init();
    void HandleEvent( SDL_Event& e );
    void Move();
    void Render() const;

private:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int DOT_VEL = 10;

    int mPosX;
    int mPosY;
    int mVelX;
    int mVelY;

    // TODO temporary - should probably capture a pointer to texture
    Texture mDotTexture;
};
