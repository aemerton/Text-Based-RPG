#ifndef UNIT_H
#define UNIT_H
#include <string>


class Unit {//class declaration, parent class of the Player and Monster class

protected:
	int health;//data members
	int attack;
	std::string name;

public:
	Unit(std::string name_, int health_, int attack_);//constructor
	virtual void update();	//virtual function to be overridden by the sub classes
};

#endif