#include "Bird.h"
#include <iostream>

Bird::Bird(const std::string &birdFilename)
{
    // Define the bird template
    DrawableObj::type("bird", GL_QUADS, "bird2.data", &DrawableObj::formatVertexColor);

    // Create the bird object instance
    birdObj = DrawableObj::create("bird");
    birdObj->setOffset(-0.5f, yOffset);
}

Bird::~Bird()
{
    delete birdObj;
}

/*
* Updates bird position on flight
*/
void Bird::update()
{
    if (fly >= 0.35f)
    {
        isFlying = false;
        fly = 0;
    }

    if (isFlying)
    {
        if (yOffset < MAX_FLIGHT_HEIGHT - 1.0f)
        {
            rotateAngle += rotateAngle >= 45.f ? 0 : 4.f;
            yOffset += 0.001f * GRAVITY;
        }
        fly += JUMP_INCREMENT;
    }
    else
    {
        if (yOffset > MIN_FLIGHT_HEIGHT)
        {
            rotateAngle -= rotateAngle <= -45.f ? 0 : 2.f;
            yOffset -= 0.002f * GRAVITY;
        }
    }

    birdObj->setRotation(rotateAngle);
    birdObj->setOffset(-0.5f, yOffset);
}

void Bird::jump()
{
    isFlying = true;
}

void Bird::draw()
{
    birdObj->draw();
}

void Bird::setSize(GLfloat scale)
{
    birdObj->setScale(scale);
}