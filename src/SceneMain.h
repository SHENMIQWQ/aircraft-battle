#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "Scene.h"

class SceneMain : public Scene {
public:
    SceneMain();
    ~SceneMain();

    void on_enter() override;
    void on_update() override;
    void on_render() override;
    void handleEvent(SDL_Event* event) override;
    
    void on_exit() override;

private:

};


#endif // SCENE_MAIN_H