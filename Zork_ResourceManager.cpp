#include "Zork_ResourceManager.h"

Zork_ResourceManager::Zork_ResourceManager(string filename)
{
	try {
		ParseXML(filename);
	}
	catch (int error) {
		cout << "Could not parse XML" << endl;
	}

}

Zork_ResourceManager::Zork_ResourceManager()
{
}

void Zork_ResourceManager::Scantypenodes(string type, xml_node<> *node, stack<xml_node<> *> &tempstack)
{
	while (node != NULL) {

		if (string((node->name())) == type) {
			tempstack.push(node);

		}
		node = node->next_sibling();
	}
}
 
bool Zork_ResourceManager::ParseXML(string filename)
{
	xml_document<> file;
	xml_node<> * rootnode;

	// Read the xml file into a vector
	ifstream theFile(filename);
	if (!theFile.is_open()) {
		cout << "Could not open File" << endl;///change this
		return false;
	}
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	file.parse<0>(&buffer[0]);

	// Find root node

	rootnode = file.first_node();

	stack<xml_node<> *> tempstack;

	xml_node<> *node = rootnode->first_node();

	Room* newRoom;
	Scantypenodes("room", node, tempstack);
	
	while ((tempstack.size()) > 0) {
		newRoom = new Room(tempstack.top());
		rooms[newRoom->name] = newRoom;
		tempstack.pop();

	}
	
	Item* newItem;
	Scantypenodes("item", node, tempstack);

	while ((tempstack.size()) > 0) {
		newItem = new Item(tempstack.top());
		items[newItem->name] = newItem;
		tempstack.pop();

	}
	Container* newContainer;
	Scantypenodes("container", node, tempstack);

	while ((tempstack.size()) > 0) {
		newContainer = new Container(tempstack.top());
		containers[newContainer->name] = newContainer;
		tempstack.pop();

	}
	Creature* newCreature;
	Scantypenodes("creature", node, tempstack);

	while ((tempstack.size()) > 0) {
		newCreature = new Creature(tempstack.top());
		creatures[newCreature->name] = newCreature;
		tempstack.pop();

	}


	return true;

}

