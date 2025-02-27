#include "Librarys/WorldItemLibrary.h"
WorldItemLibrary* WorldItemLibrary::instance = nullptr;

WorldItemLibrary::WorldItemLibrary()
{

}

WorldItemLibrary* WorldItemLibrary::getInstance()
{

    if (instance == nullptr)
    {
        instance = new WorldItemLibrary();
    }
    return instance;
}

void WorldItemLibrary::setFunction(std::function<void(SceneType)> t_sceneChangeFunction)
{
    m_sceneChangeFunction = t_sceneChangeFunction;
}

WorldItem* WorldItemLibrary::getItem(int t_index)
{
    return m_items[t_index];
}

void WorldItemLibrary::loadTextures()
{

    Loader* loader = Loader::getInstance();

    std::string basePath = "ASSETS/IMAGES/WorldItems";


    std::vector<Texture*> textures = loader->loadAllTexturesInFile(basePath);

    for (int k = 0; k < textures.size(); k++)
    {
        m_quantity++;
        if (k == 0)
        {
            m_items.push_back(new PlayerInteractableItem(textures[k], m_sceneChangeFunction));
            m_items[k]->setPurpose(Purpose::PlayerInteractable);
        }
        else if (k == 2)
        {
            m_items.push_back(new PlayerInteractableItem(textures[k], m_sceneChangeFunction));
            m_items[k]->setPurpose(Purpose::PlayerInteractable);

            PlayerInteractableItem* item = static_cast<PlayerInteractableItem*>(m_items[k]);
            item->setTargetScene(RoomBuilder);
        }
        else
        {
            m_items.push_back(new WorldItem(textures[k]));
            m_items[k]->setPurpose(Purpose::Resource);
        }
        
    }
}
