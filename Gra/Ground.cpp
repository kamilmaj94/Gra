#include "PCH.hpp"
#include "Globals.hpp"
#include "Ground.hpp"

Ground::Ground()
{
    std::default_random_engine generator;
    generator.seed(time(NULL));
    std::uniform_int_distribution<int> distribution(100, SCREEN_WIDTH);
    prostokat.h = 10;
    prostokat.w = distribution(generator);  // generates width of the ground [minimum = 100 to width of the actual screen]}
    prostokat.x = 0;
    prostokat.y = (SCREEN_HEIGHT / 2) - 200;
}

void Ground::Render()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
    SDL_RenderFillRect(gRenderer, &prostokat);
}
