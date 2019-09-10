#include <iostream>
#include "Player.h"
#include "Monster.h"
#include "UnitIO.h"
#include <ctime>
#include <stdlib.h>

using namespace std;

int won = 0;// global variables that will be used througout 
int lost = 0;
int movement_result;
int decision;
int menu_decision;
int current_y = 9;
int current_x = 1;
int monster1 = 1;
int monster2 = 2;
int monster3 = 3;
int Monster::monster_level = 1;

int combat(Player &p, Monster &m, int boss_flag);

char map[11][11] = { {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'}, // This 2-D array represents the map for the game!
						{'|', 'O', '|', 'O', '|', 'O', '|', '|', '|', 'W', '|'},
						{'|', 'O', 'O', 'O', 'O', 'O', '|', '|', 'O', 'O', '|'},
						{'|', 'O', '-', '-', '-', 'O', '|', '|', 'O', '-', '|'},
						{'|', 'O', 'O', 'O', '|', 'O', '-', '-', 'O', 'O', '|'},
						{'|', '|', '|', 'O', '|', 'O', 'O', 'O', 'O', 'O', '|'},
						{'|', '-', '-', 'O', '|', 'O', 'O', 'O', '-', 'O', '|'},
						{'|', 'O', 'O', 'O', '|', '|', '-', '-', '|', 'O', '|'},
						{'|', 'O', '-', '-', '|', '|', 'O', 'O', 'O', 'O', '|'},
						{'|', 'O', '|', '|', '|', '|', 'O', '|', 'O', '|', '|'},
						{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'} };

void current_exp(Player &p, int type) { // the current_exp function is a friend function for the Player class
										// this function gives exp to the player and checks for a level up
	switch (type) {
	case 1:
		p.exp = p.exp + 3; // goblins give 3 experience
		break;
	case 2:
		p.exp = p.exp + 5;	//wolves give 5 experience
		break;
	case 3:
		p.exp = p.exp + 10;	//Ogres give 10 exp
		break;
	};
	
	switch (p.level) {//max level is 5

	case 1:	
		if ((6 - p.exp) <= 0) {// each case represents each possible level the player could be, and then we check if 
			cout << "********************\n";	//they have enough for the next level
			cout << "You are now Level 2!|\n";
			cout << "********************\n";
			p.level++; // player level goes up
			Monster::monster_level++;	// increment the static monster level data member, the update functions for the monsters get triggered in main
			p.update();// player's update function gets triggered here
		}
		else {// if the player does not have enough to level up, the game displays the current exp of the player
			cout << "***********************************\n";	//as well as how much is needed for the next level
			cout << " Current EXP: " << p.exp << "\t     \n";
			cout << " Next Level : " << 6 - p.exp << "\t     \n";
			cout << "***********************************\n";
		}
		break;
	case 2:	//case 2, 3, and 4 are the same as 1, just different experience requirements 

		if ((17 - p.exp) <= 0) {
			cout << "********************\n";
			cout << "You are now Level 3!|\n";
			cout << "********************\n";
			p.level++;
			Monster::monster_level++;
			p.update();
		}
		else {
			cout << "***********************************\n";
			cout << " Current EXP: " << p.exp << "       \n";
			cout << " Next Level : " << 17 - p.exp << "  \n";
			cout << "***********************************\n";
		}
		break;
	case 3:

		if ((41 - p.exp) <= 0) {
			cout << "********************\n";
			cout << "You are now Level 4!|\n";
			cout << "********************\n";
			p.level++;
			Monster::monster_level++;
			p.update();
		}
		else {
			cout << "***********************************\n";
			cout << " Current EXP: " << p.exp << "       \n";
			cout << " Next Level : " << 41 - p.exp << "  \n";
			cout << "***********************************\n";
		}
		break;
	case 4:
		if ((100 - p.exp) <= 0) {
			cout << "********************\n";
			cout << "You are now Level 5!|\n";
			cout << "********************\n";
			p.level++;
			Monster::monster_level++;
			p.update();
		}
		else {
			cout << "***********************************\n";
			cout << " Current EXP: " << p.exp << "       \n";
			cout << " Next Level : " << 100 - p.exp << " \n";
			cout << "***********************************\n";
		}
		break;		
	default: // Player is level 5, max, therefore no longer gains experience points.
		cout << "*******************\n";
		cout << " Current EXP: MAX |\n";
		cout << "*******************\n";
		break;
	};

}

int movement(int direction, Player &p, Monster &m) {	//movement function handles all movement throughout the map
	int win_game;
	switch (direction) {

	case 1:	// move up, checks if the "new" tile is equal to W as that will trigger the boss
		map[current_y][current_x] = 'O';	
		current_y--;
		if (map[current_y][current_x] == 'W') {//We only check this in the "up" case, as that is the only way to reach the boss tile ;)
			system("cls");
			cout << "\n\nYou walk into the Ogre King's Lair, he does NOT look very happy...\n\n";
			win_game = combat(p, m, 1); // triggers combat function with an Ogre (the boss), passing in the flag variable 1
			if (win_game == 1) {//the combat function will return a 1 if the player killed the boss, boom, game beat!!!
				cout << "You have beaten the game, congrats!\n\n";
				system("pause");			
			}
			else {
				system("cls");
				cout << "You have been crushed by the boss, you will be revived, but do not return until you can actually kill the boss.\n";
				current_y++; // If the player dies then the game puts them at the tile right before the boss
				map[current_y][current_x] = 'X';
				return 2;
			}
		}
		if (map[current_y][current_x] == '_' || map[current_y][current_x] == '-' || map[current_y][current_x] == '|')
		{	// checks if the "new" tile to see if it's a wall piece, if it's a wall then it says nope. 
			system("cls");
			cout << "***********************************\n";
			cout << "You cannot go up, there is a wall.|\n";
			cout << "***********************************\n";
			current_y++;
			map[current_y][current_x] = 'X';
			return 0;
		}
		
		map[current_y][current_x] = 'X'; // succesful move
		return 1;

	case 2:	//case 2, 3, and 4 are the same as case 1, just minus the boss nonsense
		map[current_y][current_x] = 'O';
		current_y++;
		if (map[current_y][current_x] == '_' || map[current_y][current_x] == '-' || map[current_y][current_x] == '|')
		{
			system("cls");
			cout << "*************************************\n";
			cout << "You cannot go down, there is a wall.|\n";
			cout << "*************************************\n";
			current_y--;
			map[current_y][current_x] = 'X';
			return 0;
		}
		map[current_y][current_x] = 'X';
		return 1;

	case 3:
		map[current_y][current_x] = 'O';
		current_x++;
		if (map[current_y][current_x] == '_' || map[current_y][current_x] == '-' || map[current_y][current_x] == '|')
		{
			system("cls");
			cout << "**************************************\n";
			cout << "You cannot go right, there is a wall.|\n";
			cout << "**************************************\n";
			current_x--;
			map[current_y][current_x] = 'X';
			return 0;
		}
		map[current_y][current_x] = 'X';
		return 1;

	case 4:
		map[current_y][current_x] = 'O';
		current_x--;
		if (map[current_y][current_x] == '_' || map[current_y][current_x] == '-' || map[current_y][current_x] == '|')
		{
			system("cls");
			cout << "*************************************\n";
			cout << "You cannot go left, there is a wall.|\n";
			cout << "*************************************\n";
			current_x++;
			map[current_y][current_x] = 'X';
			return 0;
		}
		map[current_y][current_x] = 'X';
		return 1;
	default:
		return 0;
	}
}

int main_menu(Player &player, Monster &ogre) {// the main menu function that is used for every iteration of the "main loop" of the game

	
		cout << "______________________________\n";
		cout << "What do you want to do?" << endl << endl;	//display menu for players
		cout << " Move Forward\t ---------- 1\n" << " Move Backwards\t ---------- 2\n" << " Move Right\t ---------- 3\n"
			<< " Move Left\t ---------- 4\n" << " Scoreboard\t ---------- 5\n" << " Exit Game\t ---------- 0\n";
		cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";

		while(true) {	//input validation loop
			cin >> menu_decision;				
	if ((menu_decision != 0 && menu_decision != 1 && menu_decision != 2 && menu_decision != 3 && menu_decision != 4 && menu_decision != 5) || cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid, please re-enter: ";
				continue;
			}
			else
				break;
		};

		switch (menu_decision)
		{
		case 1:	// move up
			movement_result = movement(1, player, ogre);	//the movement function is triggered for any movement actions
			if (movement_result == 0 || movement_result == 2) {
				return 1;
			}
			else
				return 3;
		case 2: //move down
			movement_result = movement(2, player, ogre);
			if (movement_result == 0)
				return 1;
			else
				return 3;
		case 3:	//move right
			movement_result = movement(3, player, ogre);
			if (movement_result == 0)
				return 1;
			else
				return 3;
		case 4:	//move left
			movement_result = movement(4, player, ogre);
			if (movement_result == 0)
				return 1;
			else
				return 3;
		case 5:
			return 4; // returns 4 which will trigger the scoreboard member function
		case 0:
			return 0;	// exits the game
		default:
			return 1;
		}
}

void victory(Player &player, string m_name) { // victory function when a player kills an enemy 
	int type = 0;
	if (m_name == "Goblin") // assigns an int that represents which monster of the three types was killed
		type = 1;
	if (m_name == "Wolf")
		type = 2;
	if (m_name == "Ogre")
		type = 3;
	
	player.set_won(++won);	//increments the Won member with our setter function
	cout << "You killed the " << m_name << "!\n\n";
	current_exp(player, type);// triggers the current exp function, passing the int type into the function
}								//as it will determine how much exp is rewarded to the player for the kill

void defeat(Player &player) { // Displays that the player lost the fight and increments our Lost member with a setter function
	player.set_lost(++lost);
	cout << "you lose!\n\n";
}

int combat(Player &p, Monster &m, int boss_flag) { // The combat function, the boss_flag variables let's us know that the player is fighting the boss
													// which will change the return value to have the player win the game if that is the case
	
	int heal;
	int critical_heal;
	int fire;
	int critical_fire;
	int enemy_current_hp;
	int player_current_hp;
	int enemy_current_attack;	//creation of variables needed for the combat function
	int player_current_attack;
	string m_name = m.get_name();
	string m_dialogue = m.get_dialogue();//using our getter functions to fill certain variables
	double player_rng;
	double monster_rng;
	int smite_damage;
	int dual_strike;
	enemy_current_hp = m.get_hp();
	player_current_hp = p.get_hp();
	

	do {
		cout << "______________________________\n";
		cout << "What would you like to do?\n\n";	//the display menu for the player in combat
		cout << "Attack\t ---------- 1\n" << "Spells   ---------- 2\nRun Away ---------- 3\n";
		cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";

		while (true) {	//input validation loop
			cin >> decision;
			if ((decision != 0 && decision != 1 && decision != 2 && decision != 3) || cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid, please re-enter: ";
				continue;
			}
			else
				break;
		};

		player_rng = ((rand() % 40) + 60) / 100.0;	//generates random numbers that will determine how hard units hit/heal for.
		monster_rng = ((rand() % 40) + 60) / 100.0;
	
		player_current_attack = (int)(p.get_attack() * player_rng);
		enemy_current_attack = (int)(m.get_attack() * monster_rng);
		smite_damage = (int)(m.smite() * monster_rng);
		dual_strike = (int)((player_current_attack) * player_rng * 1.50);

		heal = (int)(p.cure_spell() * player_rng);
		critical_heal = (int)(heal * 1.50);			//Calculates how much a normal heal and a critical heal is worth

		fire = (int)(p.fire_spell() * player_rng);	//Same thing but with fire
		critical_fire = (int)(fire + 1.50);
		

		if (decision == 1)	//decision 1 is to attack
		{			
			system("cls");
			
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|";
			
			if (player_rng > 0.9) {	//if the random number generated is in the 90-100% range, the attack/heal is critical
				enemy_current_hp = enemy_current_hp - dual_strike; //chance to dualstrike!!
				cout << "\nYou Dual Strike the enemy for:\t" << dual_strike << " damage!\t |\n";
			}   
			else {
				enemy_current_hp = enemy_current_hp - (player_current_attack);
				cout << "\nYou slash the enemy for:\t" << player_current_attack << " damage!\t |\n";
			}

			if (monster_rng > 0.9) {
				player_current_hp = player_current_hp - m.smite(); //chance to smite (basically a critical hit)!
				cout << "The enemy Smites you for:\t" << smite_damage << " damage!\t |\n";
			}
			else {
				player_current_hp = player_current_hp - enemy_current_attack;
				cout << m_dialogue << "\t" << enemy_current_attack << " damage!\t |\n";
			}
			cout << "                                                 |\n";

			if (enemy_current_hp < 0)
				enemy_current_hp = 0;	//These lines make sure we dont have negative health values display to the console

			if (player_current_hp < 0)
				player_current_hp = 0;

			if (player_current_hp == 0 && enemy_current_hp == 0) {
				player_current_hp = 1;	//Can't have both hp values end a turn at 0, and the Player gets first-strike!
			}

				if(player_current_hp >= 10)
				cout << "You have: \t " << player_current_hp << " hitpoints remaining!\t |\n";// Displays current health for the units after each turn
				else cout << "You have: \t " << player_current_hp << " hitpoints remaining!\t \t |\n";
				if(enemy_current_hp >= 10)
					cout << "The enemy has:\t " << enemy_current_hp << " hitpoints remaining!\t |\n";
				else	cout << "The enemy has:\t " << enemy_current_hp << " hitpoints remaining!\t \t |\n";
			cout << "                                                 |\n";
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";

			if (enemy_current_hp == 0) {
				if (boss_flag == 1)	//checks if we killed the boss
					return 1;
				victory(p, m_name);// If we kill a random enemy, the victory function is triggered to distrubute gained experience points
				return 0;
			}

			else if (player_current_hp == 0) {
				defeat(p);	// triggers the defeat function if the player dies
				return 0;
			}
			

		}
		if (decision == 2)// decision 2 is to utilize a spell
		{
			cout << "**************************************\n";	//spell menu
			cout << "              Spells\n\n\n";
			cout << " Fire ------ 1\n";
			cout << " Cure ------ 2\n\n";
			cout << "**************************************\n";

			while (true) {	//input validation loop
				cin >> decision;
				if ((decision != 0 && decision != 1 && decision != 2) || cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid, please re-enter: ";
					continue;
				}
				else
					break;
			};

			switch (decision) {
			case 1: //case 1 is fire!
				system("cls");
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|";
				if (player_rng > 0.9) {	
					enemy_current_hp = enemy_current_hp - critical_fire; //chance to crit!!
					cout << "\nYou Fire Blast the enemy for:\t" << critical_fire << " damage!\t |\n";
				}
				else {
					enemy_current_hp = enemy_current_hp - fire;	// the default regular hit
					cout << "\nYou Burn the enemy for:\t\t" << fire << " damage!\t |\n";
				}

				if (monster_rng > 0.9) {
					player_current_hp = player_current_hp - m.smite(); //chance to smite (basically a critical hit)!
					cout << "The enemy Smites you for:\t" << smite_damage << " damage!\t |\n";
				}
				else {
					player_current_hp = player_current_hp - enemy_current_attack;
					cout << m_dialogue << "\t" << enemy_current_attack << " damage!\t |\n";
				}

				if (enemy_current_hp < 0)
					enemy_current_hp = 0;	// no negative health values 

				if (player_current_hp < 0)
					player_current_hp = 0;


				if (player_current_hp == 0 && enemy_current_hp == 0) {
					player_current_hp = 1;	//Can't have both hp values end a turn at 0, and the Player gets first-strike!
				}

				if (player_current_hp >= 10) // Have to use these if statements to make sure the display is always lined up correctly
					cout << "You have: \t " << player_current_hp << " hitpoints remaining!\t |\n";
				else cout << "You have: \t " << player_current_hp << " hitpoints remaining!\t \t |\n";
				if (enemy_current_hp >= 10)
					cout << "The enemy has:\t " << enemy_current_hp << " hitpoints remaining!\t |\n";
				else	cout << "The enemy has:\t " << enemy_current_hp << " hitpoints remaining!\t \t |\n";
				cout << "                                                 |\n";
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";

				if (enemy_current_hp == 0) {
					if (boss_flag == 1)
						return 1;
					victory(p, m_name);
					return 0;
				}

				else if (player_current_hp == 0) {
					defeat(p);
					return 0;
				}

				break;
			case 2: // case 2 is the heal spell 
				system("cls");

				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|";

				if (player_rng > 0.9) {
					player_current_hp = player_current_hp + critical_heal; //chance to double heal!!
					cout << "\nYou Double Heal yourself for:\t" << critical_heal << " health!\t |\n";
				}
				else {
					player_current_hp = player_current_hp + heal; //Normal Heal
					cout << "\nYou heal yourself for:\t\t" << heal << " health!\t |\n";
				}

				if (player_current_hp > p.get_hp()) {
					player_current_hp = p.get_hp();
				}

				if (monster_rng > 0.9) {
					player_current_hp = player_current_hp - m.smite(); //chance to smite (basically a critical hit)!
					cout << "The enemy Smites you for:\t" << smite_damage << " damage!\t |\n";
				}
				else {
					player_current_hp = player_current_hp - enemy_current_attack; //monster normal attack
					cout << m_dialogue << "\t" << enemy_current_attack << " damage!\t |\n";
				}

				if (player_current_hp < 0)
					player_current_hp = 0;			

				if (player_current_hp >= 10)
					cout << "You have: \t " << player_current_hp << " hitpoints remaining!\t |\n";
				else cout << "You have: \t " << player_current_hp << " hitpoints remaining!\t \t |\n";
				if (enemy_current_hp >= 10)
					cout << "The enemy has:\t " << enemy_current_hp << " hitpoints remaining!\t |\n";
				else	cout << "The enemy has:\t " << enemy_current_hp << " hitpoints remaining!\t \t |\n";
				cout << "                                                 |\n";
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";

				if (enemy_current_hp == 0) {
					if (boss_flag == 1)
						return 1;
					victory(p, m_name);
					return 0;
				}

				else if (player_current_hp == 0){
					defeat(p);
						return 0;
				}

				break;
			}
									
		}
		
	if (decision == 3) { // decision 3 is to run away from the enemy
		system("cls");
		if (boss_flag == 1) {	//the player can run from any enemy 100% of the time except for the boss
			cout << "You can't run from a Boss!!! Hahahahaha!!!\n";
			continue;
		}
		else {
			cout << "\nYou escape!\n\n";
			return 0;
		}
	}
			
	} while (enemy_current_hp > 0 && player_current_hp > 0);// This combat loop continues until one of the units are dead 
	return 0;												// 1 iteration of this loop is essentially one "turn"
}

void battle_switch(Player &player, Monster &goblin, Monster &ogre, Monster &wolf) {	//This function generates a random number and then either triggers 
																					//the combat function with the specific monster, or there is 
	int fight = rand() % 100;														// no combat and text is printed out

	if (fight >= 95) {	//5% chance to encounter an Ogre, equivelent to the final boss
		system("cls");
		cout << "______________________________\n";
		cout << "A Ogre leaps infront of you!\n";
		cout << "******************************\n";
		combat(player, ogre, 0);
	}

	else if (fight >= 75 && fight < 95) {	//20% chance to encounter a wolf
		system("cls");
		cout << "______________________________________\n";
		cout << "You hear a Wolf snarl from behind you!\n";
		cout << "**************************************\n";
		combat(player, wolf, 0);
	}

	else if (fight >= 50 && fight <= 75) {	//25% chance to encounter a goblin
		system("cls");
		cout << "_________________________________________\n";
		cout << "A short but fierce Goblin runs up to you!\n";
		cout << "*****************************************\n";
		combat(player, goblin, 0);
	}

	else if (fight >= 30 && fight < 50) {	//other possibilites just print out corresponding text
		system("cls");
		cout << "************************************************************|\n";
		cout << "You proceed through this desolate world, the coast is clear.|\n";
		cout << "************************************************************|\n";

	}

	else if (fight >= 15 && fight < 30) {
		system("cls");
		cout << "**********************************************************************|\n";
		cout << "You haven't seen any signs of life other than creatures roaming about.|\n";
		cout << "**********************************************************************|\n";
		
	}

	else if (fight >= 0 && fight <= 15) {
		system("cls");
		cout << "***************************************************************|\n";
		cout << "The land is quiet, you question why you're here...You press on.|\n";
		cout << "***************************************************************|\n";
		
	}
}

void print_map() { // Prints out the map array

	for (int i = 0; i < 11; i++) {
		cout << "\n";
		cout << "    ";
		for (int j = 0; j < 11; j++) {
			cout << map[i][j];
			if (i == 0)
				cout << "_";
			else if (i == 10)
				cout << "-";
			else
				cout << " ";
		}
	}
	cout << "\n";
}

int main() {

	cout << "\t\t\t       _        ______            _     _           _  " <<
		    "\n\t\t\t      /_\\      / __   \\ __      _(_)___| |_ ___  __| |" <<
		    "\n\t\t\t     //_\\\\         / /\\/\\ \\ /\\ / / / __| __/ _ \\/ _` |" <<
		    "\n\t\t\t    /  _  \\       / /    \\ V  V /| \\__ \\ || __ / (_| |" <<
		    "\n\t\t\t    \\_/ \\_/       \\/      \\_/\\_/ |_|___/\\__\\___|\\__,_|" <<

		    "\n\n\t\t\t\t       __    __           _     _" <<
		    "\n\t\t\t\t      / / /\\ \\ \\___  _ __| | __| |" <<
		    "\n\t\t\t\t      \\ \\/  \\/ / _ \\| '__| |/ _` |     " <<
	    	"\n\t\t\t\t       \\  /\\  / (_) | |  | | (_| |" <<
		    "\n\t\t\t\t        \\/  \\/ \\___/|_|  |_|\\__,_|\n";

	cout << "\n\n\t\tBattle your way to the Ogre King before he..uhhh...Destroys the World!!!\n\n";
				
	system("pause");
	system("cls");
	int result;

	Player player(" ", 0, 0, 0, 0, 0, 0); // declares and initializes the Player object with empty values
	Player *p1 = UnitIO::read_player(); // Player object is created and initialized with information from a textfile, and a pointer to that object is returned here
	player = *p1; // we dereference the returned pointer and set it equal to our empty player object, utilizing our overloaded '=' operator!
	delete p1;

	Monster goblin(" ", 0, 0, " ");	// The Monster objects are created the exact same way as the Player objects 
	Monster *m1 = UnitIO::read_monster(monster1);
	goblin = *m1;
	delete m1;

	Monster wolf(" ", 0, 0, " ");
	Monster *m2 = UnitIO::read_monster(monster2);
	wolf = *m2;
	delete m2;

	Monster ogre(" ", 0, 0, " ");
	Monster *m3 = UnitIO::read_monster(monster3);
	ogre = *m3;
	delete m3;

	
	cout << "\nYou wake up, the world is blurry, you take up your sword and stand.\n" << endl;
	map[current_y][current_x] = 'X';

	do {
		
		print_map();
		result = main_menu(player, ogre); //main menu function starts at line 216, the return value is stored into result 
		switch (result) {
		case 1:
			continue;
		case 3:
			battle_switch(player, goblin, ogre, wolf);
			continue;
		case 4:
			player.scoreboard();
		default:
			break;
		}
		
		goblin.update(1);//triggers update function every turn in case there is a level up
		wolf.update(2);
		ogre.update(3);
		
	}
	while (result != 0);// loop continues until result is 0


	system("pause");
	return 0;
}