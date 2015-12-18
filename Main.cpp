#include <iostream>
#include "Zork_ResourceManager.h"
#include "Zork_GameEngine.h"
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Please enter a Zork.xml file" << endl;
		return(1);
	}

	Zork_ResourceManager zr = Zork_ResourceManager(argv[1]);
	Zork_GameEngine Zork = Zork_GameEngine(zr);
	Zork.BootGame();

	return 0;

}