#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>

class TextureManager
{
    public:
        typedef std::unordered_map<std::string, sf::Texture*>tex_map;
        ~TextureManager();
        TextureManager(const TextureManager&) = delete;
        TextureManager operator=(const TextureManager&)=delete;
        static sf::Texture* load(const std::string& texture_name,const std::string& texture_source);
        static bool unload(const std::string& texture_name);
        static size_t clean();
        static sf::Texture* get(const std::string& texture_name);
        inline static bool exists(const std::string& texture_name){return get(texture_name)!=nullptr;}

        void preload();

        inline static TextureManager& instance()
        {
            static TextureManager instance;
            return instance;
        }

    private:
        TextureManager();
        tex_map m_textures;
    //std::string path = "/Users/Filip/Documents/code/dark_forest/dark_forest/";
    std::string path = "";
};

#endif // TEXTUREMANAGER_H
