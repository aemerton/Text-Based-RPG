#include "Monster.h"
#include "Player.h"
#include "UnitIO.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Player* UnitIO::read_player() {//reads from text file and sets up a player object

	std::string name, health, attack, line;	//temperary variables
	int health_ = 0;
	int attack_ = 0;
	int level = 1;
	int exp = 0; 
	int won = 0;
	int lost = 0;

	std::ifstream myFile;
	myFile.open("player_info.txt");	//open the file

	getline(myFile, line);	//get the line from the file

	std::stringstream s(line);	//put it into a string stream to ease management 

	getline(s, name, ' ');	//fill our temp variables, (some default to 0 or 1 so no reason to read them in from a text file)

	getline(s, attack, ' ');
	attack_ = stoi(attack);

	getline(s, health, ' ');
	health_ = stoi(health);

	Player* p = new Player(name, health_, attack_, exp, level, won, lost);	//create pointer to a player object
	
	return p; //return the pointer to main
}

Monster* UnitIO::read_monster(int type) {	//does the same exact thing as the read_player function except has a switch statement 
											// to determine which text file gets opened (there is one for goblin, wolf, and ogre
		std::string name, health, attack, dialogue, line;
		int health_ = 0;
		int attack_ = 0;

		std::ifstream myFile;

		switch (type) {
		case 1:
			myFile.open("goblin.txt");
			break;
		case 2:
			myFile.open("wolf.txt");
			break;
		case 3:
			myFile.open("ogre.txt");
			break;
		}

		getline(myFile, line);

		std::stringstream s(line);

		getline(s, name, ' ');

		getline(s, health, ' ');
		health_ = stoi(health);

		getline(s, attack, '\t');
		attack_ = stoi(attack);

		getline(s, dialogue, '\n');

		Monster* m = new Monster(name, health_, attack_, dialogue);
		

		return m;
	
}
