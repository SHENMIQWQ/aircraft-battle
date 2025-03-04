#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include <SDL.h>
#include <chrono>
#include <thread>

class Game
{
public:
    Game();
    ~Game();

    static Game* instance();
    void run();
    void on_render();
    void on_input(SDL_Event* event);

    void on_update(float delta);
    void on_enter();
    void on_exit();
    void changeScene(Scene* scene);

    SDL_Renderer* get_renderer()  const
    { return renderer; }

    SDL_FPoint get_window_size() const
    { return {(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT}; }

private:
    bool is_quit = false;
    Scene* currentScene = nullptr;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    int WINDOW_WIDTH = 600;
    int WINDOW_HEIGHT = 800;
    static Game* manager;
    int FPS = 144;
};
#endif


