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

    TextureLibrary* loader = TextureLibrary::getInstance();

    std::string basePath = "ASSETS/IMAGES/Tiles/";
    std::vector<TraversalProperty> types = { TraversalProperty::Walkable, TraversalProperty::Unwalkable, TraversalProperty::Job };

    for (int i = 0; i < types.size(); i++)
    {
        std::string folderPath = basePath + m_cellPropertyString[types[i]];
        std::vector<Texture*> textures = loader->loadAllTexturesInFile(folderPath);

        for (int k = 0; k < textures.size(); k++)
        {
            m_quantity[types[i]]++;

            m_tiles[types[i]].push_back({ textures[k], 100, 100 });
            m_tiles[types[i]][k].m_property = types[i];
        }
    }
   
}
