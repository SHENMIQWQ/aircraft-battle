#include "Game.h"
#include "SceneMain.h"
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std::chrono;
const nanoseconds frame_duration(1000000000 / 144);
steady_clock::time_point last_tick = steady_clock::now();

Game::Game()
{
}

Game::~Game()
{
    on_exit();
}

Game* Game::manager = nullptr;

Game *Game::instance()
{
   if(manager == nullptr)
   {
       manager = new Game();
   }
   return manager;
}

void Game::run()
{
    while (!is_quit)
    {
        SDL_Event event;
        on_input(&event);

        steady_clock::time_point frame_start = steady_clock::now();
        duration<float> delta = duration<float>(frame_start - last_tick);

        on_update(delta.count());
        on_render();

        last_tick = frame_start;
        nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frame_start);
        if (sleep_duration > nanoseconds(0))
	        std::this_thread::sleep_for(sleep_duration);
       
    }
}

void Game::on_render()
{
    SDL_RenderClear(renderer);
    currentScene->on_render();
    SDL_RenderPresent(renderer);
}

void Game::on_input(SDL_Event* event)
{
    while(SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
        {
            is_quit = true;
        }
        currentScene->on_input(event);
    }
}

void Game::on_update(float delta)
{
    currentScene->on_update(delta);
}

void Game::on_enter()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,"SDL_Init Error: %s", SDL_GetError());
        is_quit = true;
    }

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,"SDL_CreateWindow Error: %s", SDL_GetError());
        is_quit = true;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_TARGETTEXTURE);
    if(renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,"SDL_CreateRenderer Error: %s", SDL_GetError());
        is_quit = true;
    }
    if(IMG_Init(IMG_INIT_PNG)!=IMG_INIT_PNG)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,"IMG_Init Error: %s", IMG_GetError());
        is_quit = true;
    }
    currentScene = new SceneMain();
    currentScene->on_enter();

    run();
}

void Game::on_exit()
{


    
    if(currentScene != nullptr)
    {
        currentScene->on_exit();
        delete currentScene;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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
