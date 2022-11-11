#include "Game.h"
#include "InputHandler.h"
#include <iostream>

Game* g_game = 0;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
{
    if (TheGame::Instance()->init("Chapter 1",
        100, 100, 640, 480, false))
    {
        Uint32 frameStart, frameTime;
        while (TheGame::Instance()->running()) {
            frameStart = SDL_GetTicks();     // step 1 매 프레임 시작 시간 저장
            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();
            frameTime = SDL_GetTicks() - frameStart;  // step 2 입력, 업데이트, 랜더링 처리 후 소요 시간 계산
            if (frameTime < DELAY_TIME) {
                SDL_Delay((int)(DELAY_TIME - frameTime)); // step 3 소요시간이 DELAY_TIME 보다 큰 경우 해당 차이 만큼 Delay를 인위적으로 추가
            }
        }
    }
    else {
        std::cout << "game init failure " << SDL_GetError() << "\n";
        return -1;
    }
    TheGame::Instance()->clean();
    TheInputHandler::Instance()->clean();
    return 0;
}
