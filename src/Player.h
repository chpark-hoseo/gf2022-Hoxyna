#pragma once

#include <SDL2/SDL.h>

#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
    Player(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
    void handleInput();
    
    bool isInvincible; // invincible item
    bool isBoosted; // boost item
};