#include "FallingBlock.h"
#include "InputHandler.h"
#include "Game.h"

FallingBlock::FallingBlock(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void FallingBlock::draw()
{
	SDLGameObject::draw();
}

void FallingBlock::update()
{
	//m_acceleration.setY(0.1f);
	m_velocity.setY(3);
	SDLGameObject::update();
}

void FallingBlock::clean() {}

void FallingBlock::handleInput() {}
