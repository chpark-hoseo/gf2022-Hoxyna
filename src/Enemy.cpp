#include "Enemy.h"
#include "InputHandler.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	handleInput();

	m_currentFrame = ((SDL_GetTicks() / 100) % 6);
	//m_acceleration.setX(1);
	SDLGameObject::update();
}

void Enemy::clean() {}

void Enemy::handleInput()
{
	if (TheInputHandler::Instance()->getMouseButtonState(LEFT)) {
		printf("shoot \n");
	}
	Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
	m_velocity = (*vec - m_position) / 100;
}
