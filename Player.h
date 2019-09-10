#ifndef PLAYER_H
#define PLAYER_H
#include "Unit.h"
#include <string>


class Player : public Unit { //Class declaration, inherits the Unit class

private:	//private data memebers specific to Player
	int exp;
	int level;
	int won;
	int lost;

public:
	Player(std::string name_, int health_, int attack_, int exp_, int level_, int won_, int lost_);//constructor 
	void update();	//functions that overrides the virtual update function from unit
	friend void current_exp(Player &p, int type);	//friend function 
	void operator= (Player &p);	//overloaded operator 
	int fire_spell();	
	int cure_spell();
	void scoreboard();
	int get_hp();	//getters and setters
	int get_attack();
	void set_won(int won_);
	void set_lost(int lost_);

};

#endif
