#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>

class Scene{
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void on_enter() = 0;
    virtual void on_update() = 0;
    virtual void on_render() = 0;
    virtual void on_exit() = 0;
    virtual void handleEvent(SDL_Event* event) = 0;
};

#endif // SCENE_H