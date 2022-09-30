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

    // �ǽ�
    //SDL_Surface* pTempSurface = SDL_LoadBMP("Assets/animate.bmp");
    // ����1
    SDL_Surface* pTempSurface = SDL_LoadBMP("Assets/kerbyEdit.bmp");
    if (pTempSurface == NULL) return false; // BMP �ҷ����� ����

    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

    m_sourceRectangle.x = 0;
    m_sourceRectangle.y = 0;

    m_sourceRectangle.w = 45;
    m_sourceRectangle.h = 40;
    
    m_destinationRectangle.x = 0;
    m_destinationRectangle.y = 0;
    
    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;

    // ����2
    //SDL_Surface* pTempSurface2 = SDL_LoadBMP("Assets/kerbyEdit.bmp");
    //if (pTempSurface2 == NULL) return false; // BMP �ҷ����� ����
    //
    //m_pTexture2 = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface2);
    //
    //SDL_FreeSurface(pTempSurface2);
    //
    //SDL_QueryTexture(m_pTexture2, NULL, NULL, &m_sourceRectangle2.w, &m_sourceRectangle2.h);
    //
    //m_sourceRectangle2.x = 0;
    //m_sourceRectangle2.y = 0;
    //
    //m_sourceRectangle2.w = 45;
    //m_sourceRectangle2.h = 40;
    //
    //m_destinationRectangle2.x = 100;
    //m_destinationRectangle2.y = 100;
    //
    //m_destinationRectangle2.w = m_sourceRectangle2.w;
    //m_destinationRectangle2.h = m_sourceRectangle2.h;

    // ����3 �Ϸ�
    
    // ����4 ��������: �ִϸ��̼� �¿��̵�
    m_moveRight = true;

    return true;
}

void Game::update()
{
    m_sourceRectangle.x = 45 * ((SDL_GetTicks() / 100) % 10);

    // ����2
    //m_sourceRectangle2.x = 45 * ((SDL_GetTicks() / 200) % 10);
    
    // ����4
    if (m_input)
    {
        if (m_moveRight)
            m_destinationRectangle.x++;
        else
            m_destinationRectangle.x--;
        SDL_Delay(5);
    }
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);

    // ����2
    //SDL_RenderCopy(m_pRenderer, m_pTexture2, &m_sourceRectangle2, &m_destinationRectangle2);

    // ����4
    if (m_moveRight)
        SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 0, NULL, SDL_FLIP_NONE);
    else
        SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 0, NULL, SDL_FLIP_HORIZONTAL);

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
            // ����4
            if (event.key.keysym.sym == 97)
                m_moveRight = false;
            else if (event.key.keysym.sym == 100)
                m_moveRight = true;
            m_input = true;
            break;
        case SDL_KEYUP:
            printf("%d Ű�� �������!\n", event.key.keysym.sym);
            m_input = false;
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

    // ����4
    SDL_DestroyTexture(m_pTexture2);

    SDL_Quit();
}