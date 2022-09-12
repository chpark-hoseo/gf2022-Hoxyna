#include <SDL2/SDL.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {

		g_pWindow = SDL_CreateWindow("Game Framework", // ������ �̸� �ٲٱ�
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1024, 768, // ������ ũ�� �ٲٱ�
			SDL_WINDOW_BORDERLESS | SDL_WINDOW_MAXIMIZED); // ����2. ������ ���� �ٸ��� �غ���

		if (g_pWindow != 0)
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
		else
			return 1;
	}

	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 255, 0); // ����1. ������ ����ȭ�� �Ķ���
	SDL_RenderClear(g_pRenderer);
	SDL_RenderPresent(g_pRenderer);

	SDL_Delay(10000); // ����3. 10���� ����
	SDL_Quit();

	return 0;
}