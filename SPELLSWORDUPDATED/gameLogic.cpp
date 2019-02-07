#include "gameLogic.h"

//////////////////////////////////////CREATURE CLASS FUNCTIONS///////////////////////////////////////////////
creature::creature() {
	story = 0;
	heroHealth = 100;
	enemyHealth = 20;
	meleeDamage = 4;
	enemyDamage = 4;
	miscastChance = 15;
	mana = 50;
	spells = { "Smite" };
}

creature::~creature() {
}

void creature::addPotion() {
	cout << "You've found a potion." << endl;

	int addItem = rand() % 3;
	switch (addItem) {

	case 0: {
		cout << "It is an Instant Kill potion. Its use is obvious. Use it wisely." << endl << endl;
		string addPotion = "Instant Kill";
		potions.push_back(addPotion);
		break;
	}

	case 1: {
		cout << "It is Heart Potion. It will restore 10 health to you." << endl << endl;
		string addPotion = "Heart";
		potions.push_back(addPotion);
		break;
	}
	case 2: {
		cout << "It is a Mana potion, it will increase your Mana by 25" << endl << endl;
		string addPotion = "Mana";
		potions.push_back(addPotion);
		break;
	}

	default:
		cout << "Adding nothing to your potions" << endl << endl;;
		break;
	}
}

void creature::checkPotions() {

	if (!potions.empty()) {
		cout << "You have the following potions:" << endl;
		for (int i = 0; i < potions.size(); i++) {
			cout << i << ": " << potions.at(i) << endl;
		}
		cout << endl;
	}
	else {
		cout << "You have no potions." << endl << endl;
	}
}

void creature::healthComments() {
	if (heroHealth < 10) {
		cout << "You are mortally wounded." << endl << endl;
	}
	else if (heroHealth < 30) {
		cout << "You are severely wounded." << endl << endl;
	}
	else if (heroHealth < 50) {
		cout << "You are lightly wounded." << endl << endl;
	}
}

void creature::combat() {
	string userInput;

	int inventoryNum;
	int empowerEndTurn = 0;
	int turns = 0;

	int prevHeroHealth;
	int prevEnemyHealth;

	int prevMeleeDamage = meleeDamage;
	int heroDamageRand;
	int enemyDamageRand;

	if (story == 3) {
		cout << "A hulking mountain of a man appears in front of you. \"She sent me to kill you. Sorry it has to be this way.\"" << endl << endl;
		enemyHealth = 40;
		enemyDamage = 7;
	}
	else if (story == 6) {
		cout << "A small impish fiend rises from a circle of flame in the ground. It cackles, and says \"Burn, burn, BUUUUUUURN!\"" << endl << endl;
		enemyHealth = 50;
		enemyDamage = 9;
	}
	else if (story == 9) {
		cout << "A thin woman appears out of the trees. Her hair is stringy and black, her arms covered in scar tissue." << endl;
		cout << "She utters the words \"You killed my husband, and my favorite servant. You will answer for your sins." << endl;
		cout << "Nobody loots and kills in my forest except for me.\"" << endl << endl;
		enemyHealth = 60;
		enemyDamage = 11;
	}
	else {
		cout << "A creature appears before you, willing to fight, yet still trembling." << endl << endl;
		enemyHealth = 20;
		enemyDamage = 4;
	}

	while (enemyHealth > 0 && heroHealth > 0) {
		if (turns == empowerEndTurn) {
			meleeDamage = prevMeleeDamage;
		}

		heroDamageRand = (rand() % 4) + 1;
		enemyDamageRand = (rand() % 2) + 1;

		prevHeroHealth = heroHealth;
		prevEnemyHealth = enemyHealth;

		cout << "Combat Commands" << endl;
		cout << "\"melee\" - Do Melee Attack" << endl;
		cout << "\"inventory\" - Use Inventory Item on Creature" << endl;
		cout << "\"potions\" - Use Potion on Creature" << endl;
		cout << "\"spells\" - Cast a spell" << endl << endl;

		getline(cin, userInput);

		while (userInput != "melee" && userInput != "inventory" && userInput != "potions" && userInput != "spells") {
			std::cout << endl << "Enter a valid command." << endl;
			getline(cin, userInput);
		}

		if (userInput == "melee") {
			enemyHealth -= meleeDamage + heroDamageRand;
			heroHealth -= enemyDamage + enemyDamageRand;

			cout << endl << prevEnemyHealth - enemyHealth << " damage to the creature" << endl;
			cout << prevHeroHealth - heroHealth << " damage to the hero" << endl;
			cout << "Hero has " << heroHealth << " health left" << endl;
			cout << "The creature has " << enemyHealth << " health left" << endl << endl;
		}

		else if (userInput == "inventory") {
			cout << endl;
			checkInventory();
			if (!inventory.empty()) {
				cout << "Which inventory item would you like to use (enter the number)?" << endl;
				cin >> inventoryNum;
				cin.ignore();

				while (inventoryNum > inventory.size() - 1 || inventoryNum < 0) {
					std::cout << endl << "Enter a valid command." << endl;
					cin >> inventoryNum;
					cin.ignore();
				}

				int damage = inventory.at(inventoryNum).strength;
				enemyHealth -= damage;
				heroHealth -= enemyDamage;

				cout << endl << "Using " << inventory.at(inventoryNum).name << endl;
				cout << damage << " damage to the creature" << endl;
				cout << enemyDamage << " damage to the hero" << endl;
				cout << "Hero has " << heroHealth << " health left" << endl;
				cout << "The creature has " << enemyHealth << " health left" << endl << endl;
				inventory.erase(inventory.begin() + inventoryNum);

				if (enemyHealth <= 0 && (story % 3) != 0) {
					cout << "The creature lets out a quit whimper as it draws its final breath." << endl << endl;
				}
			}
		}

		else if (userInput == "potions") {
			cout << endl;
			checkPotions();
			if (!potions.empty()) {
				cout << "Which potion would you like to use (enter the number)?" << endl;
				cin >> inventoryNum;
				cin.ignore();

				while (inventoryNum > potions.size() - 1 || inventoryNum < 0) {
					std::cout << endl << "Enter a valid command." << endl;
					cin >> inventoryNum;
					cin.ignore();
				}

				if (potions.at(inventoryNum) == "Heart") {
					heroHealth += 10;
					cout << "Tastes like sweet wine." << endl;
					cout << "You now have " << heroHealth << " health." << endl << endl;
					potions.erase(potions.begin() + inventoryNum);
				}
				else if (potions.at(inventoryNum) == "Instant Kill") {
					if (story == 3 || story == 6 || story == 9) {
						cout << "Your opponent dodges out of the way of the vial." << endl << endl;
					}
					else {
						enemyHealth = 0;
						cout << "You throw the vial at the creature. Its flesh sizzles as it dissolves in agony... You monster." << endl << endl;
						potions.erase(potions.begin() + inventoryNum);
					}
				}
				else if (potions.at(inventoryNum) == "Mana") {
					if (mana == 50) {
						cout << "You are already at full mana." << endl << endl;
					}
					else if (mana >= 25) {
						mana = 50;
						cout << "A shiver goes down your spine as the bitter liquid goes down your throat." << endl;
						cout << "You now have " << mana << " mana." << endl << endl;
						potions.erase(potions.begin() + inventoryNum);
					}
					else {
						mana += 25;
						cout << "A shiver goes down your spine as the bitter liquid goes down your throat." << endl;
						cout << "You now have " << mana << " mana." << endl << endl;
						potions.erase(potions.begin() + inventoryNum);
					}
				}
			}
		}
		else if (userInput == "spells") {
			cout << endl;
			checkSpells();
			if (!spells.empty()) {
				cout << "Which spell would you like to cast? (enter the number)" << endl;
				cin >> inventoryNum;
				cin.ignore();

				while (inventoryNum > spells.size() - 1 || inventoryNum < 0) {
					std::cout << endl << "Enter a valid command." << endl;
					cin >> inventoryNum;
					cin.ignore();
				}

				if (spells.at(inventoryNum) == "Smite") {
					if (mana < 20) {
						cout << endl << "Not enough mana." << endl << endl;
					}
					else {
						smite();
						cout << endl << "You have " << mana << " mana left." << endl << endl;
					}
				}
				else if (spells.at(inventoryNum) == "Holy Light") {
					if (mana < 30) {
						cout << endl << "Not enough mana." << endl << endl;
					}
					else {
						holyLight();
						cout << endl << "You have " << mana << " mana left." << endl << endl;
					}
				}
				else if (spells.at(inventoryNum) == "Empower") {
					if (mana < 15) {
						cout << endl << "Not enough mana." << endl << endl;
					}
					else {
						empower();
						cout << endl << "You have " << mana << " mana left." << endl << endl;
						empowerEndTurn = turns + 4;
					}
				}
			}
		}

		++turns;

		if (enemyHealth <= 0 && heroHealth > 0) {
			if (story == 3) {
				cout << endl << "He falls to the ground with a hard slam. \"Desdemona... Forgive me... My wife...\"" << endl << endl;
				meleeDamage += 2;
				spells.push_back("Empower");
				cout << endl << "You have learned the Empower spell. It will increase the damage you deal for a short time. Cost: 15 mana" << endl;
				cout << "Be careful with spells. The winds of magic are not always in your favour..." << endl << endl;
			}
			else if (story == 6) {
				cout << endl << "The imp lets of a hellish wail, \"NOOOOO! This is not the end, She will make you pay!\"" << endl;
				cout << "Its skin turns to ash and falls in a small clump on the ground." << endl << endl;
				meleeDamage += 2;
				spells.push_back("Holy Light");
				cout << "You have learned to Holy Light spell. It will heal you for a great amount. Cost: 30 mana" << endl << endl;
			}
			else if (story == 9) {
				cout << "She lets out an agonizing scream before she mutters, \"No... I have stood as terror of this forest for 10,000 years..." << endl;
				cout << "The gods below will make you rue this day. I will make sure of it, when you leave this mortal fold...\"" << endl;
				cout << "Her body falls to the ground with a soft thud. Her decays into a soft sludge, sapping the life from the plants around." << endl << endl;
				endGame = true;
			}
			else {
				cout << "The creature lets out a quiet whimper as it draws its final breath." << endl << endl;
				meleeDamage = prevMeleeDamage;
			}
		}
	}
	story += 1;
}

void creature::checkSpells() {
	if (!spells.empty()) {
		cout << "You have learned the following spells" << endl;
		for (int i = 0; i < spells.size(); i++) {
			cout << i << ": " << spells.at(i) << endl;
		}
		cout << endl;
	}
	else {
		cout << "You have not learned any spells. Maybe you should read more..." << endl << endl;
	}
}

void creature::checkInventory() {

	if (!inventory.empty()) {
		cout << "You have the following items" << endl;
		for (int i = 0; i < inventory.size(); i++) {
			cout << i << ": " << inventory.at(i).name << endl;
		}
		cout << endl;
	}
	else {
		cout << "You have no items." << endl << endl;
	}
}

void creature::addInventory() {

	int addItem = rand() % 5;
	switch (addItem) {

	case 0: {
		cout << "You found a hammer, it will do 14 damage to an enemy." << endl << endl;
		collectibles hammer;
		hammer.name = "Hammer";
		hammer.strength = 14;
		inventory.push_back(hammer);
		break;
	}

	case 1: {
		cout << "You found a sword, it will do 16 damage to an enemy." << endl << endl;
		collectibles sword;
		sword.name = "Sword";
		sword.strength = 16;
		inventory.push_back(sword);
		break;
	}

	case 2: {
		cout << "You found a whip, it will do 12 damage to an enemy." << endl << endl;
		collectibles whip;
		whip.name = "Whip";
		whip.strength = 12;
		inventory.push_back(whip);
		break;
	}

	case 3: {
		cout << "You found a bomb, it will do 20 damage to an enemy." << endl << endl;
		collectibles handBomb;
		handBomb.name = "Hand Bomb";
		handBomb.strength = 20;
		inventory.push_back(handBomb);
		break;
	}

	case 4: {
		cout << "You found a slingshot, it will do 10 damage to an enemy." << endl << endl;
		collectibles slingShot;
		slingShot.name = "Slingshot";
		slingShot.strength = 10;
		inventory.push_back(slingShot);
		break;
	}


	default:
		cout << "Adding nothing to your inventory" << endl << endl;;
		break;
	}
}

void creature::randomPlaceGenerator() {
	int randLocation = rand() % 5;
	int monsterOrItem = rand() % 3;
	string userInput;

	switch (randLocation) {

	case 0:
		cout << "You have come across a mysterious hut, would you like to check inside? \"yes\" or \"no\"" << endl;
		getline(cin, userInput);

		while (userInput != "yes" && userInput != "no") {
			std::cout << endl << "Enter a valid command.." << endl;
			getline(cin, userInput);
		}

		if (userInput == "yes") {
			cout << endl << "You think you hear a giggle behind you. A glance over your shoulder reveals it was nothing. You hope." << endl << endl;
			if (monsterOrItem == 0) {
				addInventory();
			}
			else if (monsterOrItem == 1) {
				combat();
			}
			else if (monsterOrItem == 2) {
				addPotion();
			}
		}
		break;

	case 1:
		cout << "You have come across an abandoned campsite, would you like to scavenge it? \"yes\" or \"no\"" << endl;
		getline(cin, userInput);

		while (userInput != "yes" && userInput != "no") {
			std::cout << endl << "Enter a valid command.." << endl;
			getline(cin, userInput);
		}

		if (userInput == "yes") {
			cout << endl << "The coals of the fire are still hot. Someone was here recently." << endl << endl;
			if (monsterOrItem == 0) {
				addInventory();
			}
			else if (monsterOrItem == 1) {
				combat();
			}
			else if (monsterOrItem == 2) {
				addPotion();
			}
		}
		break;

	case 2:
		cout << "You have come across a dark cave, would you like to check inside? \"yes\" or \"no\"" << endl;
		getline(cin, userInput);

		while (userInput != "yes" && userInput != "no") {
			std::cout << endl << "Enter a valid command.." << endl;
			getline(cin, userInput);
		}

		if (userInput == "yes") {
			cout << endl << "The sound of wet water dripping echoes within the dark serpentines of the cave." << endl << endl;
			if (monsterOrItem == 0) {
				addInventory();
			}
			else if (monsterOrItem == 1) {
				combat();
			}
			else if (monsterOrItem == 2) {
				addPotion();
			}
		}
		break;

	case 3:
		cout << "You have come across an old house, would you like to check inside? \"yes\" or \"no\"" << endl;
		getline(cin, userInput);

		while (userInput != "yes" && userInput != "no") {
			std::cout << endl << "Enter a valid command.." << endl;
			getline(cin, userInput);
		}

		if (userInput == "yes") {
			cout << endl << "The door creaks as you enter." << endl << endl;
			if (monsterOrItem == 0) {
				addInventory();
			}
			else if (monsterOrItem == 1) {
				combat();
			}
			else if (monsterOrItem == 2) {
				addPotion();
			}
		}
		break;

	case 4:
		cout << "You've stumbled across a mysterius waterfall, would you like to check behind it? \"yes\" or \"no\"" << endl;
		getline(cin, userInput);

		while (userInput != "yes" && userInput != "no") {
			std::cout << endl << "Enter a valid command." << endl;
			getline(cin, userInput);
		}

		if (userInput == "yes") {
			cout << endl << "Your gear is soaked as you walk into a hidden cave behind the falls." << endl << endl;
			if (monsterOrItem == 0) {
				addInventory();
			}
			else if (monsterOrItem == 1) {
				combat();
			}
			else if (monsterOrItem == 2) {
				addPotion();
			}
		}
		break;

	default:
		cout << "This is not a valid location" << endl;
		break;
	}
}

void creature::smite() {
	int prevHealth = enemyHealth;

	int castRoll = (rand() % 101) + 5;
	int miscastRoll = (rand() % 101) + 6;

	if (miscastRoll < miscastChance) {
		cout << "The winds of magic deny you. Spell miscast." << endl;
		heroHealth -= (3 + ((rand() % 7) + 1));
	}
	else if (castRoll > 100) {
		cout << "The winds of magic are generous. Critical cast." << endl;
		enemyHealth -= (16 + ((rand() % 20) + 1));
	}
	else {
		cout << "Successful cast." << endl;
		enemyHealth -= (12 + ((rand() % 8) + 1));
	}

	mana -= 20;
	int presHealth = enemyHealth;
	heroHealth -= enemyDamage;

	cout << endl << prevHealth - presHealth << " damage to the creature" << endl;
	cout << enemyDamage << " damage to the hero" << endl;
	cout << "You have " << heroHealth << " health left" << endl;
	cout << "The creature has " << enemyHealth << " health left" << endl;

	if (enemyHealth <= 0) {
		cout << "You opponent's flesh is seared to the bone with divine energy. It screams in pain, and lets out a death rattle." << endl << endl;
	}

}

void creature::holyLight() {
	int castRoll = (rand() % 101) + 6;
	int miscastRoll = (rand() % 101) + 6;

	if (miscastRoll < miscastChance) {
		cout << "The winds of magic deny you. Spell miscast.\n";
		heroHealth -= (3 + ((rand() % 7) + 1));
	}
	else if (castRoll > 100) {
		cout << "The winds of magic are generous. Critical cast.\n";
		cout << "Your plea to the gods of the land is heard. You feel your wounds closing up." << endl;
		heroHealth += 30 + ((rand() % 41) + 1);
		cout << "Your health has been increased to " << heroHealth << endl;
	}
	else {
		cout << "Successful cast." << endl;
		cout << "Your plea to the gods of the land is heard. You feel your wounds closing up." << endl;
		heroHealth += (20 + ((rand() % 31) + 1));
		cout << "Your health has been increased to " << heroHealth << endl;
	}

	mana -= 30;
}

void creature::empower() {
	int castRoll = (rand() % 101) + 6;
	int miscastRoll = (rand() % 101) + 6;

	if (miscastRoll < miscastChance) {
		cout << "The winds of magic deny you. Spell miscast." << endl;
		meleeDamage = 2;
	}
	else if (castRoll > 100) {
		cout << "The winds of magic are generous. Critical cast." << endl;
		cout << "You invoke your inner power, channeling energy throughout your body." << endl << endl;
		meleeDamage += 6;
	}
	else {
		cout << "Successful cast." << endl;
		cout << "You invoke your inner power, channeling energy throughout your body." << endl << endl;
		meleeDamage += 4;
	}
	mana -= 15;
}
