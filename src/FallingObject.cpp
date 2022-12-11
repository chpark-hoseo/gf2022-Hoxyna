#include "FallingObject.h"
#include "InputHandler.h"
#include "Game.h"

FallingObject::FallingObject(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void FallingObject::draw()
{
	SDLGameObject::draw();
}

void FallingObject::update()
{
	//m_acceleration.setY(0.1f);
	m_velocity.setY(3);
	SDLGameObject::update();
}

void FallingObject::clean() {}

void FallingObject::handleInput() {}
