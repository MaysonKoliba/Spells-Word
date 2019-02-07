#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

#ifndef gameLogic_H
#define gameLogic_H

////////////////////////////////////////INVENTORY STRUCT///////////////////////////////////////////////////
struct collectibles {
	string name;
	int strength;
};

////////////////////////////////////////CREATURE CLASS/////////////////////////////////////////////////////
class creature {
private:

	int story;
	int heroHealth;
	int enemyHealth;
	int meleeDamage;
	int enemyDamage;
	int miscastChance;
	int mana;

	vector <collectibles> inventory;
	vector <string> potions;
	vector <string> spells;

public:
	creature();
	~creature();

	int getHealth() { return heroHealth; }
	int getMana() { return mana; }
	void healthComments();
	void combat();
	void addPotion();
	void checkPotions();
	void checkSpells();
	void addInventory();
	void checkInventory();
	void randomPlaceGenerator();
	void holyLight();
	void smite();
	void empower();
	bool endGame = false;
};

#endif
