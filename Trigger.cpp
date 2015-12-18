#include "Trigger.h"

Trigger::Trigger(rapidxml::xml_node<>* triggerNode)
{

	string xmlname;
	string xmldata;
	rapidxml::xml_node<> * condnode;
	this->used = true;
	triggerNode = triggerNode->first_node();

	while (triggerNode != NULL) {

		xmlname = triggerNode->name();
		xmldata = triggerNode->value();

		if (xmlname == "type")
			this->type = xmldata;
		else if (xmlname == "command")
			this->commands.push_back(xmldata);
		else if (xmlname == "print")
			this->triggerPrints.push_back(xmldata);
		else if (xmlname == "action")
			this->triggerActions.push_back(xmldata);
		else if (xmlname == "condition")
			this->conditions.push_back(new Condition(triggerNode));
		
		triggerNode = triggerNode->next_sibling();

	}
}
Trigger::Trigger()
{
	this->used = false;

}