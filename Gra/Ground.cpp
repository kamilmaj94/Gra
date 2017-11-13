#include "PCH.hpp"
#include "Globals.hpp"
#include "Ground.hpp"

Ground::Ground(): mPosX(0)
{
    std::default_random_engine generator;
    generator.seed(time(NULL));
    std::uniform_int_distribution<int> distribution(100, SCREEN_WIDTH);
    width = distribution(generator);  // generates number in the range 1..6 
}

void Ground::Render()
{
    prostokat.h = this->height;
    prostokat.w = this->width;
    prostokat.x = this->mPosX;
    prostokat.y = this->mPosY;
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
    SDL_RenderFillRect(gRenderer, &prostokat);
    SDL_RenderDrawRect(gRenderer, &prostokat);
}
