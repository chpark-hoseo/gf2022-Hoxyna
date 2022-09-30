#include "Game.h"
#include <SDL2/SDL_image.h>
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
    SDL_Surface* pTempSurface = IMG_Load("Assets/animate-alpha.png");
    if (pTempSurface == NULL) return false; // PNG �ҷ����� ����

    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

    m_sourceRectangle.x = 0;
    m_sourceRectangle.y = 0;

    m_sourceRectangle.w = 128;
    //m_sourceRectangle.h = 40;
    
    m_destinationRectangle.x = 0;
    m_destinationRectangle.y = 0;
    
    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;

    // ����1
    SDL_Surface* pTempSurface2 = IMG_Load("Assets/animate-alpha.png");
    if (pTempSurface2 == NULL) return false; // PNG �ҷ����� ����

    m_pTexture2 = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface2);

    SDL_FreeSurface(pTempSurface2);

    SDL_QueryTexture(m_pTexture2, NULL, NULL, &m_sourceRectangle2.w, &m_sourceRectangle2.h);

    m_sourceRectangle2.x = 0;
    m_sourceRectangle2.y = 0;

    m_sourceRectangle2.w = 128;
    //m_sourceRectangle2.h = 40;

    m_destinationRectangle2.x = 100;
    m_destinationRectangle2.y = 100;

    m_destinationRectangle2.w = m_sourceRectangle2.w;
    m_destinationRectangle2.h = m_sourceRectangle2.h;
    
    return true;
}

void Game::update()
{
    m_sourceRectangle.x = 128 * ((SDL_GetTicks() / 100) % 6);
    // ����1
    m_sourceRectangle2.x = 128 * ((SDL_GetTicks() / 200) % 6);
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
    // ����1
    SDL_RenderCopy(m_pRenderer, m_pTexture2, &m_sourceRectangle2, &m_destinationRectangle2);

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

    SDL_DestroyTexture(m_pTexture);
    // ����1
    SDL_DestroyTexture(m_pTexture2);

    SDL_Quit();
}