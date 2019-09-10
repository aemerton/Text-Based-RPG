#include "Player.h"
#include "Unit.h"
#include <string>
#include <iostream>
using std::string;

Player::Player(string name_, int health_, int attack_, int exp_, int level_, int won_, int lost_) : Unit(name_, health_, attack_) {

	exp = exp_;										//constructor
	level = level_;
	won = won_;
	lost = lost_;

}

void Player::update() {//updates health and attack when player levels up

	attack = 8 + ((level * 5) - 5);
	health = 30 + ((level * 8) - 8);

}

void Player::operator= ( Player &p) {// overloaded operator
	name = p.name;
	health = p.health;
	attack = p.attack;
	exp = p.exp;
	level = p.level;
	won = p.won;
	lost = p.lost;
}

int Player::fire_spell() {		//spell functions, returns magnitude of damage or heal
	return 9 + ((level * 5) - 5);
}

int Player::cure_spell() {
	return (10 + ((level * 4) - 4));
}

void Player::scoreboard() {	//displays score board
	std::system("cls");
	std::cout << name << std::endl << std::endl;
	std::cout << "Battles Won: " << won << std::endl;
	std::cout << "Battles Lost: " << lost << std::endl;
}

int Player::get_attack() {//getter functions
	return attack;
}

int Player::get_hp() {
	return health;
}


void Player::set_won(int won_) {//setter functions
	won = won_;
}

void Player::set_lost(int lost_) {
	lost = lost_;
}
	