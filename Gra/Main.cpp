#include "PCH.hpp"
#include "Utils.hpp"
#include "Texture.hpp"
#include "Globals.hpp"
#include "Dot.hpp"
#include "Ground.hpp"

bool gKeys[512];
bool gQuit = false;

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

    gWindow = SDL_CreateWindow("The Witcher 4 leaked demo pre alpha 0.00001", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

void HandleEvents()
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            gQuit = true;
        }

        if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                gQuit = true;
            }
        }

        if (e.type == SDL_KEYDOWN)
        {
            gKeys[e.key.keysym.scancode] = true;
        }

        if (e.type == SDL_KEYUP)
        {
            gKeys[e.key.keysym.scancode] = false;
        }
    }
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
        system("pause");
        return 1;
    }

    // Construct a world object, which will hold and simulate the rigid bodies.
    // Define the gravity vector.
    b2Vec2 gravity(0.0f, 100.0f);
    b2World world(gravity);

    Ground floor(world);

    Dot dot;
    if (!dot.Init(world))
    {
        std::cout << "Failed to initialize Dot" << std::endl;
        system("pause");
        Close();
        return 2;
    }

    // TODO timestep should be measured from frame time
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for (uint32_t i = 0; i < 512; ++i)
        gKeys[i] = false;

    while (!gQuit)
    {
        /////////////////////
        // UPDATING EVENTS //
        /////////////////////

        // process window events (pressed keys etc)
        HandleEvents();

        // update Dot according to pressed keys
        if (gKeys[SDL_SCANCODE_UP])
            dot.ApplyMoveDirection(b2Vec2(0.0f, -1.0f));
        if (gKeys[SDL_SCANCODE_LEFT])
            dot.ApplyMoveDirection(b2Vec2(-1.0f, 0));
        if (gKeys[SDL_SCANCODE_RIGHT])
            dot.ApplyMoveDirection(b2Vec2(1.0f, 0));

        // reflect velocity in Dot's body
        dot.Update();

        // physics simulation step
        world.Step(timeStep, velocityIterations, positionIterations);

        ///////////////
        // RENDERING //
        ///////////////

        // prepare frame
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // draw objects
        dot.Render();
        floor.Render();

        // show on screen
        SDL_RenderPresent(gRenderer);
    }

    Close();

    return 0;
}
