#include "resourceManager.hpp"

ResourceManager::ResourceManager()
{
    this->loadTexture("wall_textures",this->resourcePath+"wall_textures.png");
    this->loadFont("arial",this->resourcePath+"arial.ttf");
}

void ResourceManager::loadTexture(const std::string &name, const std::string &filename){
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    textures[name] = std::move(texture);
    std::cout << "Loading " << filename << " was succesfull\n";
}

void ResourceManager::loadFont(const std::string &name, const std::string &filename)
{
    sf::Font font;
    if (!font.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load font: " + filename);
    }
    fonts[name] = std::move(font);
    std::cout << "Loading " << filename << " was succesfull\n";
}

sf::Texture &ResourceManager::getTexture(const std::string &name)
{
    auto it = textures.find(name);
    if (it == textures.end()) {
        throw std::runtime_error("Texture not found: " + name);
    }
    return it->second;
}

sf::Font &ResourceManager::getFont(const std::string &name)
{
    auto it = fonts.find(name);
    if (it == fonts.end()) {
        throw std::runtime_error("Font not found: " + name);
    }
    return it->second;
}

sf::Sprite ResourceManager::createSprite16x16(const std::string &textureName, const WallTextureType textureEnum)
{
    
    // Retrieve the texture from the resource manager
    sf::Texture& texture = getTexture(textureName);

    // Get the texture rectangle for the given WallTextureType
    sf::IntRect textureRect = getTextureRect(textureEnum, 16, 8, 8);

    // Create the sprite and set its texture and texture rectangle
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);

    return sprite;
}

sf::IntRect ResourceManager::getTextureRect(const int index, const int size, const int rows, const int columns)
{
    int x = index % columns; // Column index
    int y = index / rows; // Row index
    return sf::IntRect(x * size, y * size, size, size);
}

sf::IntRect ResourceManager::getTextureRectWall(const WallTextureType textureEnum, const int size, const int rows, const int columns)
{
    int x = textureEnum % columns; // Column index
    int y = textureEnum / rows; // Row index
    return sf::IntRect(x * size, y * size, size, size);
}
