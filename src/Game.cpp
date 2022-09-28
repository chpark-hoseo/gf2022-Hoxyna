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
                    m_pRenderer, 255, 255, 255, 255);
            }
            else {
                return false; // 랜더러 생성 실패
            }
        }
        else {
            return false; // 윈도우 생성 실패
        }
    }
    else {
        return false; // SDL 초기화 실패
    }

    m_bRunning = true;

    SDL_Surface* pTempSurface = SDL_LoadBMP("Assets/rider.bmp");
    if (pTempSurface == NULL) return false; // BMP 불러오기 실패

    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

    // 실습
    //m_sourceRectangle.x = 0;
    //m_sourceRectangle.y = 0;
    //
    //m_sourceRectangle.w = 50;
    //m_sourceRectangle.h = 50;
    //
    //m_destinationRectangle.x = 0;
    //m_destinationRectangle.y = 0;
    //
    //m_destinationRectangle.w = 50;
    //m_destinationRectangle.h = 50;

    // 과제1
    //m_sourceRectangle.x = 0;
    //m_sourceRectangle.y = 0;
    //
    //m_sourceRectangle.w = 50;
    //m_sourceRectangle.h = 50;
    //
    //m_destinationRectangle.x = 100;
    //m_destinationRectangle.y = 100;
    //
    //m_destinationRectangle.w = 50;
    //m_destinationRectangle.h = 50;

    // 과제2
    //m_sourceRectangle.x = 50;
    //m_sourceRectangle.y = 50;
    //
    //m_sourceRectangle.w = 50;
    //m_sourceRectangle.h = 50;
    //
    //m_destinationRectangle.x = 100;
    //m_destinationRectangle.y = 100;
    //
    //m_destinationRectangle.w = 50;
    //m_destinationRectangle.h = 50;

    // 과제3
    m_sourceRectangle.x = 0;
    m_sourceRectangle.y = 0;
    
    m_destinationRectangle.x = 0;
    m_destinationRectangle.y = 0;
    
    m_destinationRectangle.w = SCREEN_WIDTH;
    m_destinationRectangle.h = SCREEN_HEIGHT;

    return true;
}

void Game::update()
{

}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    //SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
    
    // 과제4
    SDL_Point center;
    center.x = SCREEN_WIDTH / 2;
    center.y = SCREEN_HEIGHT / 2;
    SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 45, &center, SDL_FLIP_HORIZONTAL);

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
            printf("%d 키가 눌렸어요!\n", event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            printf("%d 키가 때졌어요!\n", event.key.keysym.sym);
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

    SDL_Quit();
}