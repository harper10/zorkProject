#ifndef TRIGGER_H_
#define TRIGGER_H_

#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include "rapidxml.hpp"
#include <map>
#include "Condition.h"

class Trigger {
public:
	string type;
	bool used;
	vector<string> commands;
	vector<Condition*> conditions;
	vector<string> triggerPrints;
	vector<string> triggerActions;

	Trigger(rapidxml::xml_node<>*);
	Trigger();
};

#endif