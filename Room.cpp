#include "Room.h"

Room::Room(rapidxml::xml_node<>* roomNode) {

	string xmlname;
	string xmldata;
	rapidxml::xml_node<> * bordernode;
	string direction;
	string bordername;
	this->trigger = new Trigger();
	roomNode = roomNode->first_node();

	while (roomNode != NULL) {
		xmlname = roomNode->name();
		xmldata = roomNode->value();

		
		if (xmlname == "name")
			this->name = xmldata;

		else if (xmlname == "description")
			this->description = xmldata;

		else if (xmlname == "status")
			this->status = xmldata;

		else if (xmlname == "type")
			this->type = xmldata;
		else if (xmlname == "item")
			this->items.push_back(xmldata);
		
		else if (xmlname ==  "creature")
			this->creatures.push_back(xmldata);
			
		else if (xmlname == "container")
			this->containers.push_back(xmldata);
			
		else if (xmlname == "border") {
			bordernode = roomNode->first_node();
			while (bordernode != NULL) {
				xmlname = bordernode->name();
				xmldata = bordernode->value();
				if (xmlname == "direction")
					direction = xmldata;
				else if (xmlname == "name")
					bordername = xmldata;
				bordernode = bordernode->next_sibling();

			}
			this->borders[direction] = bordername;
		}
		else if (xmlname == "trigger") {
			this->trigger = new Trigger(roomNode);

		}
		roomNode = roomNode->next_sibling();
		}

					
		
				
	}
		






