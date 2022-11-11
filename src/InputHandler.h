#pragma once

#include <SDL2/SDL.h> 
class InputHandler {
public:
    ~InputHandler() {}
    static InputHandler* Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new InputHandler();
        }
        return s_pInstance;
    }
    bool isKeyDown(SDL_Scancode key);
    void update();
    void clean() {}

private:
    InputHandler() {}
    static InputHandler* s_pInstance;
    const Uint8* m_keystates; // 키보드들의 상태를 확인할 수 있는 배열 (1: 눌림 0: 눌리지 않음)
};
typedef InputHandler TheInputHandler;