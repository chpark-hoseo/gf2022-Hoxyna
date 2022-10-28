#include "Monster.h"

void Monster::load(int x, int y, int width, int height, std::string textureID)
{
    GameObject::load(x, y, width, height, textureID);
}

void Monster::draw(SDL_Renderer* pRenderer)
{
    GameObject::draw(pRenderer);
}

void Monster::update()
{
    m_currentFrame = ((SDL_GetTicks() / 100) % 6);

    if (m_x < 0)
    {
        m_bFlipX = false;
        m_bMoveLeft = false;
    }
    else if (m_x > 480 - m_width)
    {
        m_bFlipX = true;
        m_bMoveLeft = true;
    }

    if (m_bMoveLeft)
        m_x -= m_speed;
    else
        m_x += m_speed;
}