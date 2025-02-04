#pragma once
#include "World/Room.h"
#include "Utility/FileReader.h"

class RoomLibrary
{
public:
	RoomLibrary(const Room& t_other) = delete;

	static RoomLibrary* getInstance();

	Room* getRoom(ResourceType t_type, int index);

	std::map<ResourceType, int> m_quantity;

private:

	RoomLibrary();

	void loadRooms();

	static RoomLibrary* instance;

	std::map< ResourceType, std::vector<Room>> m_rooms;
	std::vector< ResourceType> m_types = { ResourceType::Electricty/*, ResourceType::Happinness, ResourceType::Oxygen, ResourceType::Water, ResourceType::None*/ };
	std::map<ResourceType, std::string> m_resourceString = {
																{ ResourceType::None, "None"},
																{ ResourceType::Electricty, "Electricity"},
																{ ResourceType::Happinness, "Happinness"},
																{ ResourceType::Water, "Water"},
																{ ResourceType::Oxygen, "Oxygen"}
	};

};