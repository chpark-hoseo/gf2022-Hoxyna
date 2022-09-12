#include <SDL2/SDL.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {

		g_pWindow = SDL_CreateWindow("Game Framework", // 윈도우 이름 바꾸기
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1024, 768, // 윈도우 크기 바꾸기
			SDL_WINDOW_BORDERLESS | SDL_WINDOW_MAXIMIZED); // 과제2. 윈도우 생성 다르게 해보기

		if (g_pWindow != 0)
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
		else
			return 1;
	}

	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 255, 0); // 과제1. 윈도우 바탕화면 파란색
	SDL_RenderClear(g_pRenderer);
	SDL_RenderPresent(g_pRenderer);

	SDL_Delay(10000); // 과제3. 10초후 종료
	SDL_Quit();

	return 0;
}