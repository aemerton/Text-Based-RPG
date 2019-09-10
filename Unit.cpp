#include "Unit.h"
#include <string>
using std::string;

Unit::Unit(string name_, int health_, int attack_) {//constructor

	name = name_;
	health = health_;
	attack = attack_;

}

void Unit::update() {//virutal function with no functionality, to be overridden by the sub classes
	return;
}

