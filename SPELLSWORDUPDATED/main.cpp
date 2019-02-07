#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <cctype>
#include "gameLogic.h"

using namespace std;

int main() {
	srand(time(0));
	creature hero;
	string userInput;

	cout << "You are a novice spellsword for the Kingdom of Vaal." << endl;
	cout << "You have been sent by the Order of the Magi to cleanse the Forest of Nightmares of a witch known as Desdemona." << endl << endl;

	while (hero.getHealth() > 0 && hero.endGame == false) {
		int itemPlaceMonster = (rand() % 101) + 1;

		std::cout << "Commands" << endl;
		std::cout << "\"explore\" - Continue Exploring" << endl;
		std::cout << "\"inventory\" - Check Inventory" << endl;
		std::cout << "\"health\" - Check Health" << endl;
		std::cout << "\"potions\" - Check Potions" << endl;
		std::cout << "\"spells\" - Check Spells" << endl << endl;

		getline(cin, userInput);

		while (userInput != "explore" && userInput != "inventory" && userInput != "health" && userInput != "potions" && userInput != "spells") {
			std::cout << endl << "Enter a valid command." << endl;
			getline(cin, userInput);
		}

		if (userInput == "explore") {
			if (itemPlaceMonster > 55) {
				hero.combat();
			}
			else if (itemPlaceMonster > 45) {
				hero.addInventory();
			}
			else if (itemPlaceMonster > 15) {
				hero.randomPlaceGenerator();
			}
			else {
				hero.addPotion();
			}

			if (hero.getHealth() < 50) {
				hero.healthComments();
			}
		}
		else if (userInput == "inventory") {
			hero.checkInventory();
		}
		else if (userInput == "health") {
			std::cout << "Your current health is " << hero.getHealth() << endl;
			std::cout << "Your current mana is " << hero.getMana() << endl << endl;
		}
		else if (userInput == "potions") {
			hero.checkPotions();
		}
		else if (userInput == "spells") {
			hero.checkSpells();
		}
	}
	if (hero.getHealth() <= 0) {
		std::cout << "As you collapse to the ground in death, your mind is flooded with memories of home, your late mother, and your family." << endl;
		std::cout << "You have come to a perilous end, adventurer..." << endl;
	}
	else {
		std::cout << "Your quest is finished. You may now return home to the Vaal homeland. Congratulations, novice." << endl;
	}

	return 0;
}

