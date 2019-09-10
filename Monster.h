#ifndef MONSTER_H
#define MONSTER_H
#include "Unit.h"
#include <string>


class Monster : public Unit { //Class declaration, inheriting Unit

private:
	std::string dialogue; //data memeber
	

public:
	static int monster_level;	//public memeber, and member functions
	Monster(std::string name_, int health_, int attack_, std::string dialogue_); //constructor
	void update(int type);	//overriting virutal function from Unit
	void operator = (Monster &p);
	int smite(); //enemy critical attack
	int get_hp();//getters
	int get_attack();
	std::string get_name();	
	std::string get_dialogue();
	
};

#endif

