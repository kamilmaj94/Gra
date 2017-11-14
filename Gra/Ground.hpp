#pragma once



class Ground
{
public:
    Ground();
    void Render();
    SDL_Rect getBody();
private:
    SDL_Rect mRect;
};