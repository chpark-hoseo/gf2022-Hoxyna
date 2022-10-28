#pragma once
#include <SDL2/SDL.h>
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"

class Game
{
public:
	Game() {}
	~Game() {}

	bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
	void update();
    void render();
	bool running();
	void handleEvents();
	void clean();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	int m_currentFrame;

	bool m_bRunning;

	GameObject m_go;
	Player m_player;

	Monster m_mon1;
	Monster m_mon2;
};