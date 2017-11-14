#pragma once

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

#ifdef WIN32
#define FORCEINLINE __forceinline
#else
#error "Platform not supported"
#endif
#define PI 3.14159265359