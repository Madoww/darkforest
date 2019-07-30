
#include "DialogueSystem.hpp"

DialogSystem::DialogSystem()
:letters(2),close_check(90)
{
    text.setFont(font.font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);

    background.setSize(def_background_size);//500
    //background.setPosition(0,1080-background.getSize().y);
    background.setPosition(0,-background.getSize().y-4);
    background.setFillColor(sf::Color(111,111,111,111));
    def_border = 500;
}

void DialogSystem::draw(sf::RenderWindow& window)
{
    /*if(is_open && background.getPosition().y<0)
    {
        background.move(0,6);
    }
    else if(!is_open && background.getPosition().y>-background.getSize().y)
        background.move(0,-6);*/
    background.setPosition(player.getPosition().x-background.getSize().x/2,player.getPosition().y-background.getSize().y-150);
    text.setPosition(background.getPosition().x+background.getSize().x/2,background.getPosition().y+10);
    letters.update();
    if(letters.getStatus() && letters_to_draw<string.getSize())
    {
        temp.insert(temp.getSize(), string[letters_to_draw]);
        if(text.findCharacterPos(text.getString().getSize()-1).x>background.getPosition().x+def_border)
        {
            int to_space=0;
            for(int i = text.getString().getSize(); i>0; i--)
            {
                if(temp[i]!=sf::String(" "))
                    to_space++;
                else
                {
                    break;
                    background.setSize(sf::Vector2f(background.getSize().x,background.getSize().y+5));
                }

            }
            b_resize=20;
            background.setSize(sf::Vector2f(background.getSize().x+10,background.getSize().y));
            temp.insert(temp.getSize()-to_space,"\n");
        }
        text.setString(temp);
        text.setOrigin(text.getGlobalBounds().width/2,0);
        letters_to_draw++;
        letters.restart();
        /*for(int i = 0; i<text.getString().getSize(); i++)
        {
            if(text.findCharacterPos(i).x>background.getPosition().x+def_border)
            {
                for(int j = i; j>0; j--)
                {
                    if(temp[j]==sf::String(" ") || j==1)
                    {
                        temp.insert(j,"\n");
                        def_border+=8;
                        std::cout<<"inserted"<<std::endl;
                        background.setSize(sf::Vector2f(background.getSize().x,background.getSize().y+40));
                        break;
                    }
                }
            }
        }*/
    }
    if(b_resize)
    {
        b_resize-=1;
        background.setSize(sf::Vector2f(background.getSize().x,background.getSize().y+1));
    }
    if(letters_to_draw == string.getSize() && string.getSize()>1)
    {
        is_saying = false;
        close_check.update();
    }
    /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        text.setString(string);
        letters_to_draw = string.getSize();
    }*/
    if(background.getSize().x<=510)
        background.setSize(sf::Vector2f(background.getSize().x+3,background.getSize().y));
    if(close_check.getStatus())
        setStatus(false);
    if(is_open)
    {
        window.draw(background);
        window.draw(text);
    }
    else
    {
        def_border = 500;
        background.setSize(def_background_size);
    }

}
void DialogSystem::say(const sf::String& input)
{
    if(is_saying == false)
    {
        def_border = 500;
        background.setSize(sf::Vector2f(200,50));
        is_saying = true;
        setStatus(true);
        letters_to_draw = 0;
        string = input;
        close_check.restart();
        temp = "";
        text.setString(temp);
    }
}
