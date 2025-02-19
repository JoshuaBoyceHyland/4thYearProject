#include "Librarys/TileLibrary.h"

TileLibrary* TileLibrary::instance = nullptr;

TileLibrary::TileLibrary()
{
    loadTextures();
}
TileLibrary* TileLibrary::getInstance()
{
    if (instance == nullptr)
    {
        instance = new TileLibrary();
    }

    return instance;
}

Tile* TileLibrary::getTile(TraversalProperty t_type, int t_index)
{
    return &m_tiles[t_type][t_index];
}

void TileLibrary::loadTextures()
{

    Loader* loader = Loader::getInstance();

    std::string basePath = "ASSETS/IMAGES/Tiles/";
    std::vector<TraversalProperty> types = { TraversalProperty::Walkable, TraversalProperty::Unwalkable, TraversalProperty::Job};

    int done = 0;
    for (int i = 0; i < types.size(); i++)
    {
        std::string folderPath = basePath + m_cellPropertyString[types[i]];
        std::vector<Texture*> textures = loader->loadAllTexturesInFile(folderPath);

        if (types[i] == TraversalProperty::Unwalkable && done == 0)
        {
            splitTextureIntoGrid(textures[1], TraversalProperty::Unwalkable);
            done++;
        }

        for (int k = 0; k < textures.size(); k++)
        {
            m_quantity[types[i]]++;

            m_tiles[types[i]].push_back({ textures[k], 100, 100 });
            m_tiles[types[i]][k].m_property = types[i];
        }
    }
   
}



Grid TileLibrary::splitTextureIntoGrid(Texture* t_texture, TraversalProperty t_property)
{


    float textureWidth = t_texture->texture.getSize().x;
    float textureHeight = t_texture->texture.getSize().y;

    int columnsNeeded = textureWidth / 32;
    int rowsNeeded = textureHeight / 32;


    int startX = 0;
    int startY = 0;

    sf::Texture newTexture;
    sf::IntRect imageArea;
    sf::Image image = t_texture->texture.copyToImage();
  
    Grid tile(rowsNeeded, columnsNeeded, 100, 100, {-500, -100});


    for (int row = 0; row < rowsNeeded; row++)
    {
        for (int column = 0; column < columnsNeeded; column++)
        {
            // part of image we are extracting
            imageArea = sf::IntRect(startX, startY, 32, 32);
            newTexture.loadFromImage(image, imageArea);
     
            tempTexture2.push_back({ t_texture->id, newTexture });

            tile.m_cells[row][column].setTexture(&tempTexture2[row * columnsNeeded +  ( column)]);
            tile.m_cells[row][column].setColor(sf::Color::White);
            startX += 32;
        }

        startX = 0;
        startY += 32;
    }

    temp1.push_back(tile);

    return temp1[0];
}
