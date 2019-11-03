#include "NoteSystem.h"
#include "Phone.h"

Note::Note(std::string title_string,std::string inside_string, const sf::Vector2f& position)
{
    background.setSize(sf::Vector2f(177,30));
    background.setPosition(position);
    title.setCharacterSize(10);
    title.setFillColor(sf::Color::Black);
    title.setString(title_string);
    background.setOrigin(background.getSize().x/2,background.getSize().y/2.5);
    title.setOrigin(title.getGlobalBounds().width/2,title.getGlobalBounds().height/2);
    title.setPosition(background.getPosition());
    background.setFillColor(sf::Color(128, 128, 128));
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(2);

    inside.setCharacterSize(10);
    inside.setFillColor(sf::Color::Black);
    inside.setString(inside_string);
    relative_pos=position.y;
    std::cout<<position.y<<std::endl;

    note_background.setSize(sf::Vector2f(185,330));
    note_background.setFillColor(sf::Color(128, 128, 128));
}
void Note::setPosition(const sf::Vector2f& position, sf::Vector2f def_pos)
{
    background.setPosition(position);
    title.setPosition(background.getPosition());
    note_background.setPosition(def_pos.x+35,def_pos.y+45);
    inside.setPosition(note_background.getPosition().x,note_background.getPosition().y+15);
}
void Note::draw_prev(sf::RenderWindow& window, const sf::Vector2f& position)
{
    if(background.getPosition().y>position.y+30 && background.getPosition().y<position.y+360)
    {
        window.draw(background);
        window.draw(title);
    }
}
void Note::draw_note(sf::RenderWindow& window)
{
    if(is_inside == true)
    {
        window.draw(note_background);
        window.draw(inside);
        sf::String temp = inside.getString();
    for(int i = 0; i<inside.getString().getSize(); i++)
    {
        if(inside.findCharacterPos(i).x>note_background.getPosition().x+def_note_border)
        {
            for(int j = i; j>0; j--)
            {
                if(temp[j]==sf::String(" ") || j==1)
                {
                    temp.insert(j,"\n");
                    def_note_border+=160;
                    std::cout<<"inserted"<<std::endl;
                    break;
                }
            }
        }
    }
    inside.setString(temp);
    }
}
void NoteSystem::add_note(sf::String title, sf::String inside)
{
    notes.emplace_back(Note(title,inside,sf::Vector2f(notes[notes.size()-1].getPosition().x,notes[notes.size()-1].getPosition().y+notes[0].getGlobalBounds().height)));
    notes[notes.size()-1].setFont(font.font);
}
void NoteSystem::setPosition(const sf::Vector2f& position)
{
    if(is_set == false)
    {
        is_set = true;
        def_pos = position;
    }
    notes[0].setPosition(sf::Vector2f(position.x+notes[0].getGlobalBounds().width/2+35,position.y+notes[0].getGlobalBounds().height/2+50+notes[0].relative_pos),position);
    for(int i = 1; i<notes.size(); i++)
        notes[i].setPosition(sf::Vector2f(notes[i-1].getPosition().x,notes[i-1].getPosition().y+notes[i-1].getGlobalBounds().height),position);
}
NoteSystem::NoteSystem()
:note_open_check(20)
{
    notes.emplace_back(Note("To do","-Add a pin to my phone \n -Explore the forest",sf::Vector2f(200,0)));
    notes[0].setFont(font.font);
    background.setPosition(1700,1080);
    background.setSize(sf::Vector2f(185,330));
    background.setFillColor(sf::Color(100, 100, 100));
}

NoteSystem::~NoteSystem()
{
    //dtor
}
void Note::move(float x)
{
    relative_pos += x;
}
void NoteSystem::scroll_up()
{
    if(notes[notes.size()-1].getPosition().y>background.getPosition().y+background.getGlobalBounds().height-50)
    for(auto& note : notes)
        note.move(-10);
}
void NoteSystem::scroll_down()
{
    if(notes[0].getPosition().y<background.getPosition().y+20)
    for(auto& note : notes)
        note.move(10);
}
void NoteSystem::draw(sf::RenderWindow& window, const sf::Vector2f& position)
{
    note_open_check.update();
    background.setPosition(position.x+35,position.y+45);
    window.draw(background);
    for(int i = 0; i<notes.size(); i++)
    {
        for(int i = 0; i<notes.size(); i++)
        {
            if(notes[i].getStatus())
            {
                is_reading = true;
            }

        }
        if(is_reading == false)
            notes[i].draw_prev(window,position);
        if(notes[i].getGlobalBounds().contains(Click::instance().getPosition()) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && note_open_check.getStatus())
        {
            notes[i].setStatus(true);
            note_open_check.restart();
        }
        notes[i].draw_note(window);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || Phone::instance().is_back_clicked())
    {
        is_reading = false;
        for(int i = 0; i<notes.size(); i++)
            notes[i].setStatus(false);
    }
    if(is_reading)
        Phone::instance().enable_menu();
    else
        Phone::instance().disable_menu();
}
void NoteSystem::restart_notecheck()
{
    note_open_check.restart();
}
