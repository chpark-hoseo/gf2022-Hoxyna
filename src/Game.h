#pragma once // ���� 2. ��ó���� �߰��ϱ�
// ����3. ��Ŀ->�ý���->���� �ý���: �ܼ� ���� �Ϸ�

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.h"

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
	int m_kirbyIdleFrame;
	int m_kirbyMoveFrame;

	bool m_bRunning;
	bool m_bInput;
	bool m_bMoveLeft;
	bool m_bMoveRight;
	bool m_bLookLeft;
	int kirbyX, kirbyY;
};