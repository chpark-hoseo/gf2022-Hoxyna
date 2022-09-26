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

    SDL_Surface* pTempSurface = SDL_LoadBMP("Assets/rider.bmp");
    if (pTempSurface == NULL) return false; // BMP �ҷ����� ����

    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;

    m_destinationRectangle.x = m_sourceRectangle.x = 0;
    m_destinationRectangle.y = m_sourceRectangle.y = 0;

    // ���� 2
    SDL_Surface* pTempSurface2 = SDL_LoadBMP("Assets/rider.bmp");
    if (pTempSurface2 == NULL) return false; // BMP �ҷ����� ����

    m_pTexture2 = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface2);

    SDL_FreeSurface(pTempSurface2);

    SDL_QueryTexture(m_pTexture2, NULL, NULL, &m_sourceRectangle2.w, &m_sourceRectangle2.h);

    m_destinationRectangle2.w = m_sourceRectangle2.w;
    m_destinationRectangle2.h = m_sourceRectangle2.h;

    m_destinationRectangle2.x = m_sourceRectangle2.x = 0;
    m_destinationRectangle2.y = m_sourceRectangle2.y = 0;


    return true;
}

void Game::update()
{
    // ���� 1
    if (m_destinationRectangle.x == 0)
        m_moveRight = true;
    if (m_destinationRectangle.x == SCREEN_WIDTH - m_sourceRectangle.w)
        m_moveRight = false;

    if (m_moveRight)
        m_destinationRectangle.x++;
    else
        m_destinationRectangle.x--;

    SDL_Delay(5);
}

void Game::render()
{
    // ���� 4
    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(m_pRenderer);

    SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(m_pRenderer, &fillRect);

    SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
    SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(m_pRenderer, &outlineRect);

    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);
    SDL_RenderDrawLine(m_pRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 0, 255);
    for (int i = 0; i < SCREEN_HEIGHT; i += 4)
    {
        SDL_RenderDrawPoint(m_pRenderer, SCREEN_WIDTH / 2, i);
    }

    // ���� 1, 2
    //SDL_RenderClear(m_pRenderer);
    //SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
    //SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle2, &m_destinationRectangle2);

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
    // ���� 3
    SDL_DestroyTexture(m_pTexture);
    SDL_DestroyTexture(m_pTexture2);

    SDL_Quit();
}