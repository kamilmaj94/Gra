#pragma once

#include "Globals.hpp"

class Texture
{
public:
    Texture();
    ~Texture();

    bool Init(const std::string& path);
    void Release();

    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetBlendMode(SDL_BlendMode blending);
    void SetAlpha(Uint8 alpha);

    void Render(int x,
                int y,
                SDL_Rect* clip = NULL,
                double angle = 0.0,
                SDL_Point* center = NULL,
                SDL_RendererFlip flip = SDL_FLIP_NONE) const;

    FORCEINLINE int GetWidth() const
    {
        return mWidth;
    }

    FORCEINLINE int GetHeight() const
    {
        return mHeight;
    }

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};
