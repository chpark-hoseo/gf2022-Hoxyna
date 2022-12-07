#include "Player.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
    handleInput();

    if (m_velocity.getX() == 0 && m_velocity.getY() == 0) // 과제 2
    {
        m_currentFrame = ((SDL_GetTicks() / 500) % 2);
        m_currentRow = 1;
    }
    else
    {
        m_currentFrame = ((SDL_GetTicks() / 100) % 10);
        m_currentRow = 0;
    }

	SDLGameObject::update();
}

void Player::clean() {}

void Player::handleInput()
{
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) && m_canMoveRight) {
        m_velocity.setX(2);
        m_bFlipHorizontal = false;
    }
    else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A) && m_canMoveLeft) {
        m_velocity.setX(-2);
        m_bFlipHorizontal = true;
    }
    else
        m_velocity.setX(0); // 과제 1
    //if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W) && m_canMoveUp) {
    //    m_velocity.setY(-2);
    //}
    //else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S) && m_canMoveDown) {
    //    m_velocity.setY(2);
    //}
    //else
    //    m_velocity.setY(0); // 과제 1
}