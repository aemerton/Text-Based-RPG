#include "Monster.h"
#include "Unit.h"
#include <string>
#include <iostream>
using std::string;

Monster::Monster(string name_, int health_, int attack_, string dialogue_) : Unit(name_, health_, attack_) {	// constructor

	dialogue = dialogue_;

}

void Monster::update(int type) {	// the overriden update function, updates differently based on which monster is being updated.

	switch (type) {
	case 1:
		attack = (attack + ((monster_level * 3) - 3));//fore the goblin				
		health = (health + ((monster_level * 5) - 5));
		break;
	case 2:
		attack = (attack + ((monster_level * 5) - 5));//for the wolf
		health = (health + ((monster_level * 8) - 8));
		break;
	case 3:
		attack = (attack + ((monster_level * 3) - 3));//for the ogre
		health = (health + ((monster_level * 6) - 6));
		break;
	}
}

void Monster::operator= (Monster &m) { // overloaded operator for monster objects
	name = m.name;
	health = m.health;
	attack = m.attack;
	dialogue = m.dialogue;
}

int Monster::smite() {// a monsters ability to "critical" strike
	return (10 + (monster_level * 3));
}

int Monster::get_attack() {//getter functions
	return attack;
}

int Monster::get_hp() {
	return health;
}

std::string Monster::get_name() {
	return name;
}

std::string Monster::get_dialogue() {
	return dialogue;
}

