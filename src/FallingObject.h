#pragma once

#include <SDL2/SDL.h>

#include "SDLGameObject.h"

class FallingObject : public SDLGameObject
{
public:
    FallingObject(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
    void handleInput();
};