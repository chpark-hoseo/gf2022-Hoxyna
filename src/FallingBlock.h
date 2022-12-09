#pragma once

#include <SDL2/SDL.h>

#include "SDLGameObject.h"

class FallingBlock : public SDLGameObject
{
public:
    FallingBlock(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
    void handleInput();

    void setVelocityY(int input) { m_velocity.setY(input); }
};