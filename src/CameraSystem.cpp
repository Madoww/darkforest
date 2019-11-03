#include "CameraSystem.h"
#include <iostream>

CameraSystem::CameraSystem()
:zoom_check(20),slow_move_check(1)
{
    view.setSize(1920,1080);
    view.setCenter(1920/2,1080/2);
    default_view = view;
}
void CameraSystem::update()
{
    if(move_slowly){
    slow_move_check.update();
    if(!slow_move_check.getStatus())
    {
        zoom(smv.zoom_amount);
        move(smv.xspeed,smv.yspeed);
    }
    else
    {
        smv.restart();
        slow_move_check.restart();
        move_slowly=false;
    }
    }
    
}
void CameraSystem::zoom(float zoom_amount)
{
    zoom_check.update();
    //if(zoom_check.getStatus())
    {
        view.zoom(zoom_amount);
        zoom_check.restart();
    }
}
void CameraSystem::slow_move(float x, float xspeed,float yspeed, float zoom_amount)
{
    smv = {x,xspeed,yspeed,zoom_amount};
    slow_move_check.setDelay(x/xspeed);
    move_slowly = true;
}
