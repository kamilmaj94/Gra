#pragma once



class Ground
{
public:
    Ground(b2World& world);
    void Render();
    b2BodyDef GetBody();
    SDL_Rect getRect();
private:
    SDL_Rect mRect;
    b2BodyDef groundBodyDef;
    b2PolygonShape groundBox;     // Define the ground box shape.
    b2Body* groundBody;
};