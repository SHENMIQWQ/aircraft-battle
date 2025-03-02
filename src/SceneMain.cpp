#include "SceneMain.h"
#include "Game.h"

#include<SDL_image.h>


SceneMain::SceneMain() : game(*Game::instance())
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::on_update()
{
    
}

void SceneMain::on_render()
{
    SDL_Rect player_rect = {(int)player.position.x, (int)player.position.y, player.width, player.height};
    SDL_RenderCopy(game.get_renderer(), player.texture, NULL, &player_rect);
}

void SceneMain::on_input(SDL_Event *event)
{
}

void SceneMain::on_enter()
{
    player.texture = IMG_LoadTexture(game.get_renderer(), "assets/image/Spaceship.png");
    SDL_QueryTexture(player.texture, NULL, NULL, &player.width, &player.height);
    player.width /= 4;
    player.height /= 4;
    player.position.x = game.get_window_size().x / 2 - player.width / 2;
    player.position.y = game.get_window_size().y - player.height;
}

void SceneMain::on_exit()
{
    if (player.texture != NULL)
    {
        SDL_DestroyTexture(player.texture);
        player.texture = NULL;
    }
}

