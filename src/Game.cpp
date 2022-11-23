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

    if (!TheTextureManager::Instance()->load("Assets/wall_1.png", "wall_1", m_pRenderer))
    {
        return false;
    }

    m_player = new Player(new LoaderParams(100, 100, 45, 40, "kirbyEdit-alpha"));
    m_gameObjects.push_back(new Enemy(new LoaderParams(200, 200, 45, 40, "wall_1")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(245, 245, 45, 40, "wall_1")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(290, 200, 45, 40, "wall_1")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(335, 200, 45, 40, "wall_1")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(370, 200, 45, 40, "wall_1")));

    return true;
}

void Game::update()
{
    m_player->update();
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
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        if (m_player->getPosition().getX() + m_player->getWidth() >= m_gameObjects[i]->getPosition().getX()
            && m_player->getPosition().getY() + m_player->getHeight() >= m_gameObjects[i]->getPosition().getY()
            && m_player->getPosition().getX() <= m_gameObjects[i]->getPosition().getX() + m_gameObjects[i]->getWidth()
            && m_player->getPosition().getY() <= m_gameObjects[i]->getPosition().getY() + m_gameObjects[i]->getHeight())
        {
            if (m_player->getPosition().getX() + m_player->getWidth() == m_gameObjects[i]->getPosition().getX())
            {
                // block right move
                m_player->setCanMoveRight(false);
                m_player->setCanMoveLeft(true);
                m_player->setCanMoveDown(true);
                m_player->setCanMoveUp(true);

                printf("block move R\n");
            }
            if (m_player->getPosition().getX() == m_gameObjects[i]->getPosition().getX() + m_gameObjects[i]->getWidth())
            {
                // block left move
                m_player->setCanMoveRight(true);
                m_player->setCanMoveLeft(false);
                m_player->setCanMoveDown(true);
                m_player->setCanMoveUp(true);

                printf("block move L\n");
            }
            if (m_player->getPosition().getY() + m_player->getHeight() == m_gameObjects[i]->getPosition().getY())
            {
                // block down move
                m_player->setCanMoveRight(true);
                m_player->setCanMoveLeft(true);
                m_player->setCanMoveDown(false);
                m_player->setCanMoveUp(true);

                printf("block move D\n");
            }
            if (m_player->getPosition().getY() == m_gameObjects[i]->getPosition().getY() + m_gameObjects[i]->getHeight())
            {
                // block up move
                m_player->setCanMoveRight(true);
                m_player->setCanMoveLeft(true);
                m_player->setCanMoveDown(true);
                m_player->setCanMoveUp(false);

                printf("block move U\n");
            }
        }
        else
        {
            m_player->setCanMoveRight(true);
            m_player->setCanMoveLeft(true);
            m_player->setCanMoveDown(true);
            m_player->setCanMoveUp(true);
        }
    }
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    m_player->draw();
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