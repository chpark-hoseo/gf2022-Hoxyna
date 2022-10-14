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

    if (!TheTextureManager::Instance()->load("Assets/kirbyEdit.bmp", "kirby", m_pRenderer))
    {
        return false;
    }

    if (!TheTextureManager::Instance()->load("Assets/19201080.jpg", "19201080", m_pRenderer))
    {
        return false;
    }
    
    return true;
}

void Game::update()
{
    m_kirbyIdleFrame = ((SDL_GetTicks() / 500) % 2);
    m_kirbyMoveFrame = ((SDL_GetTicks() / 100) % 10);

    if (m_bInput)
    {
        if (m_bMoveRight)
            kirbyX++;
        if (m_bMoveLeft)
            kirbyX--;
        if (m_bMoveUp)
            kirbyY--;
        if (m_bMoveDown)
            kirbyY++;
    }
    SDL_Delay(5);
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    TheTextureManager::Instance()->draw("19201080", 0, 0, 1920, 1080, m_pRenderer);

    if (!m_bInput)
    {
        if (m_bLookLeft)
            TheTextureManager::Instance()->drawFrame("kirby", kirbyX, kirbyY, 45, 40, 1, m_kirbyIdleFrame, m_pRenderer, SDL_FLIP_HORIZONTAL);
        else
            TheTextureManager::Instance()->drawFrame("kirby", kirbyX, kirbyY, 45, 40, 1, m_kirbyIdleFrame, m_pRenderer, SDL_FLIP_NONE);
    }
    else
    {
        if (m_bLookLeft)
            TheTextureManager::Instance()->drawFrame("kirby", kirbyX, kirbyY, 45, 40, 0, m_kirbyMoveFrame, m_pRenderer, SDL_FLIP_HORIZONTAL);
        else
            TheTextureManager::Instance()->drawFrame("kirby", kirbyX, kirbyY, 45, 40, 0, m_kirbyMoveFrame, m_pRenderer, SDL_FLIP_NONE);
    }

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
            printf("%d 키가 눌렸어요!\n", event.key.keysym.sym);
            m_bInput = true;
            switch (event.key.keysym.sym)
            {
            case 97:
                m_bMoveLeft = true;
                m_bLookLeft = true;
                break;
            case 100:
                m_bMoveRight = true;
                m_bLookLeft = false;
                break;
            case 115:
                m_bMoveDown = true;
                break;
            case 119:
                m_bMoveUp = true;
                break;
            }
            break;
        case SDL_KEYUP:
            printf("%d 키가 때졌어요!\n", event.key.keysym.sym);
            m_bInput = false;
            switch (event.key.keysym.sym)
            {
            case 97:
                m_bMoveLeft = false;
                break;
            case 100:
                m_bMoveRight = false;
                break;
            case 115:
                m_bMoveDown = false;
                break;
            case 119:
                m_bMoveUp = false;
                break;
            }
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
    TheTextureManager::Instance()->destroyTexture("kirby");
    TheTextureManager::Instance()->destroyTexture("19201080");

    SDL_Quit();
}