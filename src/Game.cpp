#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::run()
{
    on_update();

}

void Game::on_render()
{
}

void Game::on_event(SDL_Event &e)
{
}

void Game::on_update()
{
    while (isRunning)
    {
        SDL_Event event;
        currentScene->handleEvent(&event);
        currentScene->on_update();
        currentScene->on_render();
    }
    
}

void Game::on_enter()
{
}

void Game::on_exit()
{
}

void Game::changeScene(Scene *scene)
{
    if (currentScene != nullptr)
    {
        currentScene->on_exit();
        delete currentScene;
    }
    currentScene = scene;
    currentScene->on_enter();
}
