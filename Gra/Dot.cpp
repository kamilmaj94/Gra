#include "PCH.hpp"
#include "Dot.hpp"
#include "Globals.hpp"
#include "Ground.hpp"

Dot::Dot()
    : mPosX(0)
    , mPosY(0)
    , mVelX(0)
    , mVelY(0)
{

    /*  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        This thing SHOULD BE implemented somewhere here.
        It describes physical material based on basic variables of this object, like 
        size and position in space.
    *///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(mPosX , mPosY);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);
}

bool Dot::Init()
{
    return mDotTexture.Init("Data/Textures/dot.bmp");
}

void Dot::HandleEvent(SDL_Event& e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::Move()
{
    mPosX += mVelX;
    if ((mPosX < 0) ||
        (mPosX + DOT_WIDTH > SCREEN_WIDTH))
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;
    if ((mPosY < 0) ||
        (mPosY + DOT_HEIGHT > SCREEN_HEIGHT))
    {
        mPosY -= mVelY;
    }
}

void Dot::Render() const
{
    mDotTexture.Render(mPosX, mPosY);
}
