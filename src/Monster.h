#pragma once
#include "GameObject.h"

class Monster : public GameObject 
{
public:
    void load(int x, int y, int width, int height, std::string textureID);
    void draw(SDL_Renderer* pRenderer);
    void update();
    void clean() {};
    
    void set_speed(int speed) { m_speed = speed; }

private:
    int m_speed;
    bool m_bMoveLeft;
};