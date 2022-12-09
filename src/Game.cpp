#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.h"
#include "InputHandler.h"

#include "Player.h"
#include "FallingBlock.h"

#include <algorithm>

#include <ctime>
#include <random>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

TextureManager* TextureManager::s_pInstance = 0;
Game* Game::s_pInstance = 0;

//SDL_Rect Game::camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

bool Game::init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
    timer = clock();
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        m_pWindow = SDL_CreateWindow(
            title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0) {
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if (m_pRenderer != 0) {
                SDL_SetRenderDrawColor(
                    m_pRenderer, 0, 0, 0, 255);
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

    m_player = new Player(new LoaderParams(SCREEN_WIDTH/2, SCREEN_HEIGHT-40, 45, 40, "kirbyEdit-alpha"));
    playerRender = true;

    //// map
    //int world[10][10] = {
    //    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    //    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    //    { 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
    //    { 1, 1, 1, 0, 0, 0, 0, 1, 0, 1 },
    //    { 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
    //    { 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
    //    { 1, 0, 1, 0, 1, 0, 0, 1, 0, 1 },
    //    { 1, 0, 1, 0, 1, 1, 1, 1, 1, 1 },
    //    { 1, 0, 0, 0, 0, 0, 0, 0, 2, 1 },
    //    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    //};
    //
    //int x = 0;
    //int y = 0;
    //
    //for (int i = 0; i < 10; i++)
    //{
    //    for (int j = 0; j < 10; j++)
    //    {
    //        if (world[i][j] == 1)
    //        {
    //            m_gameObjects.push_back(new FallingBlock(new LoaderParams(x, y, 50, 50, "wall_1")));
    //        }
    //        x += 50;
    //    }
    //    x = 0;
    //    y += 50;
    //}

    //m_gameObjects.push_back(new FallingBlock(new LoaderParams(48 * 5, 0, 48, 40, "wall_1")));
    //m_gameObjects.push_back(new FallingBlock(new LoaderParams(48 * 6, 0, 48, 40, "wall_1")));
    //m_gameObjects.push_back(new FallingBlock(new LoaderParams(48 * 7, 40, 48, 40, "wall_1")));
    //m_gameObjects.push_back(new FallingBlock(new LoaderParams(48 * 9, 0, 48, 40, "wall_1")));

    return true;
}

void Game::update()
{
    // level
    int level = (clock() - timer) / 10000;

    // createDuration(ms)
    createDuration = 1000 - level * 100;
    if (createDuration < 300)
        createDuration = 300;

    term = (clock() - timer) / createDuration;
    if (term > termSaved)
    {
        termSaved = term;
        maxBlockCount++;
    }

    printf("%d\n", createDuration);

    // createBlock
    if (curBlockCount < maxBlockCount)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 9);
        m_gameObjects.push_back(new FallingBlock(new LoaderParams(48 * dis(gen), 0, 48, 48, "wall_1")));
        curBlockCount++;
    }

    //camera.x = m_player->getPosition().getX() - SCREEN_WIDTH / 2;
    //camera.y = m_player->getPosition().getY() - SCREEN_HEIGHT / 2;

    //if (camera.x < 0)
    //    camera.x = 0;
    //if (camera.y < 0)
    //    camera.y = 0;
    //if (camera.x > camera.w)
    //    camera.x = camera.w;
    //if (camera.y > camera.h)
    //    camera.y = camera.h;

    //printf("camera.x: %d\n", camera.x);
    //printf("camera.y: %f\n", m_player->getPosition().getY() - SCREEN_HEIGHT / 2);

    m_player->update();
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }

    if (SCREEN_WIDTH <= m_player->getPosition().getX() + m_player->getWidth()) {
        m_player->setCanMoveRight(false);
    }
    else {
        m_player->setCanMoveRight(true);
    }

    if (0 >= m_player->getPosition().getX()) {
        m_player->setCanMoveLeft(false);
    }
    else {
        m_player->setCanMoveLeft(true);
    }

    //if (SCREEN_HEIGHT <= m_player->getPosition().getY() + m_player->getHeight()) {
    //    m_player->setCanMoveDown(false);
    //}
    //else {
    //    m_player->setCanMoveDown(true);
    //}
    //
    //if (0 >= m_player->getPosition().getY()) {
    //    m_player->setCanMoveUp(false);
    //}
    //else {
    //    m_player->setCanMoveUp(true);
    //}

    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        if (m_player->getPosition().getX() + m_player->getWidth() >= m_gameObjects[i]->getPosition().getX()
            && m_player->getPosition().getY() + m_player->getHeight() >= m_gameObjects[i]->getPosition().getY()
            && m_player->getPosition().getX() <= m_gameObjects[i]->getPosition().getX() + m_gameObjects[i]->getWidth()
            && m_player->getPosition().getY() <= m_gameObjects[i]->getPosition().getY() + m_gameObjects[i]->getHeight())
        {
            printf("rect intersect\n");
            m_gameObjects.erase(m_gameObjects.begin() + i);
            playerRender = false;
            //if (m_player->getPosition().getX() + m_player->getWidth() == m_gameObjects[i]->getPosition().getX())
            //{
            //    // block right move
            //    m_player->setCanMoveRight(false);
            //
            //    printf("block move R\n");
            //}
            //if (m_player->getPosition().getX() == m_gameObjects[i]->getPosition().getX() + m_gameObjects[i]->getWidth())
            //{
            //    // block left move
            //    m_player->setCanMoveLeft(false);
            //
            //    printf("block move L\n");
            //}
            //if (m_player->getPosition().getY() + m_player->getHeight() == m_gameObjects[i]->getPosition().getY())
            //{
            //    // block down move
            //    m_player->setCanMoveDown(false);
            //
            //    printf("block move D\n");
            //}
            //if (m_player->getPosition().getY() == m_gameObjects[i]->getPosition().getY() + m_gameObjects[i]->getHeight())
            //{
            //    // block up move
            //    m_player->setCanMoveUp(false);
            //
            //    printf("block move U\n");
            //}
        }
        else
        {
            //printf("NO BLOCKS\n");
            //m_player->setCanMoveLeft(true);
            //m_player->setCanMoveRight(true);
            //m_player->setCanMoveDown(true);
            //m_player->setCanMoveUp(true);
        }
    }
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    if (playerRender)
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