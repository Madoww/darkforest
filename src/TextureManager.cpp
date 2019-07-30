#include "TextureManager.h"

void TextureManager::preload()
{
    load("tree",path+"Sources/Textures/tree.png");
    load("tree2",path+"Sources/Textures/tree2.png");
    load("tree3",path+"Sources/Textures/tree3.png");
    load("ground",path+"Sources/Textures/grass.png");
    load("bush",path+"Sources/Textures/bush.png");
    load("path",path+"Sources/Textures/path.png");
    load("grass",path+"Sources/Textures/grasstile.png");
    load("player",path+"Sources/Textures/player_animation.png");
    load("car",path+"Sources/Textures/car.png");
    load("phone",path+"Sources/Textures/phone.png");
    load("standup",path+"Sources/Textures/standup_animation.png");
    load("street",path+"Sources/Textures/road.png");
    load("roadblock",path+"Sources/Textures/roadblock.png");
    load("house",path+"Sources/Textures/house.png");
    load("roof",path+"Sources/Textures/roof.png");
    load("toolbox",path+"Sources/Textures/toolbox.png");
    load("inside",path+"Sources/Textures/inside.png");
    load("crouch",path+"Sources/Textures/player_crouch.png");
    load("painting",path+"Sources/Textures/painting.png");
    load("cross",path+"Sources/Textures/cross.png");
    load("basement",path+"Sources/Textures/basement.png");
    load("sit",path+"Sources/Textures/player_sit_animation.png");
    load("blood_drop",path+"Sources/Textures/blood_drop.png");
    load("player_drop",path+"Sources/Textures/player_drop.png");
    load("gas",path+"Sources/Textures/gas_station.png");
    load("gas_house",path+"Sources/Textures/gas_house.png");
    load("asphalt",path+"Sources/Textures/asphalt.png");
    load("booth",path+"Sources/Textures/booth.png");
    load("barrel",path+"Sources/Textures/barrel.png");
    load("fire_animation",path+"Sources/Textures/fire_animation.png");
    load("crow",path+"Sources/Textures/crow.png");
    load("phone_background",path+"Sources/Textures/phone_background.png");
    load("dial_background",path+"Sources/Textures/dial_background.png");
    load("dial_clicked",path+"Sources/Textures/dial_clicked.png");
    load("dial_numbers",path+"Sources/Textures/dial_numbers.png");
    load("phone_icon",path+"Sources/Textures/phone_icon.png");
    load("delete_icon",path+"Sources/Textures/delete_icon.png");
    load("storage_room",path+"Sources/Textures/storage_room.png");
}

TextureManager::TextureManager()
{
    //ctor
}

TextureManager::~TextureManager()
{
    //dtor
}

sf::Texture* TextureManager::load(const std::string& texture_name,const std::string& texture_source)
{
    sf::Texture* result = get(texture_name);
    if(result)
    {
        result->loadFromFile(texture_source);
    }
    else
    {
        result = new sf::Texture();
        result->loadFromFile(texture_source);
        instance().m_textures[texture_name] = result;
    }
    return result;
}

size_t TextureManager::clean()
{
    size_t texture_count = instance().m_textures.size();
    for(auto texture_data : instance().m_textures)
        delete texture_data.second;
    return texture_count;
}

bool TextureManager::unload(const std::string& texture_name)
{
    auto texture_iterator = instance().m_textures.find(texture_name);
    if(texture_iterator == instance().m_textures.end())
        return false;
    else
    {
        delete texture_iterator->second;
        instance().m_textures.erase(texture_iterator);
        return true;
    }
}

sf::Texture* TextureManager::get(const std::string& texture_name)
{
    //TextureManager& instance = instance;
    auto texture_iterator = instance().m_textures.find(texture_name);
    if(texture_iterator == instance().m_textures.end())
    {
        return nullptr;
    }
    return texture_iterator->second;
}
