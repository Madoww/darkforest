#include "Flashlight.h"

float Flashlight::darkness_level = 10;
Flashlight::~Flashlight()
{
    //dtor
}
void Flashlight::move_sources(float x, float y)
{
    for(int i = 0; i<sources.size(); i++)
    {
        sources[i]->getSource().move(x,y);
    }
}
