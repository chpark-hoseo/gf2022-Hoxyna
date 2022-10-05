#pragma once // 과제 2. 전처리기 추가하기
// 과제3. 링커->시스템->하위 시스템: 콘솔 설정 완료

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

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

    SDL_Texture* m_pTexture;
    SDL_Rect m_sourceRectangle;
    SDL_Rect m_destinationRectangle;
	SDL_Texture* m_pTexture2;
	SDL_Rect m_sourceRectangle2;
	SDL_Rect m_destinationRectangle2;
	SDL_Texture* m_pTexture3;
	SDL_Rect m_sourceRectangle3;
	SDL_Rect m_destinationRectangle3;

	bool m_bRunning;
	bool m_moveRight;
	bool m_input;
};