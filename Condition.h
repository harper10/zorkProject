#ifndef CONDITION_H_
#define CONDITION_H_

#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include "rapidxml.hpp"
#include <map>

using namespace std;
class Condition {
public:
	string has;
	string object;
	string owner;
	string status;

	Condition(rapidxml::xml_node<>*);

};

#endif