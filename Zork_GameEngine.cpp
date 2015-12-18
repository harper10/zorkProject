#include "Zork_GameEngine.h"

Zork_GameEngine::Zork_GameEngine(Zork_ResourceManager &resourceManager) {
	
	this->resourceManager = resourceManager;
	
	

	

}

void Zork_GameEngine::BootGame()
{
	currentroom = "Entrance";

	roomIt = resourceManager.rooms.find(currentroom);
	triggered = false;
	gameover = false;
	cout << roomIt->second->description << endl;
	//check trigger
	checkTriggers();
	triggered = false;
	while (!gameover)
	{
		getline(cin, input);
		userInput(input);

		
	}


}

void Zork_GameEngine::userInput(string input)
{
	
	if (!input.empty()) {
		istringstream buffer(input);
		istream_iterator<std::string> start(buffer), end;
		vector<string> inputs(start, end);
		if (!triggered)
			commandTriggers(input);
		else {
			if (input == "n" || input == "e" || input == "s" || input == "w")
				move(input);
			else if (input == "i")
				openInventory();
			else if (input == "open exit")
				openExit();
			else if ((inputs[0] == "take") && (inputs.size() == 2))
				takeItem(inputs[1]);
			else if ((inputs[0] == "open") && (inputs.size() == 2))
				openContainer(inputs[1]);
			else if ((inputs[0] == "read") && (inputs.size() == 2))
				readItem(inputs[1]);
			else if ((inputs[0] == "drop") && (inputs.size() == 2))
				dropItem(inputs[1]);
			else if ((inputs[0] == "put") && (inputs[2] == "in") && (inputs.size()== 4))
				putItem(inputs[1], inputs[3]);
			else if ((inputs[0] == "turn") && (inputs[1] == "on") && (inputs.size() == 3))
				turnOnItem(inputs[2]);
			else if ((inputs[0] == "attack") && (inputs[2] == "with") && (inputs.size() == 4))
				attack(inputs[1], inputs[3]);
			//else
				//cout << "I dont understand Dave " << endl;
			else if (backend)
			{
				if ((inputs[0] == "Add") && (inputs[2] == "to"))
					Addcommand(inputs[1], inputs[3]);
				else if (inputs[0] == "Delete")
					Deletecommand(inputs[1]);
				else if ((inputs[0] == "Update") && (inputs[2] == "to"))
					Updatecommand(inputs[1], inputs[3]);
				else if (input == "Game Over")
					gameover = true;


			}
			else
				cout << "I dont understand Dave " << endl;
			checkTriggers();
			triggered = false;
		}
	}
	else
		cout << "error" << endl;
	
	//cout << "print" << endl;
}

void Zork_GameEngine::move(string input)
{
	currentRoomdata = resourceManager.rooms.find(currentroom)->second;
	map<string, string>::iterator it;
	
	if (input == "n")
	{
		it = currentRoomdata->borders.find("north");
		if (it != currentRoomdata->borders.end())
		{
			currentroom = it->second;
			currentRoomdata = resourceManager.rooms.find(currentroom)->second;
			//check trigger
			cout << currentRoomdata->description << endl;
		}
		else
			cout << "Can't go that way" << endl;
	}
	else if (input == "s")
	{
		it = currentRoomdata->borders.find("south");
		if (it != currentRoomdata->borders.end())
		{
			currentroom = it->second;
			currentRoomdata = resourceManager.rooms.find(currentroom)->second;
			//check trigger
			cout << currentRoomdata->description << endl;
		}
		else
			cout << "Can't go that way" << endl;
	}
	else if (input == "w")
	{
		it = currentRoomdata->borders.find("west");
		if (it != currentRoomdata->borders.end())
		{
			currentroom = it->second;
			currentRoomdata = resourceManager.rooms.find(currentroom)->second;
			//check trigger
			cout << currentRoomdata->description << endl;
		}
		else
			cout << "Can't go that way" << endl;
	}
	else if (input == "e")
	{
		it = currentRoomdata->borders.find("west");
		if (it != currentRoomdata->borders.end())
		{
			currentroom = it->second;
			currentRoomdata = resourceManager.rooms.find(currentroom)->second;
			//check trigger
			cout << currentRoomdata->description << endl;
		}
		else
			cout << "Can't go that way" << endl;
	}
}

void Zork_GameEngine::openInventory()
{
	if (inventory.empty())
		cout << "Inventory: empty" << endl;
	else {
		cout << "Inventory: ";
		for (vector<string>::iterator invit = inventory.begin(); invit != inventory.end(); ++invit)
		{
			cout << *invit << " ";
		}
		cout << endl;
	}
}

void Zork_GameEngine::takeItem(string input)
{
	currentRoomdata = resourceManager.rooms.find(currentroom)->second;
	vector<string>::iterator it;
	vector<string>::iterator it2;
	Container* currentContainer;
	bool flag = false;
	
	it = find(currentRoomdata->items.begin(), currentRoomdata->items.end(), input);
	it2 = currentRoomdata->containers.begin();
	if (it != currentRoomdata->items.end())
	{
		inventory.push_back(input);
		currentRoomdata->items.erase(it);
		flag = true;
		//check trigger

	}
	else {
		for (it2; it2 != currentRoomdata->containers.end(); ++it2)
		{
			currentContainer = resourceManager.containers.find(*it2)->second;
			if (currentContainer->opened)
			{
				vector<string>::iterator it3;
				it3 = find(currentContainer->items.begin(), currentContainer->items.end(), input);
				if (it3 != currentContainer->items.end())
				{
					if (currentContainer->opened) {
						flag = true;
						inventory.push_back(input);
						currentContainer->items.erase(it3);
						break;
					}
				}
			}

			
		}
			
	}
	if (!flag)
		cout << "That item is not in the room/container" << endl;
	else
		cout << "Item " << input << " added to inventory" << endl;

}

void Zork_GameEngine::openContainer(string input)
{
	currentRoomdata = resourceManager.rooms.find(currentroom)->second;
	vector<string>::iterator it;
	vector<string>::iterator it2;

	Container* currentContainer;
	it = find(currentRoomdata->containers.begin(), currentRoomdata->containers.end(), input);

	if (it != currentRoomdata->containers.end()) {
		currentContainer = resourceManager.containers.find(input)->second;
		currentContainer->opened = true;
		if (currentContainer->items.empty())
			cout << input << " is empty" << endl;
		else {
			cout << input << " contains";
			for (it2 = currentContainer->items.begin(); it2 != currentContainer->items.end(); ++it2)
			{
				cout << " " << *it2;
				if (!(it2 + 1 == currentContainer->items.end()))
					cout << ",";
			}
			cout << endl;
		}
	}

	else
		cout << "That container is not in this room" << endl;

}  

void Zork_GameEngine::readItem(string input)
{
	vector<string>::iterator it;
	Item* currentItem;

	it = find(inventory.begin(), inventory.end(), input);

	if (it != inventory.end())
	{
		currentItem = resourceManager.items.find(input)->second;
		if (currentItem->writing.empty())
			cout << "Nothing Written" << endl;
		else
			cout << currentItem->writing << endl;

	}
	else
		cout << "That item is not in your inventory" << endl;
}

void Zork_GameEngine::dropItem(string input)
{
	vector<string>::iterator it;
	Item* currentItem;
	currentRoomdata = resourceManager.rooms.find(currentroom)->second;

	it = find(inventory.begin(), inventory.end(), input);

	if (it != inventory.end())
	{
		currentRoomdata->items.push_back(input);
		inventory.erase(it);
		cout << input << " dropped" << endl;
	}
	else
		cout << "That item is not in your inventory" << endl;

}

void Zork_GameEngine::putItem(string itInput, string conInput)
{
	vector<string>::iterator it;
	vector<string>::iterator it2;

	currentRoomdata = resourceManager.rooms.find(currentroom)->second;
	it = find(inventory.begin(), inventory.end(), itInput);

	if (it == inventory.end())
		cout << "That item is not in your inventory" << endl;
	else {
		it2 = find(currentRoomdata->containers.begin(), currentRoomdata->containers.end(), conInput);
		if (it2 == currentRoomdata->containers.end())
			cout << "That container is not in this room" << endl;
		else {
			cout << "You place " << itInput << " in " << conInput << endl;
			resourceManager.containers.find(conInput)->second->items.push_back(itInput);
			inventory.erase(it);

		}

	}

}
void Zork_GameEngine::turnOnItem(string input)
{
	vector<string>::iterator it;
	
	Item* currentItem;

	it = find(inventory.begin(), inventory.end(), input);

	if (it != inventory.end())
	{
		currentItem = resourceManager.items.find(input)->second;
		vector<string>::iterator it2;
		vector<string>::iterator it3;

		it2 = currentItem->turnonActions.begin();
		it3 = currentItem->turnonPrints.begin();
		if (it3 != currentItem->turnonPrints.end())
		{

			for (it3; it3 != currentItem->turnonPrints.end(); ++it3)
			{

				cout<< *it3 << endl;

			}
		}
		if (it2 != currentItem->turnonActions.end())
		{

			for (it2; it2 != currentItem->turnonActions.end(); ++it2)
			{
				backend = true;
				userInput(*it2);
				
			}
		}

	}
	else
		cout << "That item is not in your inventory" << endl;

}
void Zork_GameEngine::attack(string creInput, string itInput)
{
	vector<string>::iterator it;
	Creature* currentCreature;
	Item* currentItem;
	Item* condItem;
	currentRoomdata = resourceManager.rooms.find(currentroom)->second;
	it = find(inventory.begin(), inventory.end(), itInput);
	if(it == inventory.end())
		cout << "That item is not in your inventory" << endl;
	else {
		vector<string>::iterator it2;
		it2 = find(currentRoomdata->creatures.begin(), currentRoomdata->creatures.end(), creInput);
		if (it2 == currentRoomdata->creatures.end())
			cout << "That creature is not in this area" << endl;
		else
		{
			currentCreature = resourceManager.creatures.find(creInput)->second;
			currentItem = resourceManager.items.find(itInput)->second;
			vector<string>::iterator it3;
			for (it3 = currentCreature->vulnerabilities.begin(); it3 != currentCreature->vulnerabilities.end(); ++it3)
			{
			  //cout << "hi" << endl;
				if (*it3 == itInput)
				{
				  //cout << "hi" << endl;
					if (currentCreature->conditions.empty() || handleCondition(currentCreature->conditions))
					{
						vector<string>::iterator it4;
						vector<string>::iterator it5;
						it4 = currentCreature->attackActions.begin();
						it5 = currentCreature->attackPrints.begin();
						if (it5 != currentCreature->attackPrints.end())
						{

							for (it5; it5 != currentCreature->attackPrints.end(); ++it5)
							{
								cout << *it5 << endl;

							}
						}
						if (it4 != currentCreature->attackActions.end())
						{

							for (it4; it4 != currentCreature->attackActions.end(); ++it4)
							{
								backend = true;
								userInput(*it4);

							}
						}

						break;
					}
				}

			}

		}

		}
}

void Zork_GameEngine::Addcommand(string obj, string rorc)
{
	itemIt = resourceManager.items.find(obj);
	containerIt = resourceManager.containers.find(obj);
	creatureIt = resourceManager.creatures.find(obj);
	if (itemIt != resourceManager.items.end())
	{
		if (resourceManager.rooms.find(rorc) != resourceManager.rooms.end())
			resourceManager.rooms.find(rorc)->second->items.push_back(obj);
		else
			resourceManager.containers.find(rorc)->second->items.push_back(obj);
	}
	else if (containerIt != resourceManager.containers.end())
	{
		if (resourceManager.rooms.find(rorc) != resourceManager.rooms.end())
			resourceManager.rooms.find(rorc)->second->containers.push_back(obj);
	}
	else if (creatureIt != resourceManager.creatures.end())
	{
		if (resourceManager.rooms.find(rorc) != resourceManager.rooms.end())
			resourceManager.rooms.find(rorc)->second->creatures.push_back(obj);
		
	}
	backend = false;
}
void Zork_GameEngine::Deletecommand(string input)
{
	Room* roomtemp;
	roomIt = resourceManager.rooms.begin();
	Container* contemp;
	containerIt = resourceManager.containers.begin();
	

	for (containerIt; containerIt != resourceManager.containers.end(); ++containerIt)
	{
		vector<string>::iterator it;
		contemp = containerIt->second;
		it = find(contemp->items.begin(), contemp->items.end(), input);
		if (it != contemp->items.end())
			contemp->items.erase(it);
	}

	for (roomIt; roomIt != resourceManager.rooms.end(); ++roomIt)
	{
		vector<string>::iterator it;
		vector<string>::iterator it2;
		vector<string>::iterator it3;
		roomtemp = roomIt->second;
		it = find(roomtemp->items.begin(), roomtemp->items.end(), input);
		if (it != roomtemp->items.end())
			roomtemp->items.erase(it);
		it2 = find(roomtemp->creatures.begin(), roomtemp->creatures.end(), input);
		if (it2 != roomtemp->creatures.end())
			roomtemp->creatures.erase(it2);
		it3 = find(roomtemp->containers.begin(), roomtemp->containers.end(), input);
		if (it3 != roomtemp->containers.end())
			roomtemp->containers.erase(it3);
		
	}
	backend = false;
}
void Zork_GameEngine::Updatecommand(string obj, string statinput)
{
	itemIt = resourceManager.items.find(obj);
	containerIt = resourceManager.containers.find(obj);
	creatureIt = resourceManager.creatures.find(obj);
	roomIt = resourceManager.rooms.find(obj);

	if (itemIt != resourceManager.items.end())
		itemIt->second->status = statinput;
	else if (containerIt != resourceManager.containers.end())
		containerIt->second->status = statinput;
	else if (creatureIt != resourceManager.creatures.end())
		creatureIt->second->status = statinput;
	else if (roomIt != resourceManager.rooms.end())
		roomIt->second->status = statinput;
	
	backend = false;
}



bool Zork_GameEngine::handleCondition(vector<Condition*>conditions)
{
	vector<Condition*>::iterator it;
	//cout << "hi" << endl;
	it = conditions.begin();
	//cout << "hi" << endl;
	vector<string>::iterator it2;
	vector<string>::iterator it3;
	for (it; it != conditions.end(); ++it)
	{
		if ((*it)->owner.empty())
		{

			//cout << "1" << endl;
			if (resourceManager.items.find((*it)->object) != resourceManager.items.end())
			{
				//cout << "2" << endl;
				if (resourceManager.items.find((*it)->object)->second->status == (*it)->status)
					return true;
			}
			else if (resourceManager.rooms.find((*it)->object) != resourceManager.rooms.end())
			{
				if(resourceManager.rooms.find((*it)->object)->second->status == (*it)->status)
					return true;
			}
			else if (resourceManager.creatures.find((*it)->object) != resourceManager.creatures.end())
			{
				if (resourceManager.creatures.find((*it)->object)->second->status == (*it)->status)
					return true;
			}
			else if (resourceManager.containers.find((*it)->object) != resourceManager.containers.end())
			{
				//cout << "it hit" << endl;
				if (resourceManager.containers.find((*it)->object)->second->status == (*it)->status)
					return true;
				else
					return false;
			}




		}
		else if ((*it)->owner == "inventory")
		{
			it3 = find(inventory.begin(), inventory.end(), (*it)->object);
			if (it3 != inventory.end())
			{
				if ((*it)->has == "yes")
				 {
				   cout << "hi" << endl; 
					return true;
					
				 }
				else
					return false;
			}
			else
				return false;
		}
		else
		{
			
				if (resourceManager.rooms.find((*it)->owner) != resourceManager.rooms.end())
				{
					if (find(resourceManager.rooms.find((*it)->owner)->second->items.begin(), resourceManager.rooms.find((*it)->owner)->second->items.end(), (*it)->object) != resourceManager.rooms.find((*it)->owner)->second->items.end())
					{
						//cout << "1" << endl;
						if ((*it)->has == "yes")
							return true;
						else
							return false;
					}
				}
		
				else if (resourceManager.containers.find((*it)->owner) != resourceManager.containers.end())
				{
					//cout << "3" << endl;
					if (find(resourceManager.containers.find((*it)->owner)->second->items.begin(), resourceManager.containers.find((*it)->owner)->second->items.end(), (*it)->object) != resourceManager.containers.find((*it)->owner)->second->items.end())
					{
						//cout << "2" << endl;
						if ((*it)->has == "yes")
							return true;
						else
							return false;
					}
				}
			
		}
	}
	return false;
}

void Zork_GameEngine::checkTriggers()
{
	Room* currRoom = resourceManager.rooms.find(currentroom)->second;
	Item* item;
	Creature* creature;
	Container* container;
	vector<string>::iterator it;
	vector<string>::iterator it5;
	vector<string>::iterator it6;
	vector<string>::iterator it10;
	//bool temp = false;
	if (currRoom->trigger->used != false)
	{
		if (currRoom->trigger->commands.empty())
		{
			if (!handleCondition(currRoom->trigger->conditions))
			{
				//triggered = true;
				//userInput(input);
				//triggered = false;
				//return;
				//temp = false;
			}
			else {
				triggered = true;
				if (currRoom->trigger->type != "permanent")
					currRoom->trigger->used = false;
				vector<string>::iterator it3;
				vector<string>::iterator it4;
				for (it3 = currRoom->trigger->triggerPrints.begin(); it3 != currRoom->trigger->triggerPrints.end(); ++it3)
				{
					cout << *it3 << endl;

				}
				for (it4 = currRoom->trigger->triggerActions.begin(); it4 != currRoom->trigger->triggerActions.end(); ++it4)
				{
					triggered = true;
					backend = true;
					userInput(*it4);
				}
				triggered = false;
				//return;
				//temp = true;

			}
		}
	}
	
	for (it = currRoom->items.begin(); it != currRoom->items.end(); ++it)
	{
		item = resourceManager.items.find(*it)->second;
		if (item->trigger->used != false)
		{
			if (item->trigger->commands.empty())
			{
				if (!handleCondition(item->trigger->conditions))
				{
					//triggered = true;
					//serInput(input);
					//return;
					//temp = false;
				}
				else {
					triggered = true;
					if (item->trigger->type != "permanent")
						item->trigger->used = false;
					vector<string>::iterator it3;
					vector<string>::iterator it4;
					for (it3 = item->trigger->triggerPrints.begin(); it3 != item->trigger->triggerPrints.end(); ++it3)
					{
						cout << *it3 << endl;

					}
					for (it4 = item->trigger->triggerActions.begin(); it4 != item->trigger->triggerActions.end(); ++it4)
					{
						triggered = true;
						backend = true;
						userInput(*it4);
					}
					triggered = false;
					//temp = true;

				}
			}
		}
	}
	for (it10 = inventory.begin(); it10 != inventory.end(); ++it10)
	{
		item = resourceManager.items.find(*it10)->second;
		if (item->trigger->used != false)
		{
			if (item->trigger->commands.empty())
			{
				if (!handleCondition(item->trigger->conditions))
				{
					//triggered = true;
					//serInput(input);
					//return;
					//temp = false;
				}
				else {
					triggered = true;
					if (item->trigger->type != "permanent")
						item->trigger->used = false;
					vector<string>::iterator it3;
					vector<string>::iterator it4;
					for (it3 = item->trigger->triggerPrints.begin(); it3 != item->trigger->triggerPrints.end(); ++it3)
					{
						cout << *it3 << endl;

					}
					for (it4 = item->trigger->triggerActions.begin(); it4 != item->trigger->triggerActions.end(); ++it4)
					{
						triggered = true;
						backend = true;
						userInput(*it4);
					}
					triggered = false;
					//temp = true;

				}
			}
		}
	}
	
	for (it5 = currRoom->containers.begin(); it5 != currRoom->containers.end(); ++it5)
	{
		container = resourceManager.containers.find(*it5)->second;
		if (container->trigger->used != false)
		{
			if (container->trigger->commands.empty())
			{
				if (!handleCondition(container->trigger->conditions))
				{
					//triggered = true;
					//userInput(input);
					//triggered = false;
					//return;
				}
				else {
					triggered = true;
					if (container->trigger->type != "permanent")
					{
						container->trigger->used = false;
					}
					vector<string>::iterator it13;
					vector<string>::iterator it14;
					for (it13 = container->trigger->triggerPrints.begin(); it13 != container->trigger->triggerPrints.end(); it13++)
					{
						cout << *it13 << endl;
						//cout << "hi" << endl;
					}
					//cout << "help" << endl;
					for (it14 = container->trigger->triggerActions.begin(); it14 != container->trigger->triggerActions.end(); it14++)
					{
						backend = true;
						triggered = true;
						userInput(*it14);
					
					} 
					triggered = false;
					//return;
					//temp = true;
				}
			}
		}
	}
	

	for (it6 = currRoom->creatures.begin(); it6 != currRoom->creatures.end(); ++it6)
	{
		creature = resourceManager.creatures.find(*it6)->second;
		if (creature->trigger->used != false)
		{
			if (creature->trigger->commands.empty())
			{
				if (!handleCondition(creature->trigger->conditions))
				{
					//triggered = true;
					//userInput(input);
					//triggered = false;
					//return;
					//temp = false;
				}
				else {
					triggered = true;
					if (creature->trigger->type != "permanent")
						creature->trigger->used = false;
					vector<string>::iterator it3;
					vector<string>::iterator it4;
					for (it3 = creature->trigger->triggerPrints.begin(); it3 != creature->trigger->triggerPrints.end(); ++it3)
					{
						cout << *it3 << endl;

					}
					for (it4 = creature->trigger->triggerActions.begin(); it4 != creature->trigger->triggerActions.end(); ++it4)
					{
						triggered = true;
						backend = true;
						userInput(*it4);
					}
					triggered = false;
					//return;
					//temp = true;

				}
			}
		}
	}


}
void Zork_GameEngine::commandTriggers(string input)
{
	//cout << "5" << endl;
	Room* currRoom = resourceManager.rooms.find(currentroom)->second;
	Item* item;
	bool temp = false;
	Creature* creature;
	Container* container;
	vector<string>::iterator it;

	vector<string>::iterator it5;
	vector<string>::iterator it6;
	vector<string>::iterator it7;
	vector<string>::iterator it8;
	vector<string>::iterator it10;
	vector<string>::iterator it11;
	if (currRoom->trigger->used != false) {
		for (it = currRoom->trigger->commands.begin(); it != currRoom->trigger->commands.end(); ++it)
		{
			if (*it == input)
			{
				//cout << "6" << endl;
				if (!handleCondition(currRoom->trigger->conditions))
				{
					//cout << "7" << endl;
					//triggered = true;
					//userInput(input);
					//triggered = false;
					//return;
					//temp = false;
				}
				else {
					triggered = true;
					if (currRoom->trigger->type != "permanent")
						currRoom->trigger->used = false;
					vector<string>::iterator it3;
					vector<string>::iterator it4;
					//cout << "8" << endl;
					for (it3 = currRoom->trigger->triggerPrints.begin(); it3 != currRoom->trigger->triggerPrints.end(); ++it3)
					{
						cout << *it3 << endl;

					}
					for (it4 = currRoom->trigger->triggerActions.begin(); it4 != currRoom->trigger->triggerActions.end(); ++it4)
					{
						triggered = true;
						backend = true;
						userInput(*it4);
					}
					triggered = false;
					//return;
					temp = true;
				}
			}
		}
	}
	for (it5 = currRoom->items.begin(); it5 != currRoom->items.end(); ++it5)
	{
		item = resourceManager.items.find(*it5)->second;
		vector<string>::iterator it6;
		if (item->trigger->used != false) {
			for (it6 = item->trigger->commands.begin(); it6 != item->trigger->commands.end(); ++it6)
			{
				if (*it6 == input)
				{
					if (!handleCondition(item->trigger->conditions))
					{
						//triggered = true;
						//userInput(input);
						//triggered = false;
						//return;
						//temp = false;
					}
					else {
						triggered = true;
						if (item->trigger->type != "permanent")
							item->trigger->used = false;
						vector<string>::iterator it3;
						vector<string>::iterator it4;
						for (it3 = item->trigger->triggerPrints.begin(); it3 != item->trigger->triggerPrints.end(); ++it3)
						{
							cout << *it3 << endl;

						}
						for (it4 = item->trigger->triggerActions.begin(); it4 != item->trigger->triggerActions.end(); ++it4)
						{
							triggered = true;
							backend = true;
							userInput(*it4);
						}
						triggered = false;
						//return;
						temp = true;
					}
				}
			}
		}
	}
	for (it10 = inventory.begin(); it10 != inventory.end(); ++it10)
	{
		item = resourceManager.items.find(*it10)->second;

		if (item->trigger->used != false) {
			for (it11 = item->trigger->commands.begin(); it11 != item->trigger->commands.end(); ++it11)
			{
				if (*it11 == input)
				{
					if (!handleCondition(item->trigger->conditions))
					{
						//triggered = true;
						//userInput(input);
						//triggered = false;
						//return;
						//temp = false;
					}
					else {
						triggered = true;
						if (item->trigger->type != "permanent")
							item->trigger->used = false;
						vector<string>::iterator it3;
						vector<string>::iterator it4;
						for (it3 = item->trigger->triggerPrints.begin(); it3 != item->trigger->triggerPrints.end(); ++it3)
						{
							cout << *it3 << endl;

						}
						for (it4 = item->trigger->triggerActions.begin(); it4 != item->trigger->triggerActions.end(); ++it4)
						{
							triggered = true;
							backend = true;
							userInput(*it4);
						}
						triggered = false;
						//return;
						temp = true;

					}
				}
			}
		}
	}

	for (it7 = currRoom->containers.begin(); it7 != currRoom->containers.end(); ++it7)
	{
		container = resourceManager.containers.find(*it7)->second;
		vector<string>::iterator it2;
		if (container->trigger->used != false) {
			for (it2 = container->trigger->commands.begin(); it2 != container->trigger->commands.end(); ++it2)
			{
				if (*it2 == input)
				{
					if (!handleCondition(container->trigger->conditions))
					{
						//triggered = true;
						//userInput(input);
						//triggered = false;
						//return;
							//temp = false;
					}
					else {
						triggered = true;
						if (container->trigger->type != "permanent")
							container->trigger->used = false;
						vector<string>::iterator it3;
						vector<string>::iterator it4;
						for (it3 = container->trigger->triggerPrints.begin(); it3 != container->trigger->triggerPrints.end(); ++it3)
						{
							cout << *it3 << endl;
							
						}
						for (it4 = container->trigger->triggerActions.begin(); it4 != container->trigger->triggerActions.end(); ++it4)
						{
							triggered = true;
							
							backend = true;
							userInput(*it4);
						}
						triggered = false;
						//return;
						temp = true;

					}
				}
			}
		}
		for (it8 = currRoom->creatures.begin(); it8 != currRoom->creatures.end(); ++it8)
		{
			creature = resourceManager.creatures.find(*it8)->second;
			vector<string>::iterator it2;
			if (creature->trigger->used != false) {
				for (it2 = creature->trigger->commands.begin(); it2 != creature->trigger->commands.end(); ++it2)
				{
					if (*it2 == input)
					{
						if (!handleCondition(creature->trigger->conditions))
						{
							//triggered = true;
							//userInput(input);
							//temp = false;
							//triggered = false;
							//return;
						}
						else {
							triggered = true;
							if (creature->trigger->type != "permanent")
								creature->trigger->used = false;
							vector<string>::iterator it3;
							vector<string>::iterator it4;
							for (it3 = creature->trigger->triggerPrints.begin(); it3 != creature->trigger->triggerPrints.end(); ++it3)
							{
								cout << *it3 << endl;

							}
							for (it4 = creature->trigger->triggerActions.begin(); it4 != creature->trigger->triggerActions.end(); ++it4)
							{
								triggered = true;
								backend = true;
								userInput(*it4);
							}
							triggered = false;
							//return;
							temp = true;

						}
					}
				}
			}
		}

	}
	if (temp == false)
	{
		triggered = true;
		userInput(input);
	}
}
void Zork_GameEngine::openExit()
{
	Room* temp = resourceManager.rooms.find(currentroom)->second;
	if(temp->type == "exit")
		gameover = true;
}
