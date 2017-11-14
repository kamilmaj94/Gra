#include "PCH.hpp"
#include "Dot.hpp"
#include "Globals.hpp"
#include "Ground.hpp"

Dot::Dot()
    : position(320,240)
    , velocity(0,0)
    , angle(0)
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
        mBodyDef.position.Set(position.x, position.y);
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

void Dot::HandleEvent(SDL_Event& e)
{

    //mBody->ApplyLinearImpulse(velocity, mBody->GetWorldCenter(), 1);
    //mBody->ApplyAngularImpulse(100, 1);
    //mBody->ApplyTorque(100, 1);

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP: velocity.y -= DOT_VEL; break;
        case SDLK_DOWN: velocity.y += DOT_VEL; break;
        case SDLK_LEFT: velocity.x -= DOT_VEL; break;
        case SDLK_RIGHT: velocity.x += DOT_VEL; break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP: velocity.y += DOT_VEL; break;
        case SDLK_DOWN: velocity.y -= DOT_VEL; break;
        case SDLK_LEFT: velocity.x += DOT_VEL; break;
        case SDLK_RIGHT: velocity.x -= DOT_VEL; break;
        }
    }

	//dot.move part
	position.x += velocity.x;
	if ((position.x < 0) ||
		(position.x + DOT_WIDTH > SCREEN_WIDTH))
	{
		position.x -= velocity.x;
	}

	position.y += velocity.y;
	if ((position.y < 0) ||
		(position.y + DOT_HEIGHT > SCREEN_HEIGHT))
	{
		position.y -= velocity.y;
	}

	/*
	TYPES OF MOVEMENT - needs further investigation
	*/
	mBody->ApplyForce(velocity, mBody->GetWorldCenter(), 1);
}

void Dot::Render() const
{
    mDotTexture.Render(mBody->GetPosition().x, mBody->GetPosition().y, 0, mBody->GetAngle(), 0, SDL_FLIP_NONE);
}

