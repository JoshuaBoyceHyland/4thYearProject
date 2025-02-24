#include "Librarys/WorldItemLibrary.h"
WorldItemLibrary* WorldItemLibrary::instance = nullptr;

WorldItemLibrary::WorldItemLibrary()
{
    loadTextures();
}

WorldItemLibrary* WorldItemLibrary::getInstance()
{

    if (instance == nullptr)
    {
        instance = new WorldItemLibrary();
    }
    return instance;
}

WorldItem* WorldItemLibrary::getItem(int t_index)
{
    return &m_items[t_index];
}

void WorldItemLibrary::loadTextures()
{

    Loader* loader = Loader::getInstance();

    std::string basePath = "ASSETS/IMAGES/WorldItems";


    std::vector<Texture*> textures = loader->loadAllTexturesInFile(basePath);

    for (int k = 0; k < textures.size(); k++)
    {
        m_quantity++;

        m_items.push_back({ textures[k]});
    }
}
