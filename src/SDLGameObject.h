#pragma once

#include "GameObject.h"
#include <math.h>
#include "Vector2D.h"

class SDLGameObject : public GameObject {
public:
	SDLGameObject(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}
	virtual ~SDLGameObject() {}

	virtual Vector2D getPosition() { return m_position; }
	virtual int getWidth() { return m_width; }
	virtual int getHeight() { return m_height; }

	void setCanMoveRight(bool input) { m_canMoveRight = input; }
	void setCanMoveLeft(bool input) { m_canMoveLeft = input; }
	void setCanMoveUp(bool input) { m_canMoveUp = input; }
	void setCanMoveDown(bool input) { m_canMoveDown = input; }

protected:
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;
	std::string m_textureID;

	bool m_bFlipHorizontal;

	bool m_canMoveRight;
	bool m_canMoveLeft;
	bool m_canMoveUp;
	bool m_canMoveDown;
};