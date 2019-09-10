#ifndef UNITIO_H
#define UNITIO_H
#include "Monster.h"
#include "Player.h"

class UnitIO {

public:

	static Player* read_player();		// static functions to read information from a text file and initialize player and monster objects
	static Monster* read_monster(int type);	// the int parameter tells the function which text file to open of the three monster objects that will be created

};

#endif
