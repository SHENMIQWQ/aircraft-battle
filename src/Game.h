#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include "SDL.h"

class Game
{
public:
    Game();
    ~Game();

    void run();
    void on_render();
    void on_event(SDL_Event& e);

    void on_update();
    void on_enter();
    void on_exit();
    void changeScene(Scene* scene);
private:
    bool isRunning = true;
    Scene* currentScene = nullptr;
};
#endif


