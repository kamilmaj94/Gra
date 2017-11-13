#pragma once



class Ground
{
public:
    Ground();
    void Render();
private:
    const int height = 10;
    int width;
    const int mPosY = SCREEN_HEIGHT / 2 ;
    int mPosX;
    int mVelX;
    SDL_Rect prostokat;

};