#pragma once // ���� 2. ��ó���� �߰��ϱ�
// ����3. ��Ŀ->�ý���->���� �ý���: �ܼ� ���� �Ϸ�

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
	bool m_bRunning;
};

bool Game::init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        m_pWindow = SDL_CreateWindow(
            title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0) {
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if (m_pRenderer != 0) {
                SDL_SetRenderDrawColor(
                    m_pRenderer, 255, 255, 255, 255);
            }
            else {
                return false; // ������ ���� ����
            }
        }
        else {
            return false; // ������ ���� ����
        }
    }
    else {
        return false; // SDL �ʱ�ȭ ����
    }

    m_bRunning = true;
    return true;
}

void Game::update()
{

}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);
    SDL_RenderPresent(m_pRenderer);
}

bool Game::running()
{
    return m_bRunning;
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) // ���� 1. if �� while �� �ٲٴ� ������ ����ؼ� event���� Ȯ���ϰ�
        // event.type �� �������� �̺�Ʈ�� ���� �� while���� ������������ �ϱ� ����. 
        // if �� ����ϸ� main���� �� ������ �ٽ� �˻�������, ���� ������ ������ �� ����.
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_bRunning = false;
            break;
        case SDL_KEYDOWN:
            printf("%d Ű�� ���Ⱦ��!\n", event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            printf("%d Ű�� �������!\n", event.key.keysym.sym);
            break;
        default:
            break;
        }
    }
}

void Game::clean()
{
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}