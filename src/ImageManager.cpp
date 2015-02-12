#include "ImageManager.h"
#include <fstream>
#include <iostream>

ImageManager::ImageManager()
{
    //ctor
}

ImageManager::~ImageManager()
{
    //dtor
}

// Load an image into the map and use the file path as the key
void ImageManager::loadImage(const std::string& filename)
{
    sf::Texture tempTexture;

    // Ensuring that the file exists
    if (!tempTexture.loadFromFile(filename))
    {
        std::cout << "Error loading " << filename << std::endl;
    }
    images[filename] = tempTexture;
}

// Load an image into the map and specify the key
void ImageManager::loadImage(const std::string& filename, const std::string& name)
{
    sf::Texture tempTexture;

    // Ensuring that the file exists
    if (!tempTexture.loadFromFile(filename))
    {
        std::cout << "Error loading " << filename << std::endl;
    }

    images[name] = tempTexture;
}

// Method to unload an image from memory based on it's key
void ImageManager::unloadImage(const std::string& key)
{
    images.erase(key);
}

// Method to access a texture given its filename
sf::Texture& ImageManager::getTexture(const std::string& key)
{
    return images[key];
}
