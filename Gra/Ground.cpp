#include "PCH.hpp"
#include "Ground.hpp"
#include "Globals.hpp"


Ground::Ground()
{
    std::default_random_engine generator;
    generator.seed(time(NULL));
    std::uniform_int_distribution<int> distribution(100, SCREEN_WIDTH);
    mRect.h = 10;
    mRect.w = distribution(generator);  // generates width of the ground [minimum = 100 to width of the actual screen]}
    mRect.x = 0;
    mRect.y = (SCREEN_HEIGHT / 2) - 200;
}

void Ground::Render()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
    SDL_RenderFillRect(gRenderer, &mRect);
}
