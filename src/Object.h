#ifndef OBJECT_H
#define OBJECT_H
#include "SDL.h"


struct Player
{
    SDL_Texture *texture;
    SDL_FPoint position = {0, 0};
    int width = 0;
    int height = 0;
    bool left_key_down = false, right_key_down = false, up_key_down = false, down_key_down = false;
    int SPEED = 350;
};

#endif // OBJECT_H