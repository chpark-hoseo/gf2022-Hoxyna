#include "Game.h"
#define SCREEN_WIDTH 820
#define SCREEN_HEIGHT 820
#define collisionCount 100
#define TILE_SIZE 75

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
                    m_pRenderer, 0, 0, 255, 255);
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

    if (!TheTextureManager::Instance()->load("assets/kirbyEdit-alpha.png", "kirby", m_pRenderer))
    {
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/wall_1.png", "wall_1", m_pRenderer))
    {
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/key_silver.png", "key_silver", m_pRenderer))
    {
        return false;
    }

    kirbyX = 75;
    kirbyY = 75;

    // map
    int world[10][10] = {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
        { 1, 1, 1, 0, 0, 0, 0, 1, 0, 1 },
        { 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
        { 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
        { 1, 0, 1, 0, 1, 0, 0, 1, 0, 1 },
        { 1, 0, 1, 0, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 2, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };

    int x = 0;
    int y = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (world[i][j] == 1)
            {
                xywh[10 * i + j].x = x; xywh[10 * i + j].y = y; xywh[10 * i + j].w = TILE_SIZE; xywh[10 * i + j].h = TILE_SIZE;
            }
            else if (world[i][j] == 2)
            {
                keyXYWH.x = x; keyXYWH.y = y; keyXYWH.w = TILE_SIZE; keyXYWH.h = TILE_SIZE;
            }
            x += TILE_SIZE;
        }
        x = 0;
        y += TILE_SIZE;
    }

    return true;
}

void Game::update()
{
    // animation frame
    m_kirbyIdleFrame = ((SDL_GetTicks() / 500) % 2);
    m_kirbyMoveFrame = ((SDL_GetTicks() / 100) % 10);
    
    // rect intersect
    for (int i = 0; i < collisionCount; i++)
    {
        if (kirbyX + 45 >= xywh[i].x
            && kirbyY + 40 >= xywh[i].y
            && kirbyX <= xywh[i].x + xywh[i].w
            && kirbyY <= xywh[i].y + xywh[i].h)
        {
            if (kirbyX + 45 == xywh[i].x)
                m_bMoveRight = false;
            if (kirbyX == xywh[i].x + xywh[i].w)
                m_bMoveLeft = false;
            if (kirbyY + 40 == xywh[i].y)
                m_bMoveDown = false;
            if (kirbyY == xywh[i].y + xywh[i].h)
                m_bMoveUp = false;
        }
    }

    // player move input
    if (m_bInput)
    {
        if (m_bMoveRight)
            kirbyX++;
        if (m_bMoveLeft)
            kirbyX--;
        if (m_bMoveDown)
            kirbyY++;
        if (m_bMoveUp)
            kirbyY--;
    }
    SDL_Delay(5);
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    for (int i = 0; i < collisionCount; i++)
    {
        TheTextureManager::Instance()->draw("wall_1", xywh[i].x, xywh[i].y, xywh[i].w, xywh[i].h, m_pRenderer);
    }

    TheTextureManager::Instance()->draw("key_silver", keyXYWH.x, keyXYWH.y, keyXYWH.w, keyXYWH.h, m_pRenderer, SDL_FLIP_HORIZONTAL);

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
            //printf("%d 키가 눌렸어요!\n", event.key.keysym.sym);
            switch (event.key.keysym.sym)
            {
            case 97:
                m_bInput = true;
                m_bMoveLeft = true;
                m_bLookLeft = true;
                break;
            case 100:
                m_bInput = true;
                m_bMoveRight = true;
                m_bLookLeft = false;
                break;
            case 115:
                m_bInput = true;
                m_bMoveDown = true;
                break;
            case 119:
                m_bInput = true;
                m_bMoveUp = true;
                break;
            }
            break;
        case SDL_KEYUP:
            //printf("%d 키가 때졌어요!\n", event.key.keysym.sym);
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
    TheTextureManager::Instance()->destroyTexture("wall_1");
    TheTextureManager::Instance()->destroyTexture("key_silver");

    SDL_Quit();
}