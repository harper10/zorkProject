#ifndef ROOM_H_
#define ROOM_H_

#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include "rapidxml.hpp"
#include <map>
#include "Trigger.h"

using namespace std;

class Room {

public:
	Room(rapidxml::xml_node<>*);
	//virtual ~Room();

	string name;
	string description;
	string type;
	string status;
	Trigger* trigger;
	bool gameover;

	vector<string> items;
	vector<string> containers;
	vector<string> creatures;
	map<string, string> borders;






};


#endif 




