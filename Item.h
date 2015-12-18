#ifndef ITEM_H_
#define ITEM_H_

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "rapidxml.hpp"
#include "Trigger.h"

using namespace std;

class Item {

public:
	Item(rapidxml::xml_node<> *);
	//virtual ~Item();

	string name;
	string writing;
	string description;
	string status;
	Trigger* trigger;

	vector<string> turnonPrints;
	vector<string> turnonActions;

	


};

#endif