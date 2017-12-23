#include "PCH.hpp"
#include "Dot.hpp"
#include "Globals.hpp"
#include "Ground.hpp"

Dot::Dot()
    : mAngle(0)
    , mVel(0, 0)
{

}

bool Dot::Init(b2World& world)
{
    if (!mDotTexture.Init("Data/Textures/smile.bmp"))
    {
        return 1;
    }
    else
    {
        // Define the dynamic mBody. We set its position and call the mBody factory.
        b2BodyDef mBodyDef;
        mBodyDef.type = b2_dynamicBody;
        mBodyDef.position.Set(320, 240);
        mBody = world.CreateBody(&mBodyDef);
        // Define circle shape for our dynamic mBody.
        b2CircleShape dynamicCircle;
        dynamicCircle.m_radius = DOT_HEIGHT / 2;
        // Define the dynamic mBody fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicCircle;
        // Set the box density to be non-zero, so it will be dynamic.
        fixtureDef.density = 1.0f;
        // Override the default friction.
        fixtureDef.friction = 1.0f;
        // Add the shape to the mBody.
        mBody->CreateFixture(&fixtureDef);
    }
    return true;
}

void Dot::Move()
{
    mBody->ApplyForce(mVel, mBody->GetWorldCenter(), 1);
    mVel = b2Vec2(0, 0);
}

void Dot::Render() const
{
    mDotTexture.Render(mBody->GetPosition().x, mBody->GetPosition().y, 0, mBody->GetAngle(), 0, SDL_FLIP_NONE);
}

