#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams)
    : GameObject(pParams) , m_position(pParams->getX(), pParams->getY()), m_velocity(0,0), m_acceleration(0,0)
{
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_currentRow = 0;
    m_currentFrame = 0;

    m_bFlipHorizontal = false; // 과제 3

    m_canMoveRight = true;
    m_canMoveLeft = true;
    m_canMoveUp = true;
    m_canMoveDown = true;
}

void SDLGameObject::update()
{
    if (!m_canMoveRight && m_velocity.getX() > 0) m_velocity.setX(0);
    if (!m_canMoveLeft && m_velocity.getX() < 0) m_velocity.setX(0);
    if (!m_canMoveUp && m_velocity.getY() < 0) m_velocity.setY(0);
    if (!m_canMoveDown && m_velocity.getY() < 0) m_velocity.setY(0);
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

void SDLGameObject::draw()
{
    SDL_RendererFlip flip = m_bFlipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE; // 과제 3
    TextureManager::Instance()->drawFrame(m_textureID,
         (int) m_position.getX(), (int)m_position.getY(), 
         m_width, m_height, m_currentRow, m_currentFrame,
         TheGame::Instance()->getRenderer(), flip); // 과제 3
}