#ifndef CREATURE_H_
#define CREATURE_H_

#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include "rapidxml.hpp"
#include <map>
#include "Condition.h"
#include "Trigger.h"

using namespace std;

class Creature {

public:
	Creature(rapidxml::xml_node<>*);
	//virtual ~Creature();

	string name;
	string description;
	string status;

	Trigger* trigger;

	vector<string> vulnerabilities;
	vector<string> attackPrints;
	vector<string> attackActions;
	vector<Condition*> conditions;
	//trigger

	




};


#endif 

#pragma once
