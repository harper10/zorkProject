#include "Creature.h"

Creature::Creature(rapidxml::xml_node<>* creatureNode) {

	string xmlname;
	string xmldata;
	rapidxml::xml_node<> * attacknode;
	this->trigger = new Trigger();
	creatureNode = creatureNode->first_node();
	while (creatureNode != NULL) {
		xmlname = creatureNode->name();
		xmldata = creatureNode->value();

		
		if (xmlname == "name")
			this->name = xmldata;
		
		else if (xmlname == "status")
			this->status = xmldata;
			
		else if (xmlname == "description")
			this->description = xmldata;
		else if (xmlname == "vulnerability")
			this->vulnerabilities.push_back(xmldata);

		else if (xmlname == "attack") {
			attacknode = creatureNode->first_node();
			while (attacknode != NULL) {
				xmlname = attacknode->name();
				xmldata = attacknode->value();
				if (xmlname == "print")
					this->attackPrints.push_back(xmldata);
				else if (xmlname == "action")
					this->attackActions.push_back(xmldata);
				else if (xmlname == "condition")
				{
					this->conditions.push_back(new Condition(attacknode));

				}
				attacknode = attacknode->next_sibling();

			}


		}
		else if (xmlname == "trigger") {
			this->trigger = new Trigger(creatureNode);

		}

		creatureNode = creatureNode->next_sibling();
		}



	}







