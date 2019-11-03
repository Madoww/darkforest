#ifndef NOTESYSTEM_H
#define NOTESYSTEM_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <iostream>
#include "Fonts.h"
#include "ClickCheck.h"
#include <vector>

class Note
{
public:
    Note(std::string title_string,std::string inside_string, const sf::Vector2f& position);
    ~Note(){};
    void draw_prev(sf::RenderWindow&, const sf::Vector2f& position);
    void draw_note(sf::RenderWindow& window);
    void setPosition(const sf::Vector2f& position, sf::Vector2f def_pos);
    sf::Vector2f getPosition(){return background.getPosition();}
    sf::FloatRect getGlobalBounds(){return background.getGlobalBounds();}
    void setFont(const sf::Font& font){title.setFont(font);title.setOrigin(title.getGlobalBounds().width/2,title.getGlobalBounds().height/2);title.setPosition(background.getPosition());
                                        inside.setFont(font);}
    void move(float x);
    void setStatus(bool status){is_inside = status;}
    bool getStatus(){return is_inside;}
    Fonts font;
    float relative_pos;
private:
    sf::RectangleShape background;
    sf::Text title;
    sf::Text inside;
    sf::RectangleShape note_background;
    bool is_inside = false;
    int def_note_border = 160;
    int space_position = 0;
};

class NoteSystem
{
public:
    virtual ~NoteSystem();
    inline static NoteSystem& instance()
    {
        static NoteSystem inst;
        return inst;
    }
    void add_note(sf::String title, sf::String inside);
    void setPosition(const sf::Vector2f& position);
    void draw(sf::RenderWindow&, const sf::Vector2f& position);
    void scroll_up();
    void scroll_down();
    void restart_notecheck();
    void move(float x);
    bool is_reading = false;
private:
    NoteSystem();
    Fonts font;
    bool is_set = false;
    sf::Vector2f def_pos;
    std::vector<Note>notes;
    Check note_open_check;
    sf::RectangleShape background;
};

#endif // NOTESYSTEM_H
