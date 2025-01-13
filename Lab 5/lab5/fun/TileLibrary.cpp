#include "TileLibrary.h"
TileLibrary* TileLibrary::instance = nullptr;

TileLibrary* TileLibrary::getInstance()
{

    if (instance == nullptr)
    {
        instance = new TileLibrary();
    }

    
    return instance;
}

void TileLibrary::loadTextures()
{

    Loader* loader = Loader::getInstance();
    std::vector<sf::Texture*> walkableTextures = loader->loadAllTexturesInFile("ASSETS/IMAGES/Tiles/Walkable");
    std::vector<sf::Texture*> unwalkableTextures = loader->loadAllTexturesInFile("ASSETS/IMAGES/Tiles/Unwalkable");
    std::vector<sf::Texture*> jobTextures = loader->loadAllTexturesInFile("ASSETS/IMAGES/Tiles/Job");

    std::string path = "ASSETS/IMAGES/Tiles/";
    std::vector<TraversalProperty> types = { TraversalProperty::Walkable/*, TraversalProperty::Unwalkable, TraversalProperty::Job*/ };

    for (int i = 0; i < types.size(); i++)
    {
        std::vector<sf::Texture*> textures = loader->loadAllTexturesInFile(path + m_cellPropertyString[types[i]]);

        for (int i = 0; i < textures.size(); i++)
        {
           
        }
    }
   
}

int TileLibrary::rowNumInTexture(sf::Texture* t_texture)
{


    float textureHeight = t_texture->getSize().y;

    int rowsNeeded = textureHeight / m_pixelPerCellWidth;


    return rowsNeeded;
}

int TileLibrary::colNumInTexture(sf::Texture* t_texture)
{
    float textureWidth = t_texture->getSize().x;
    int columnsNeeded = textureWidth / m_pixelPerCellWidth;

    return columnsNeeded;
}
