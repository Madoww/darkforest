#include "Rain.h"

Rain::Rain()
{
    srand(time(NULL));
    drops.setPrimitiveType(sf::Quads);
    drops.resize(4);
}

Rain::~Rain()
{
    //dtor
}

void Rain::rain(sf::RenderWindow& window)
{
    if(drops_created<1100)
    for(int i = 0; i<10; i++)
    {
        //drop.setPosition(rand()%(window.getSize().x+int(windspeed*60))-windspeed*25,0);
        sf::Vector2f def_pos = sf::Vector2f(rand()%(1920+int(windspeed*60))-windspeed*25+camera.getOffset().x,0);
        drops.append(sf::Vertex(sf::Vector2f(def_pos.x-windspeed*50,def_pos.y)));
        drops.append(sf::Vertex(sf::Vector2f(def_pos.x-windspeed*50,def_pos.y+8)));
        drops.append(sf::Vertex(sf::Vector2f(def_pos.x+2-windspeed*50,def_pos.y+8)));
        drops.append(sf::Vertex(sf::Vector2f(def_pos.x+2-windspeed*50,def_pos.y)));
        for(int i = 0; i<drops.getVertexCount(); i++)
            drops[i].color = sf::Color(102, 157, 244,30);
        drops_created++;
        //transform.push_back(sf::Transform());
        //states.push_back(sf::RenderStates());
        //for(int j = 0; j<drops.getVertexCount(); j++)
            //drops[j].position = sf::Vector2f(drops[j].position.x-windspeed*50,drops[j].position.y);
        //drops.push_back(drop);
    }
    /*for(int i = 0; i<drops.size(); i++)
    {
        drops[i][0].position = sf::Vector2f(drops[i][0].position.x+windspeed,drops[i][0].position.y+10);
        drops[i][1].position = sf::Vector2f(drops[i][1].position.x+windspeed,drops[i][1].position.y+10);
        drops[i][2].position = sf::Vector2f(drops[i][2].position.x+windspeed,drops[i][2].position.y+10);
        drops[i][3].position = sf::Vector2f(drops[i][3].position.x+windspeed,drops[i][3].position.y+10);
        states[i].transform = transform[i];
        window.draw(drops[i],states[i]);
    }*/
    for(int i = 0; i<drops.getVertexCount(); i++)
    {
        drops[i].position = sf::Vector2f(drops[i].position.x+windspeed,drops[i].position.y+10);
        if(i%4 == 0)
        {
            if(drops[i].position.y > 1080)
            {
                sf::Vector2f def_pos = sf::Vector2f(rand()%(1920+int(windspeed*60))-windspeed*25+camera.getOffset().x,0);
                drops[i].position = sf::Vector2f(def_pos.x-windspeed*50,def_pos.y);
                drops[i+1].position = sf::Vector2f(def_pos.x-windspeed*50,def_pos.y+8);
                drops[i+2].position = sf::Vector2f(def_pos.x+2-windspeed*50,def_pos.y+8);
                drops[i+3].position = sf::Vector2f(def_pos.x+2-windspeed*50,def_pos.y);
            }
        }
        //if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            //drops[i].position = sf::Vector2f(drops[i].position.x+player.speed,drops[i].position.y);
        //if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            //drops[i].position = sf::Vector2f(drops[i].position.x-player.speed,drops[i].position.y);
    }

    window.draw(drops);
        //drops[i].move(windspeed,10);

        //if(drops[i].getPosition().y>window.getSize().y)
            //drops.erase(drops.begin()+i);
    //std::cout<<drops.size()<<"\n";
}
