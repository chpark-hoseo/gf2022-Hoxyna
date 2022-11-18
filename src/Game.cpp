#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.h"
#include "InputHandler.h"

#include "Player.h"
//#include "Monster.h"
#include "Enemy.h"

#include <algorithm>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

TextureManager* TextureManager::s_pInstance = 0;
Game* Game::s_pInstance = 0;

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

    if (!TheTextureManager::Instance()->load("Assets/kirbyEdit-alpha.png", "kirbyEdit-alpha", m_pRenderer))
    {
        return false;
    }

    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 45, 40, "kirbyEdit-alpha")));

    return true;
}

void Game::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }

    //// rect intersect
    //for (int i = 0; i < collisionCount; i++)
    //{
    //    if (kirbyX + 45 >= xywh[i].x
    //        && kirbyY + 40 >= xywh[i].y
    //        && kirbyX <= xywh[i].x + xywh[i].w
    //        && kirbyY <= xywh[i].y + xywh[i].h)
    //    {
    //        if (kirbyX + 45 == xywh[i].x)
    //            m_bMoveRight = false;
    //        if (kirbyX == xywh[i].x + xywh[i].w)
    //            m_bMoveLeft = false;
    //        if (kirbyY + 40 == xywh[i].y)
    //            m_bMoveDown = false;
    //        if (kirbyY == xywh[i].y + xywh[i].h)
    //            m_bMoveUp = false;
    //    }
    //}
    for (int i = 1; i < m_gameObjects.size(); i++)
    {
        // if gameObject0 (Player) intersects other gameObjects
        if (m_gameObjects[0]->getPosition().getX() + m_gameObjects[0]->getWidth() >= m_gameObjects[i]->getPosition().getX()
            && m_gameObjects[0]->getPosition().getY() + m_gameObjects[0]->getHeight() >= m_gameObjects[i]->getPosition().getY()
            && m_gameObjects[0]->getPosition().getX() <= m_gameObjects[i]->getPosition().getX() + m_gameObjects[i]->getWidth()
            && m_gameObjects[0]->getPosition().getY() <= m_gameObjects[i]->getPosition().getY() + m_gameObjects[i]->getHeight())
        {
            if (m_gameObjects[0]->getPosition().getX() + m_gameObjects[0]->getWidth() == m_gameObjects[i]->getPosition().getX())
            {
                // block right move
                m_gameObjects[0]->setCanMoveRight(false);
            }
        }
    }
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }

    SDL_RenderPresent(m_pRenderer);

}

bool Game::running()
{
    return m_bRunning;
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();
}

void Game::clean()
{
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    TheTextureManager::Instance()->destroyTexture("animate");

    SDL_Quit();
}