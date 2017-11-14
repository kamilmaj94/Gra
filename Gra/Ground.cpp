#include "PCH.hpp"
#include "Ground.hpp"
#include "Globals.hpp"



Ground::Ground(b2World& world)
{
    std::default_random_engine generator;
    generator.seed(time(NULL));
    std::uniform_int_distribution<int> distribution(100, SCREEN_WIDTH);
    mRect.h = 10;
    //mRect.w = distribution(generator);  // generates width of the ground [minimum = 100 to width of the actual screen]}
    mRect.w = SCREEN_WIDTH - 100;
    mRect.x = 0;
    mRect.y = (SCREEN_HEIGHT / 2) + 200;

    // Define the ground body.
    groundBodyDef.position.Set(mRect.w / 2 + mRect.x, mRect.y);
    // Add the ground fixture to the ground body.
    groundBody = world.CreateBody(&groundBodyDef);

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(mRect.w/2, mRect.h);
    //groundBox.SetAsBox(mRect.w / 2, mRect.h, b2Vec2((mRect.w / 2), (mRect.h / 2)), 0);
    b2FixtureDef groundFixture;
    groundFixture.shape = &groundBox;
    groundFixture.density = 0.0f;
    groundFixture.friction = 1.0f; //Dot has same friction and it still does slide for some reason - temporary solution, because works pretty ok

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundFixture);
}

void Ground::Render()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
    SDL_RenderFillRect(gRenderer, &mRect);
}

b2BodyDef Ground::GetBody()
{
    return groundBodyDef;
}

SDL_Rect Ground::getRect()
{
    return mRect;
}
