#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "GameObject.h"

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

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	int m_currentFrame;

	bool m_bRunning;

	std::vector<GameObject*> m_gameObjects;
};
typedef Game TheGame;