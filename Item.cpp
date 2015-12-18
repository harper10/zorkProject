#include "Item.h"

Item::Item(rapidxml::xml_node<>* itemNode) {

	string xmlname;
	string xmldata;
	rapidxml::xml_node<> * turnnode;
	this->trigger = new Trigger();
	itemNode = itemNode->first_node();

	while (itemNode != NULL) {
		xmlname = itemNode->name();
		xmldata = itemNode->value();
	
		
		if (xmlname == "name")
			this->name = xmldata;
			
		else if(xmlname == "writing")
			this->writing = xmldata;
		
		else if(xmlname ==  "description")
			this->description = xmldata;

		else if(xmlname == "status")
			this->status = xmldata;
	
		else if (xmlname == "turnon") {
			turnnode = itemNode->first_node();
			while (turnnode != NULL) {
				xmlname = turnnode->name();
				xmldata = turnnode->value();
				if (xmlname == "print")
					this->turnonPrints.push_back(xmldata);
				else if (xmlname == "action")
					this->turnonActions.push_back(xmldata);
				turnnode = turnnode->next_sibling();

			}

		}
		else if (xmlname == "trigger") {
			this->trigger = new Trigger(itemNode);

		}
		itemNode = itemNode->next_sibling();
		}

		


	}








