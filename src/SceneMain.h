#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "Scene.h"
#include "Object.h"

class Game;


class SceneMain : public Scene 
{
public:
    SceneMain();
    ~SceneMain();

    void on_enter() override;
    void on_update() override;
    void on_render() override;
    void on_input(SDL_Event* event) override;
    
    void on_exit() override;

private:
    Player player;
    Game &game;
};


#endif // SCENE_MAIN_H