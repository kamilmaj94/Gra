#include "PCH.hpp"
#include "Dot.hpp"
#include "Globals.hpp"
#include "Ground.hpp"

Dot::Dot()
    : position(320,240) //collision works only when position = 0,0 ( ??? )
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
        // Define the dynamic body. We set its position and call the body factory.
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x, position.y);
        body = world.CreateBody(&bodyDef);
        // Define another box shape for our dynamic body.
        b2PolygonShape dynamicBox;
        b2CircleShape dynamicCircle;
        dynamicBox.SetAsBox(mDotTexture.GetWidth(), mDotTexture.GetHeight());
        dynamicCircle.m_radius = DOT_HEIGHT / 2;

        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        //Dear reviewer, not sure which one is more appropriate, both of them work ok
        //fixtureDef.shape = &dynamicBox;
        fixtureDef.shape = &dynamicCircle;
        // Set the box density to be non-zero, so it will be dynamic.
        fixtureDef.density = 1.0f;

        // Override the default friction.
        fixtureDef.friction = 1.0f; //safe: 0.3

        // Add the shape to the body.
        body->CreateFixture(&fixtureDef);
    }
    return true;
}

void Dot::HandleEvent(SDL_Event& e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: velocity.y -= DOT_VEL; break;
            case SDLK_DOWN: velocity.y += DOT_VEL; break;
            case SDLK_LEFT: velocity.x -= DOT_VEL; break;
            case SDLK_RIGHT: velocity.x += DOT_VEL; break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: velocity.y += DOT_VEL; break;
            case SDLK_DOWN: velocity.y -= DOT_VEL; break;
            case SDLK_LEFT: velocity.x += DOT_VEL; break;
            case SDLK_RIGHT: velocity.x -= DOT_VEL; break;
        }
    }
}


void Dot::Move()
{
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
    body->ApplyForce(velocity, body->GetWorldCenter(), 1);
    //body->ApplyLinearImpulse(velocity, body->GetWorldCenter(), 1);
    //body->ApplyAngularImpulse(100, 1);
    //body->ApplyTorque(100, 1);
}

void Dot::Render() const
{
    mDotTexture.Render(body->GetPosition().x, body->GetPosition().y,0,angle,0,SDL_FLIP_NONE);
}

b2Body *Dot::GetBody()
{
    return body;
}

void Dot::SetPosition(b2Vec2 position)
{
    this->position = position;
}

void Dot::SetVelocity(b2Vec2 velocity)
{
    this->velocity = velocity;
}

void Dot::SetAngle(float32 angle)
{
    this->angle = angle;
}

b2Vec2 Dot::GetPosition()
{
    return position;
}

b2Vec2 Dot::GetVelocity()
{
    return velocity;
}

