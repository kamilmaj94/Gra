#include "PCH.hpp"
#include "Utils.hpp"
#include "Texture.hpp"
#include "Globals.hpp"
#include "Dot.hpp"
#include "Ground.hpp"

bool Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    gWindow = SDL_CreateWindow("The most awesome game on Gwautke Systems", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL)
    {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == NULL)
    {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

void Close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[])
{
    if (!Utils::FS::SetCWD(Utils::FS::GetExecutableDir() + "/../../../"))
    {
        return 1;
    }

    if(!Init())
    {
        std::cout << "Failed to initialize!" << std::endl;
        return 1;
    }

    bool quit = false;

    SDL_Event e;
    Dot dot;
    Ground floor;

    /*
        DIRTY CODE - needs basically... everything
    */

    // Define the gravity vector.
    b2Vec2 gravity(0.0f, -10.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    b2World world(gravity);

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(prostokat.x, prostokat.y);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(prostokat.w, prostokat.h);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    /*
        i want to die :DDDD
    */

    if (!dot.Init())
    {
        std::cout << "Failed to initialize Dot" << std::endl;
        Close();
        return 2;
    }

    while(!quit)
    {
        while(SDL_PollEvent( &e ) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }

            if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
            }

            dot.HandleEvent(e);
        }
        dot.Move();
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        /*
            Objects to render are going below
        */
        dot.Render();
        floor.Render();
        SDL_RenderPresent(gRenderer);
    }
    Close();
    return 0;
}