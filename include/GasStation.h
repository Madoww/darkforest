#ifndef GASSTATION_H
#define GASSTATION_H
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Player.h"
#include "ClickCheck.h"
#include "NoteSystem.h"
#include "Phone.h"
#include "DialogueSystem.hpp"
#include "Items.h"
#include "Scene.h"

class GasStation : public SceneBase
{
public:
    GasStation(int& scene);
    virtual ~GasStation();
    void draw(sf::RenderWindow& window);
private:
    sf::Sprite gas;
    sf::Sprite house;
    sf::Sprite booth;
    sf::Sprite barrel;
    std::vector<sf::Sprite>ground;
    sf::Sprite fire;
    Player& player = Player::instance();
    int sourcex = 0;
    Check fire_check;
    std::vector<sf::RectangleShape>particles;
    sf::RectangleShape part;
    sf::Sprite crow;
    Phone& phone = Phone::instance();
    NoteSystem& notes = NoteSystem::instance();
    DialogSystem& dialog = DialogSystem::instance();
    Items& items = Items::instance();
    int& scene;
    sf::Sprite car;
};

#endif // GASSTATION_H
