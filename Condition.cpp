#include "Condition.h"

Condition::Condition(rapidxml::xml_node<>* conditionNode) {
	string xmlname;
	string xmldata;

	conditionNode = conditionNode->first_node();
	while (conditionNode != NULL) {
		xmlname = conditionNode->name();
		xmldata = conditionNode->value();


		if (xmlname == "object")
			this->object = xmldata;

		else if (xmlname == "status")
			this->status = xmldata;

		else if (xmlname == "has" )
			this->has = xmldata;

		else if (xmlname == "owner")
			this->owner = xmldata;

		conditionNode = conditionNode->next_sibling();
	}




}