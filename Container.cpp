#include "Container.h"

Container::Container(rapidxml::xml_node<>* containerNode) {

	string xmlname;
	string xmldata;
	opened = false;
	this->trigger = new Trigger();
	containerNode = containerNode->first_node();
	while (containerNode != NULL) {
		xmlname = containerNode->name();
		xmldata = containerNode->value();

		
		if (xmlname == "name")
			this->name = xmldata;
			
		else if (xmlname == "status")
			this->status = xmldata;
			
		else if (xmlname == "description")
			this->description = xmldata;
			
		else if (xmlname == "item")
			this->items.push_back(xmldata);
			
		else if (xmlname == "accept")
			this->accepted.push_back(xmldata);
		else if (xmlname == "trigger")
			this->trigger = new Trigger(containerNode);
		
		containerNode = containerNode->next_sibling();
		}

	


	}








