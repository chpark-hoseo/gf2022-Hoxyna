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

    if (m_velocity.getX() == 0 && m_velocity.getY() == 0) // 苞力 2
        m_currentFrame = 0;
    else
        m_currentFrame = ((SDL_GetTicks() / 100) % 6);

	SDLGameObject::update();
}

void Player::clean() {}

void Player::handleInput()
{
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        m_velocity.setX(2);
        m_bFlipHorizontal = false; // 苞力 3
    }
    else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
        m_velocity.setX(-2);
        m_bFlipHorizontal = true; // 苞力 3
    }
    else
        m_velocity.setX(0); // 苞力 1
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
        m_velocity.setY(-2);
    }
    else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        m_velocity.setY(2);
    }
    else
        m_velocity.setY(0); // 苞力 1
}