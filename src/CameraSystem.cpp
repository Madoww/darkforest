#include "CameraSystem.h"

CameraSystem::CameraSystem()
:zoom_check(20)
{
    view.setSize(1920,1080);
    view.setCenter(1920/2,1080/2);
    default_view = view;
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
