#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include <SFML/Graphics.hpp>


class ImageManager
{
    public:
        ImageManager();
        virtual ~ImageManager();
        void loadImage(const std::string& filename);
        void loadImage(const std::string& filename, const std::string& name);
        void unloadImage(const std::string& key);
        sf::Texture& getTexture(const std::string& key);
    private:
        std::map<std::string, sf::Texture> images;
};

#endif // IMAGEMANAGER_H
