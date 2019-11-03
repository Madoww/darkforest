#ifndef APP_H
#define APP_H
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "forest.h"
#include "Player.h"
#include "Flashlight.h"
#include "InventorySystem.h"
#include "Shed.h"
#include "GasStation.h"
#include "NoteSystem.h"
#include "DialogueSystem.hpp"
#include "Items.h"
#include "Effects.hpp"
#include "CameraSystem.h"
#include "Forest2.hpp"
#include "Rain.h"
#include "Enemies.h"
#include "Screenshot.h"


enum Status
{
    Initializing    = 0,
    Running         = 1,
    Paused          = 2,
    CleaningUp      = 3
};
enum Scene
{
    GasStationScene = 0,
    Woods,
    ShedScene,
    Woods2
};

class app
{
    public:
        ~app();
        app(const app&) = delete;
        app operator=(const app&) = delete;
        inline static app& instance()
        {
            static app instance;
            return instance;
        }
        void setScene(int get){scene=get;}
        void run();
        int scene = Scene::Woods2;
    private:
        app();
        sf::RenderWindow m_window;
        Status m_status;
        sf::Sprite obj;
        sf::Sprite background;
        std::vector<SceneBase*>scenes;
        Player& player = Player::instance();
        Phone& phone = Phone::instance();
        Flashlight& torch = Flashlight::instance();
        CameraSystem& camera = CameraSystem::instance();
        InventorySystem& inventory = InventorySystem::instance();
    sf::RectangleShape cover;
    Rain rain;
    Items& items = Items::instance();
    DialogSystem& dialog = DialogSystem::instance();
    Leafs& leafs = Leafs::instance();
    Screenshot& screenshot = Screenshot::instance();
    Photos& photos = Photos::instance();
    NoteSystem& notes = NoteSystem::instance();
};

#endif // APP_H
