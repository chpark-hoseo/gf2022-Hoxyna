#include "Game.h"
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640


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

    // �ǽ�
    m_textureManager.load("Assets/animate-alpha.png", "animate", m_pRenderer);
    // ����1
    m_textureManager.load("Assets/kirbyEdit.bmp", "kirby", m_pRenderer);
    
    return true;
}

void Game::update()
{
    m_currentFrame = ((SDL_GetTicks() / 100) % 6);
    // ����1
    m_kirbyFrame_walk = ((SDL_GetTicks() / 100) % 10);
    m_kirbyFrame_idle = ((SDL_GetTicks() / 1000) % 2);
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    m_textureManager.draw("animate", 0, 0, 128, 82, m_pRenderer);
    m_textureManager.drawFrame("animate", 100, 100, 128, 82, 0, m_currentFrame, m_pRenderer);
    // ����1
    if (m_isWalking)
        m_textureManager.drawFrame("kirby", 200, 200, 45, 40, 0, m_kirbyFrame_walk, m_pRenderer);
    else
        m_textureManager.drawFrame("kirby", 200, 200, 45, 40, 1, m_kirbyFrame_idle, m_pRenderer);

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
            m_bRunning = false;
            break;
        case SDL_KEYDOWN:
            printf("%d Ű�� ���Ⱦ��!\n", event.key.keysym.sym);
            m_isWalking = true;
            break;
        case SDL_KEYUP:
            printf("%d Ű�� �������!\n", event.key.keysym.sym);
            m_isWalking = false;
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
    m_textureManager.destroyTexture("animate");
    m_textureManager.destroyTexture("kirby");

    SDL_Quit();
}