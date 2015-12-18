#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include "rapidxml.hpp"
#include <map>
#include "Trigger.h"

using namespace std;

class Container {

public:
	Container(rapidxml::xml_node<>*);
	//virtual ~Container();

	string name;
	string description;
	string status;
	bool opened;
	Trigger* trigger;

	vector<string> accepted;
	vector<string> items;
	//trigger






};


#endif 

