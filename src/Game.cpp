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

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

TextureManager* TextureManager::s_pInstance = 0;
Game* Game::s_pInstance = 0;

SDL_Rect Game::camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

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

    m_player = new Player(new LoaderParams(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 45, 40, "kirbyEdit-alpha"));

    m_gameObjects.push_back(new FallingBlock(new LoaderParams(200, 300, 45, 40, "wall_1")));
    m_gameObjects.push_back(new FallingBlock(new LoaderParams(245, 300, 45, 40, "wall_1")));
    m_gameObjects.push_back(new FallingBlock(new LoaderParams(290, 300, 45, 40, "wall_1")));
    m_gameObjects.push_back(new FallingBlock(new LoaderParams(335, 260, 45, 40, "wall_1")));

    return true;
}

void Game::update()
{
    camera.x = m_player->getPosition().getX() - SCREEN_WIDTH / 2;
    camera.y = m_player->getPosition().getY() - SCREEN_HEIGHT / 2;

    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > camera.w)
        camera.x = camera.w;
    if (camera.y > camera.h)
        camera.y = camera.h;

    printf("camera.x: %f\n", camera.x);
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

    if (SCREEN_HEIGHT <= m_player->getPosition().getY() + m_player->getHeight()) {
        m_player->setCanMoveDown(false);
    }
    else {
        m_player->setCanMoveDown(true);
    }

    if (0 >= m_player->getPosition().getY()) {
        m_player->setCanMoveUp(false);
    }
    else {
        m_player->setCanMoveUp(true);
    }

    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        //if (m_player->getPosition().getX() + m_player->getWidth() >= m_gameObjects[i]->getPosition().getX()
        //    && m_player->getPosition().getY() + m_player->getHeight() >= m_gameObjects[i]->getPosition().getY()
        //    && m_player->getPosition().getX() <= m_gameObjects[i]->getPosition().getX() + m_gameObjects[i]->getWidth()
        //    && m_player->getPosition().getY() <= m_gameObjects[i]->getPosition().getY() + m_gameObjects[i]->getHeight())
        //{
        //    printf("rect intersect\n");
        //    if (m_player->getPosition().getX() + m_player->getWidth() == m_gameObjects[i]->getPosition().getX())
        //    {
        //        // block right move
        //        m_player->setCanMoveRight(false);
        //    
        //        printf("block move R\n");
        //    }
        //    if (m_player->getPosition().getX() == m_gameObjects[i]->getPosition().getX() + m_gameObjects[i]->getWidth())
        //    {
        //        // block left move
        //        m_player->setCanMoveLeft(false);
        //    
        //        printf("block move L\n");
        //    }
        //    if (m_player->getPosition().getY() + m_player->getHeight() == m_gameObjects[i]->getPosition().getY())
        //    {
        //        // block down move
        //        m_player->setCanMoveDown(false);
        //    
        //        printf("block move D\n");
        //    }
        //    if (m_player->getPosition().getY() == m_gameObjects[i]->getPosition().getY() + m_gameObjects[i]->getHeight())
        //    {
        //        // block up move
        //        m_player->setCanMoveUp(false);
        //    
        //        printf("block move U\n");
        //    }
        //}
        //else
        //{
        //    m_player->setCanMoveLeft(true);
        //    m_player->setCanMoveRight(true);
        //    m_player->setCanMoveDown(true);
        //    m_player->setCanMoveUp(true);
        //    printf("NO BLOCKS\n");
        //}

        if (m_player->getPosition().getX() + m_player->getWidth() >= m_gameObjects[i]->getPosition().getX()
            && m_player->getPosition().getY() + m_player->getHeight() >= m_gameObjects[i]->getPosition().getY()
            && m_player->getPosition().getX() <= m_gameObjects[i]->getPosition().getX() + m_gameObjects[i]->getWidth()
            && m_player->getPosition().getY() <= m_gameObjects[i]->getPosition().getY() + m_gameObjects[i]->getHeight())
        {
            //printf("rect intersect\n");
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

        //// Fake Camera Move
        //if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
        //    m_gameObjects[i]->setVelocityX(2);
        //}
        //else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
        //    m_gameObjects[i]->setVelocityX(-2);
        //}
        //else
        //    m_gameObjects[i]->setVelocityX(0);
        //if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) {
        //    m_gameObjects[i]->setVelocityY(-2);
        //}
        //else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) {
        //    m_gameObjects[i]->setVelocityY(2);
        //}
        //else
        //    m_gameObjects[i]->setVelocityY(0);
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