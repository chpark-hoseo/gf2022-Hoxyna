#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;
bool g_bRunning = false;

bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
void input();
void update();
void render();

int main(int argc, char* args[])
{
	srand(time(NULL));

	if (init("Breaking Up HelloSDL",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480,
		SDL_WINDOW_SHOWN))
	{
		g_bRunning = true;
	}
	else
	{
		return 1;
	}

	while (g_bRunning)
	{
		input();
		update();
		render();
	}

	SDL_Quit();
	return 0;
}

bool init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {

		g_pWindow = SDL_CreateWindow(
			title, xpos, ypos, height, width, flags);

		if (g_pWindow != 0) {
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
		}

	}
	else {
		return false;
	}

	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);

	return true;
}

void input()
{
	
}

void update()
{
	g_bRunning = rand() % 2;
	SDL_SetRenderDrawColor(g_pRenderer, rand() % 256, rand() % 256, rand() % 256, 255);
	SDL_Delay(1000);
}

void render()
{
	SDL_RenderClear(g_pRenderer); // 백버퍼 초기화
	SDL_RenderPresent(g_pRenderer); // 백버퍼 스위치
}