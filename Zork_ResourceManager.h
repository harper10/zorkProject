#ifndef ZORK_RESOURCEMANAGER_H_
#define ZORK_RESOURCEMANAGER_H_


#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "rapidxml.hpp"
#include "Room.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include <map>
#include <stack>
#include <iterator>
#include <sstream>


using namespace std;
using namespace rapidxml;

class Zork_ResourceManager {

public:
	map<string, Room*> rooms;
	map<string, Item*> items;
	map<string, Container*> containers;
	map<string, Creature*> creatures;

	Zork_ResourceManager(string);
	Zork_ResourceManager();
	//virtual ~Zork_ResourceManager();

private:
	bool ParseXML(string filename);
	void Scantypenodes(string type, xml_node<> *node, stack<xml_node<> *> &tempstack);



};


#endif 