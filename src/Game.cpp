#include "Game.h"

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


    return true;
}

void Game::update()
{
    // ���� 1
    if (m_destinationRectangle.x == 0)
        m_moveRight = true;
    if (m_destinationRectangle.x == 480 - m_sourceRectangle.w)
        m_moveRight = false;

    if (m_moveRight)
        m_destinationRectangle.x++;
    else
        m_destinationRectangle.x--;

    SDL_Delay(5);
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);
    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
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
    SDL_DestroyTexture(m_pTexture); // ���� 3
    SDL_Quit();
}