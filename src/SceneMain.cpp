#include "SceneMain.h"
#include "Game.h"

#include<SDL_image.h>
#include<cmath>

SceneMain::SceneMain() : game(*Game::instance())
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::on_update()
{
    int move_x =  player.right_key_down - player.left_key_down;
    int move_y =  player.down_key_down - player.up_key_down;
    float t = (float)sqrt(move_x*move_x + move_y*move_y);
    player.position.x += move_x ? move_x / t * player.SPEED : 0;
    player.position.y += move_y ? move_y / t * player.SPEED : 0;
  
    //边界处理
    if(player.position.x < 0) player.position.x = 0;
    if(player.position.y < 0) player.position.y = 0;
    if(player.position.x > game.get_window_size().x - player.width) player.position.x = game.get_window_size().x - player.width;
    if (player.position.y > game.get_window_size().y - player.height) player.position.y = game.get_window_size().y - player.height;

}

void SceneMain::on_render()
{
    SDL_Rect player_rect = {(int)player.position.x, (int)player.position.y, player.width, player.height};
    SDL_RenderCopy(game.get_renderer(), player.texture, NULL, &player_rect);
}

void SceneMain::on_input(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_ESCAPE:
            game.on_exit();
            break;
        case SDLK_UP:
            player.up_key_down = true;
            break;
        case SDLK_DOWN:
            player.down_key_down = true;
            break;
        case SDLK_LEFT:
            player.left_key_down = true;
            break;
        case SDLK_RIGHT:
            player.right_key_down = true;
            break;
        }
    }
    else if (event->type == SDL_KEYUP)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_ESCAPE:
            game.on_exit();
            break;
        case SDLK_UP:
            player.up_key_down = false;
            break;
        case SDLK_DOWN:
            player.down_key_down = false;
            break;
        case SDLK_LEFT:
            player.left_key_down = false;
            break;
        case SDLK_RIGHT:
            player.right_key_down = false;
            break;
        }
        
    }


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

