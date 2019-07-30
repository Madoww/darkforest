#ifndef LIGHTING_H_INCLUDED
#define LIGHTING_H_INCLUDED
#include <SFML/Graphics.hpp>

//namespace fp

class Shadow
{
public:
    Shadow(const sf::RectangleShape& rectangle, const sf::RectangleShape* source)
    {
        this->rect = rectangle;
        this->source = source;
        for(int i = 0; i<4; i++)
        {
            shadow[i].setPrimitiveType(sf::Quads);
            shadow[i].resize(4);
        }

        shadow[0][0].position = sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2);
        shadow[0][1].position = sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2);

        shadow[1][0].position = sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2);
        shadow[1][1].position = sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2);

        shadow[2][0].position = sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2);
        shadow[2][1].position = sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2);

        shadow[3][0].position = sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2);
        shadow[3][1].position = sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2);

        for(int i = 0; i<4; i++)
        {
            for(int j = 0; j<4; j++)
              shadow[i][j].color = sf::Color::Black;
        }
    }
    void draw(sf::RenderWindow &window)
    {
        for(int i = 0; i<4; i++)
        window.draw(shadow[i]);
        //window.draw(shadow[0]);
    }
    virtual void update(sf::RectangleShape& rect)
    {
        shadow[0][0].position = sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2);
        shadow[0][1].position = sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2);

        shadow[1][0].position = sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2);
        shadow[1][1].position = sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2);

        shadow[2][0].position = sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2);
        shadow[2][1].position = sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2);

        shadow[3][0].position = sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2);
        shadow[3][1].position = sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2);
        direction1[0] = sf::Vector2f(source->getPosition()-sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2));
        direction2[0] = sf::Vector2f(source->getPosition()-sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2));
        shadow[0][2].position = sf::Vector2f(sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2)-sf::Vector2f(direction1[0].x*height,direction1[0].y*height));
        shadow[0][3].position = sf::Vector2f(sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2)-sf::Vector2f(direction2[0].x*height,direction2[0].y*height));

        direction1[1] = sf::Vector2f(source->getPosition()-sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2));
        direction2[1] = sf::Vector2f(source->getPosition()-sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2));
        shadow[1][2].position = sf::Vector2f(sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2)-sf::Vector2f(direction1[1].x*height,direction1[1].y*height));
        shadow[1][3].position = sf::Vector2f(sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2)-sf::Vector2f(direction2[1].x*height,direction2[1].y*height));

        direction1[2] = sf::Vector2f(source->getPosition()-sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2));
        direction2[2] = sf::Vector2f(source->getPosition()-sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2));
        shadow[2][2].position = sf::Vector2f(sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2)-sf::Vector2f(direction1[2].x*height,direction1[2].y*height));
        shadow[2][3].position = sf::Vector2f(sf::Vector2f(rect.getPosition().x-rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2)-sf::Vector2f(direction2[2].x*height,direction2[2].y*height));

        direction1[3] = sf::Vector2f(source->getPosition()-sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2));
        direction2[3] = sf::Vector2f(source->getPosition()-sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2));
        shadow[3][2].position = sf::Vector2f(sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y+rect.getSize().y/2)-sf::Vector2f(direction1[3].x*height,direction1[3].y*height));
        shadow[3][3].position = sf::Vector2f(sf::Vector2f(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y-rect.getSize().y/2)-sf::Vector2f(direction2[3].x*height,direction2[3].y*height));
    }
private:
    sf::VertexArray shadow[4];
    sf::Vector2f direction1[4];
    sf::Vector2f direction2[4];
    sf::RectangleShape rect;
    const sf::RectangleShape* source;
    int height = 3;
};

template<int points>
class ComplexShadow
{
public:
    ComplexShadow(sf::VertexArray& object)
    {
        for(int i = 0; i<points; i++)
        {
            shadow[i].setPrimitiveType(sf::Quads);
            shadow[i].resize(4);
            for(int j = 0; j<4; j++)
            {
                shadow[i][j].color = sf::Color::Black;
            }
        }
        for(int i = 0; i<points; i++)
        {
            for(int j = 0; j<2; j++)
            {
                std::cout<<"set"<<std::endl;
                if(i == points-1 && j == 1)
                    shadow[i][j].position = sf::Vector2f(object[0].position);
                else
                    shadow[i][j].position = sf::Vector2f(object[i+j].position);
            }
        }
    }
    void update(sf::VertexArray& object, sf::RectangleShape& source)
    {
        for(int i = 0; i<points; i++)
        {
                direction1[i] = sf::Vector2f(source.getPosition()-object[i].position);
                if(i+1<points)
                    direction2[i] = sf::Vector2f(source.getPosition()-object[i+1].position);
                else
                    direction2[i] = sf::Vector2f(source.getPosition()-object[0].position);
        }
        for(int i = 0; i<points; i++)
        {
            shadow[i][3].position = sf::Vector2f(object[i].position-direction1[i]);
            if(i+1<points)
                shadow[i][2].position = sf::Vector2f(object[i+1].position-direction2[i]);
            else
                shadow[i][2].position = sf::Vector2f(object[0].position-direction2[i]);
        }
    }
    void draw(sf::RenderTarget& window)
    {
        for(int i = 0; i<points; i++)
        {
            window.draw(shadow[i]);
        }

    }
    sf::VertexArray shadow[points];
private:
    int points_count = points;
    sf::Vector2f direction1[points];
    sf::Vector2f direction2[points];
};

class RoundShadow
{
public:
    RoundShadow(const sf::CircleShape& circle)
    {
        for(int i = 0; i<8; i++)
        {
            shadow[i].setPrimitiveType(sf::Quads);
            shadow[i].resize(4);
            for(int j = 0; j<4; j++)
            {
                shadow[i][j].color = sf::Color::Black;
            }
        }
        object.setPrimitiveType(sf::TrianglesStrip);
        object.resize(8);
        object[0].position = sf::Vector2f(circle.getPosition().x, circle.getPosition().y-circle.getRadius());
        object[1].position = sf::Vector2f(circle.getPosition().x+circle.getRadius()/sqrt(2),circle.getPosition().y-circle.getRadius()/sqrt(2));
        object[2].position = sf::Vector2f(circle.getPosition().x+circle.getRadius(),circle.getPosition().y);
        object[3].position = sf::Vector2f(circle.getPosition().x+circle.getRadius()/sqrt(2),circle.getPosition().y+circle.getRadius()/sqrt(2));
        object[4].position = sf::Vector2f(circle.getPosition().x,circle.getPosition().y+circle.getRadius());
        object[5].position = sf::Vector2f(circle.getPosition().x-circle.getRadius()/sqrt(2),circle.getPosition().y+circle.getRadius()/sqrt(2));
        object[6].position = sf::Vector2f(circle.getPosition().x-circle.getRadius(),circle.getPosition().y);
        object[7].position = sf::Vector2f(circle.getPosition().x-circle.getRadius()/sqrt(2),circle.getPosition().y-circle.getRadius()/sqrt(2));
        for(int i = 0; i<8; i++)
        {
            for(int j = 0; j<2; j++)
            {
                std::cout<<"set"<<std::endl;
                if(i == 8-1 && j == 1)
                    shadow[i][j].position = sf::Vector2f(object[0].position);
                else
                    shadow[i][j].position = sf::Vector2f(object[i+j].position);
            }
        }
    }
    void update(sf::RectangleShape& source)
    {
        for(int i = 0; i<8; i++)
        {
                direction1[i] = sf::Vector2f(source.getPosition()-object[i].position);
                if(i+1<8)
                    direction2[i] = sf::Vector2f(source.getPosition()-object[i+1].position);
                else
                    direction2[i] = sf::Vector2f(source.getPosition()-object[0].position);
        }
        for(int i = 0; i<8; i++)
        {
            shadow[i][3].position = sf::Vector2f(object[i].position-sf::Vector2f(direction1[i].x*height,direction1[i].y*height));
            if(i+1<8)
                shadow[i][2].position = sf::Vector2f(object[i+1].position-sf::Vector2f(direction2[i].x*height,direction2[i].y*height));
            else
                shadow[i][2].position = sf::Vector2f(object[0].position-sf::Vector2f(direction2[i].x*height,direction2[i].y*height));
        }
    }
    void draw(sf::RenderTarget& window)
    {
        for(int i = 0; i<8; i++)
        {
            window.draw(shadow[i]);
        }

    }
private:
    int points_count = 8;
    sf::VertexArray object;
    sf::VertexArray shadow[8];
    sf::Vector2f direction1[8];
    sf::Vector2f direction2[8];
    int height = 300;
};

#endif // LIGHTING_H_INCLUDED
