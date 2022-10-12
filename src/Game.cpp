// ����1 �Ϸ�

#include "Game.h"
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

TextureManager* TextureManager::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        m_pWindow = SDL_CreateWindow(
            title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0) {
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if (m_pRenderer != 0) {
                SDL_SetRenderDrawColor(
                    m_pRenderer, 255, 0, 0, 255);
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

    if (!TheTextureManager::Instance()->load("Assets/animate-alpha.png", "animate", m_pRenderer))
    {
        return false;
    }
    
    return true;
}

void Game::update()
{
    m_currentFrame = ((SDL_GetTicks() / 100) % 6);
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    TheTextureManager::Instance()->draw("animate", 0, 0, 128, 82, m_pRenderer);

    TheTextureManager::Instance()->drawFrame("animate", 100, 100, 128, 82, 0, m_currentFrame, m_pRenderer);

    SDL_RenderPresent(m_pRenderer);
}

bool Game::running()
{
    return m_bRunning;
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
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
    TheTextureManager::Instance()->destroyTexture("animate"); // ����2 �Ϸ�

    SDL_Quit();
}

// ����3: �Ϲ� ��� ����/�Լ� �� Ŭ������ü�� �����ϸ� �� ��ü�� ��������� ������, Ŭ������ü�� ���ٸ� �Լ��� ȣ���� �� �����ϴ�. 
// ������, ���� ��� ����/�Լ� �� Ŭ������ü�� ���������ʾƵ� Ŭ���� �̸������� �Լ��� ȣ���� �� ������, 
// ���� ��� ������ �ش� Ŭ������ ��� ��ü���� �����մϴ�.

// ����4: ��ü ���� ������ �޸𸮰� �����ϱ⿡, ��ü ���� ���� �ݵ�� �̸� �ʱ�ȭ�� ���־�� �Ѵ�.