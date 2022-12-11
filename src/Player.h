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

    bool getInvincible() { return isInvincible; }
    bool getBoosted() { return isBoosted; }
    int getHp() { return hp; }

    void setTimer(int input) { timer = input; }

    void setInvincible(bool input) { isInvincible = input; }
    void setInvEndTime(int input) { inv_endTime = input; }

    void setBoosted(bool input) { isBoosted = input; }
    void setBooEndTime(int input) { boo_endTime = input; }

    void setHp(int input) { hp = input; }

    int timer;

    // invincible
    bool isInvincible;
    int inv_endTime;

    // boost
    bool isBoosted;
    int boo_endTime;

    // health
    int hp;
};