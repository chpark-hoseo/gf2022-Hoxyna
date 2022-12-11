#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.h"
#include "InputHandler.h"

#include "Player.h"
#include "FallingObject.h"

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
    initTime = clock();
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

    if (!TheTextureManager::Instance()->load("Assets/potion_red.png", "potion_red", m_pRenderer))
    {
        return false;
    }

    if (!TheTextureManager::Instance()->load("Assets/potion_green.png", "potion_green", m_pRenderer))
    {
        return false;
    }

    if (!TheTextureManager::Instance()->load("Assets/potion_yellow.png", "potion_yellow", m_pRenderer))
    {
        return false;
    }

    m_player = new Player(new LoaderParams(SCREEN_WIDTH/2, SCREEN_HEIGHT-40, 45, 40, "kirbyEdit-alpha"));
    m_player->setHp(3);
    printf("playerHp: %d\n", m_player->getHp());
    m_player->setInvincible(false);
    m_player->setBoosted(false);

    return true;
}

void Game::update()
{
    timer = (clock() - initTime) / 1000;
    m_player->setTimer(timer);

    // level
    int level = (clock() - initTime) / 10000;

    // createDuration(ms)
    createDuration = 1000 - level * 100;
    if (createDuration < 300)
        createDuration = 300;

    term = (clock() - initTime) / createDuration;
    if (term > termSaved)
    {
        termSaved = term;
        maxBlockCount++;
    }

    //printf("%d\n", timer);

    // createBlock
    if (curBlockCount < maxBlockCount)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 9);
        switch (dis(gen))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            m_fallingBlocks.push_back(new FallingObject(new LoaderParams(48 * dis(gen), 0, 48, 48, "wall_1")));
            break;
        case 9:
            switch (dis(gen))
            {
            case 0:
            case 1:
            case 2:
            case 3:
                m_potionReds.push_back(new FallingObject(new LoaderParams(48 * dis(gen), 0, 48, 48, "potion_red")));
                break;
            case 4:
            case 5:
            case 6:
                m_potionGreens.push_back(new FallingObject(new LoaderParams(48 * dis(gen), 0, 48, 48, "potion_green")));
                break;
            case 7:
            case 8:
            case 9:
                m_potionYellows.push_back(new FallingObject(new LoaderParams(48 * dis(gen), 0, 48, 48, "potion_yellow")));
                break;
            }
            break;
        }
        curBlockCount++;
    }

    m_player->update();
    for (int i = 0; i < m_fallingBlocks.size(); i++)
    {
        m_fallingBlocks[i]->update();
    }
    for (int i = 0; i < m_potionReds.size(); i++)
    {
        m_potionReds[i]->update();
    }
    for (int i = 0; i < m_potionGreens.size(); i++)
    {
        m_potionGreens[i]->update();
    }
    for (int i = 0; i < m_potionYellows.size(); i++)
    {
        m_potionYellows[i]->update();
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

    for (int i = 0; i < m_fallingBlocks.size(); i++)
    {
        if (m_player->getPosition().getX() + m_player->getWidth() >= m_fallingBlocks[i]->getPosition().getX()
            && m_player->getPosition().getY() + m_player->getHeight() >= m_fallingBlocks[i]->getPosition().getY()
            && m_player->getPosition().getX() <= m_fallingBlocks[i]->getPosition().getX() + m_fallingBlocks[i]->getWidth()
            && m_player->getPosition().getY() <= m_fallingBlocks[i]->getPosition().getY() + m_fallingBlocks[i]->getHeight())
        {
            printf("rect intersect\n");
            m_fallingBlocks.erase(m_fallingBlocks.begin() + i);
            if (m_player->getInvincible() == false)
            {
                system("cls");
                m_player->setHp(m_player->getHp() - 1);
                printf("playerHp: %d\n", m_player->getHp());
            }
        }
    }

    for (int i = 0; i < m_potionReds.size(); i++)
    {
        if (m_player->getPosition().getX() + m_player->getWidth() >= m_potionReds[i]->getPosition().getX()
            && m_player->getPosition().getY() + m_player->getHeight() >= m_potionReds[i]->getPosition().getY()
            && m_player->getPosition().getX() <= m_potionReds[i]->getPosition().getX() + m_potionReds[i]->getWidth()
            && m_player->getPosition().getY() <= m_potionReds[i]->getPosition().getY() + m_potionReds[i]->getHeight())
        {
            system("cls");
            printf("red potion: increase hp\n");
            m_potionReds.erase(m_potionReds.begin() + i);
            m_player->setHp(m_player->getHp() + 1);
            printf("playerHp: %d\n", m_player->getHp());
        }
    }

    for (int i = 0; i < m_potionGreens.size(); i++)
    {
        if (m_player->getPosition().getX() + m_player->getWidth() >= m_potionGreens[i]->getPosition().getX()
            && m_player->getPosition().getY() + m_player->getHeight() >= m_potionGreens[i]->getPosition().getY()
            && m_player->getPosition().getX() <= m_potionGreens[i]->getPosition().getX() + m_potionGreens[i]->getWidth()
            && m_player->getPosition().getY() <= m_potionGreens[i]->getPosition().getY() + m_potionGreens[i]->getHeight())
        {
            printf("green potion: speed up for 10sec\n");
            m_potionGreens.erase(m_potionGreens.begin() + i);
            m_player->setBoosted(true);
            m_player->setBooEndTime(timer + 10);
        }
    }

    for (int i = 0; i < m_potionYellows.size(); i++)
    {
        if (m_player->getPosition().getX() + m_player->getWidth() >= m_potionYellows[i]->getPosition().getX()
            && m_player->getPosition().getY() + m_player->getHeight() >= m_potionYellows[i]->getPosition().getY()
            && m_player->getPosition().getX() <= m_potionYellows[i]->getPosition().getX() + m_potionYellows[i]->getWidth()
            && m_player->getPosition().getY() <= m_potionYellows[i]->getPosition().getY() + m_potionYellows[i]->getHeight())
        {
            printf("yellow potion: invincible for 5sec\n");
            m_potionYellows.erase(m_potionYellows.begin() + i);
            m_player->setInvincible(true);
            m_player->setInvEndTime(timer + 5);
        }
    }
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    m_player->draw();
    for (int i = 0; i < m_fallingBlocks.size(); i++)
    {
        m_fallingBlocks[i]->draw();
    }
    for (int i = 0; i < m_potionReds.size(); i++)
    {
        m_potionReds[i]->draw();
    }
    for (int i = 0; i < m_potionGreens.size(); i++)
    {
        m_potionGreens[i]->draw();
    }
    for (int i = 0; i < m_potionYellows.size(); i++)
    {
        m_potionYellows[i]->draw();
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
    TheTextureManager::Instance()->destroyTexture("potion_red");
    TheTextureManager::Instance()->destroyTexture("potion_green");
    TheTextureManager::Instance()->destroyTexture("potion_yellow");

    SDL_Quit();
}