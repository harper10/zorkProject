#ifndef ZORK_GAMEENGINE_H_
#define ZORK_GAMEENGINE_H_

#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <algorithm>

#include "Room.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include <map>
#include <stack>
#include <vector>
#include "Zork_ResourceManager.h"
#include "Condition.h"
#include "Trigger.h"

using namespace std;

class Zork_GameEngine {

public:

	Zork_ResourceManager resourceManager;
	//map<string, Room*>::iterator roomIt;



	Zork_GameEngine(Zork_ResourceManager &resourceManager);
	void BootGame();

private:

	string currentroom;
	string input;
	bool gameover;
	bool backend;
	bool triggered;
	vector <string> inventory;
	map<string, Room*>::iterator roomIt;
	map<string, Item*>::iterator itemIt;
	map<string, Container*>::iterator containerIt;
	map<string, Creature*>::iterator creatureIt;

	Room* currentRoomdata;



	void userInput(string input);
	void move(string input);
	void openInventory();
	void takeItem(string input);
	void openContainer(string input);
	void readItem(string input);
	void dropItem(string input);
	void putItem(string itInput, string conInput);
	void turnOnItem(string input);
	void openExit();
	void attack(string creInput, string itInput);
	void Addcommand(string obj, string rorc);
	void Deletecommand(string input);
	void Updatecommand(string obj, string statinput);
	bool handleCondition(vector<Condition*>conditions);
	void checkTriggers();
	void commandTriggers(string input);
};

#endif