#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "SDLGameObject.h"
#include "Player.h"

class Game
{
private:
	Game() {}
	~Game() {}
	static Game* s_pInstance;

public:
	static Game* Instance() {
		if (s_pInstance == 0)
			s_pInstance = new Game();
		return s_pInstance;
	}
	SDL_Renderer* getRenderer() const { return m_pRenderer; }

	bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
	void update();
    void render();
	bool running();
	void handleEvents();
	void clean();
	void quit() { m_bRunning = false; }

	//static SDL_Rect camera;

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	int m_currentFrame;

	bool m_bRunning;

	Player* m_player;
	std::vector<SDLGameObject*> m_fallingBlocks;
	std::vector<SDLGameObject*> m_potionReds;
	std::vector<SDLGameObject*> m_potionGreens;
	std::vector<SDLGameObject*> m_potionYellows;

	int timer;
	int initTime;
	int term, termSaved;
	int createDuration;
	int maxBlockCount;
	int curBlockCount;

	bool playerRender;
};
typedef Game TheGame;