#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.h"

#include <algorithm>

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

    if (!TheTextureManager::Instance()->load("Assets/animate-alpha.png", "animate", m_pRenderer))
    {
        return false;
    }

    GameObject* m_go = new GameObject();
    GameObject* m_player = new Player();
    Monster* m_mon1 = new Monster();

    m_go->load(100, 100, 128, 82, "animate");
    m_player->load(300, 300, 128, 82, "animate");
    m_mon1->load(100, 500, 128, 82, "animate");
    m_mon1->set_speed(3);

    m_gameObjects.push_back(m_go);
    m_gameObjects.push_back(m_player);
    m_monsters.push_back(m_mon1);

    return true;
}

void Game::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
    for (int i = 0; i < m_monsters.size(); i++)
    {
        m_monsters[i]->update();
    }
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw(m_pRenderer);
    }
    for (int i = 0; i < m_monsters.size(); i++)
    {
        m_monsters[i]->draw(m_pRenderer);
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
            break;
        case SDL_KEYUP:
            printf("%d 키가 때졌어요!\n", event.key.keysym.sym);
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
    TheTextureManager::Instance()->destroyTexture("animate");

    SDL_Quit();
}