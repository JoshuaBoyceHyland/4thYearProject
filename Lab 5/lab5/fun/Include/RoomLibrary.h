#pragma once
#include "Room.h"

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

	std::map<ResourceType, std::string> resourceString = {
																{ ResourceType::Electricty, "Electricity"},
																{ ResourceType::Happinness, "Happinness"},
																{ ResourceType::Water, "Water"},
																{ ResourceType::Oxygen, "Oxygen"}
	};

};