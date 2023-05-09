#include "game.h"

// #include "weapon.h"
// #include "gear.h"
using namespace menu;

Game::Game()
{
	choice = 0;
	playing = true;
	loadedPlayer = 0;
	fileName = "player.txt";
}

Game::~Game()
{
}
void Game::startGame()
{

	ifstream in;
	ofstream out;
	in.open("player.txt");

	Weapon::initializeNames();
	Gear::initializeNames();


	// check if a player.txt file is empty and if it is create a new character

	//Guards against an empty file
	if (in.peek() == std::ifstream::traits_type::eof())
	{
		createCharacter();
		this->save();
	} 
	//If a file does exist, load the character
	else if (in.is_open())
	{
		this->load();
	} 
	//If no file exists, create a new character
	else
	{
		createCharacter();
		this->save();
	}

	// else
	// {
	// 	createCharacter();
	// 	this->save();
	// }

	// if it is not empty, load the character

	in.close();
}

void Game::mainMenu()
{
	cout << "Enter to continue..."
		 << "\n";
	cin.get();
	clearTerminal();

	if (this->player[loadedPlayer].isAlive())
	{
		if (this->player[loadedPlayer].getExperience() >=
			this->player[loadedPlayer].getExperienceNext())
		{
			cout << "Level Up Available \n\n";
		}

		cout << "*** Menu ***"
			 << "\n"
			 << "\n";

		cout << "*** Active player: " << this->player[loadedPlayer].getName() << " " << this->loadedPlayer + 1 << "/" << this->player.size() << " ***"
			 << "\n"
			 << "\n";

		cout << "1: Wander"
			 << "\n";
		cout << "2: Level up"
			 << "\n";
		cout << "3: Sleep"
			 << "\n";
		cout << "4: Player info"
			 << "\n";
		cout << "5: Create new player"
			 << "\n";
		cout << "6: Select player"
			 << "\n";
		cout << "7: Save"
			 << "\n";
		cout << "8: Load"
			 << "\n";
		cout << "0: Exit"
			 << "\n";

		cout << "\n";

		cout << "\n"
			 << "Choice: ";
		cin >> this->choice;

		while (cin.fail() || this->choice > 9)
		{
			cout << "Try again."
				 << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "\n"
				 << "Choice (0 - 8): ";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		switch (this->choice)
		{
		case 0:
			playing = false;
			this->save();

			break;

		case 1:
			travel();

			break;

		case 2:
			this->levelUpCharacter();

			break;

		case 3:
			rest();

			break;

		case 4:
			this->characterMenu();
			break;

		case 5:
			createCharacter();
			save();
			break;

		case 6:
			select();
			break;

		case 7:
			save();
			break;

		case 8:
			load();
			break;

		default:
			break;
		}
	}
	else
	{
		cout << "*** You Died! Try again? ***"
			 << "\n"
			 << "\n";
		cout << "(1) Yes, (0) No "
			 << "\n";
		cin >> this->choice;

		while (cin.fail() || this->choice > 1 || this->choice < 0)
		{
			cout << "Try again."
				 << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "(1) Yes, (0) No "
				 << "\n";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		if (this->choice == 1)
			this->load();
		else
			playing = false;
	}
}

void Game::createCharacter()
{
	string name = "";
	cout << "Character name: ";
	getline(cin, name);
	cout << "Hello World!" << endl;

	for (size_t i = 0; i < this->player.size(); i++)
	{
		while (name == this->player[i].getName())
		{
			cout << "Error. Character already exists."
				 << "\n";
			cout << "Character name: ";
			getline(cin, name);
			cout << "Hello World!" << endl;
		}
	}

	player.push_back(Character());
	loadedPlayer = player.size() - 1;
	player[loadedPlayer].initialize(name);
}

void Game::levelUpCharacter()
{
	this->player[loadedPlayer].levelUp();

	if (this->player[loadedPlayer].getStatPoints() > 0)
	{
		cout << "You have points to allocate!"
			 << "\n\n";

		cout << "Stat to upgrade: "
			 << "\n";
		cout << "0: Strength "
			 << "\n";
		cout << "1: Vitality "
			 << "\n";
		cout << "2: Dexterity "
			 << "\n";
		cout << "3: Intelligence "
			 << "\n";

		cin >> this->choice;

		while (cin.fail() || this->choice > 3)
		{
			cout << "Try again."
				 << endl;
			cin.clear();
			cin.ignore(100, '\n');

			cout << "Stat to upgrade: "
				 << endl;
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << endl;

		switch (this->choice)
		{
		case 0: // STRENGTH
			this->player[loadedPlayer].addToStat(0, 1);
			break;

		case 1: // VITALITY
			this->player[loadedPlayer].addToStat(1, 1);
			break;

		case 2: // DEXTERITY
			this->player[loadedPlayer].addToStat(2, 1);
			break;

		case 3: // INTELLIGENCE
			this->player[loadedPlayer].addToStat(3, 1);
			break;

		default:

			break;
		}
	}
}

void Game::characterMenu()
{
	do
	{
		clearTerminal();

		cout << menu::title("Player Menu");

		cout << menu::divider();

		player[loadedPlayer].printStats();

		cout << menu::divider();

		cout << "*** Menu ***"
			 << "\n";
		cout << menu::item(0, "Back");
		cout << menu::item(1, "Print Inventory");
		cout << menu::item(2, "Equip Item");
		cout << "\n";
		cout << "Choice";
		cin >> this->choice;

		while (cin.fail() || this->choice < 0 || this->choice > 2)
		{
			cout << "Try again."
				 << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "*** Menu ***"
				 << "\n";
			cout << "0: Back"
				 << "\n";
			cout << "1: Print Inventory"
				 << "\n";
			cout << "2: Equip Item"
				 << "\n";
			cout << "\n";
			cout << "Choice: ";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << endl;

		switch (this->choice)
		{
		case 1:
			cout << this->player[this->loadedPlayer].getInventoryToString();

			break;

		case 2:
			cout << this->player[this->loadedPlayer].getInventoryToString();

			cout << "Item index: ";
			cin >> this->choice;

			while (cin.fail() || this->choice < 0 || this->choice >= this->player[this->loadedPlayer].getInventorySize())
			{
				cout << "Try again."
					 << "\n";
				cin.clear();
				cin.ignore(100, '\n');

				cout << "Item index: ";
				cin >> this->choice;
			}

			cin.ignore(100, '\n');
			cout << endl;

			this->player[this->loadedPlayer].equipItem(this->choice);

			break;
		default:
			break;
		}
		if (this->choice > 0)
		{
			cout << "Enter to continue..." << endl;
			cin.get();
		}

	} while (this->choice > 0);
}

void Game::save()
{
	ofstream outFile(fileName);

	if (outFile.is_open())
	{
		for (size_t i = 0; i < this->player.size(); i++)
		{
			outFile << this->player[i].to_String() << "\n";
			outFile << this->player[i].getSaveInventoryToString() << "\n";
		}
	}

	outFile.close();
}

void Game::load()
{
	ifstream inFile(fileName);

	this->player.clear();

	string name = "";
	int distanceWandered = 0;
	int currency = 0;
	int level = 0;
	int experience = 0;
	int strength = 0;
	int vitality = 0;
	int dexterity = 0;
	int intelligence = 0;
	int health = 0;
	int stamina = 0;
	int points = 0;

	int itemType = 0;
	int defense = 0;
	int type = 0;
	int minAttack = 0;
	int maxAttack = 0;

	int buyValue = 0;
	int sellValue = 0;
	int rarity = 0;

	Inventory tempItems;

	string line = "";

	stringstream str;

	// check if file is open
	if (inFile.is_open())
	{
		// read in lines from file
		while (getline(inFile, line))
		{

			str.str(line);
			str >> name >> distanceWandered >> currency >> level >> experience >> strength >> vitality >> dexterity >> intelligence >> health >> stamina >> points;

			// Create player
			Character temp(name, distanceWandered, currency, level,
						   experience, strength, vitality, dexterity, intelligence,
						   health, stamina, points);

			// String Weapon
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				minAttack >> maxAttack;

			Weapon weapon(minAttack, maxAttack, name, level, buyValue, sellValue, rarity);

			// Gear head string
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				defense >> type;

			Gear helmet(type, defense, name, level, buyValue, sellValue, rarity);

			// Gear chest string
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				defense >> type;

			Gear chest_armor(type, defense, name, level, buyValue, sellValue, rarity);

			// Gear arms string
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				defense >> type;

			Gear armor_arms(type, defense, name, level, buyValue, sellValue, rarity);

			// Gear legs string
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				defense >> type;

			Gear armor_legs(type, defense, name, level, buyValue, sellValue, rarity);

			// Set armor
			temp.setGearHead(helmet);
			temp.setGearChest(chest_armor);
			temp.setGearArms(armor_arms);
			temp.setGearLegs(armor_legs);

			// Set weapon
			temp.setWeapon(weapon);

			// Add Inventory Items
			str.clear();
			line.clear();
			if (!inFile.is_open() || inFile.eof())
			{
				break;
			}
			getline(inFile, line);

			str.str(line);

			while (str >> itemType >> name >> level >>
				   rarity >> buyValue >> sellValue >>
				   minAttack >> maxAttack)
			{
				temp.addItem(
					Weapon(
						minAttack,
						maxAttack,
						name,
						level,
						buyValue,
						sellValue,
						rarity));
			}

			str.clear();
			line.clear();
			getline(inFile, line);

			str.str(line);

			while (str >>
				   itemType >> name >> level >>
				   rarity >> buyValue >> sellValue >>
				   defense >> type)
			{
				temp.addItem(
					Gear(
						type,
						defense,
						name,
						level,
						buyValue,
						sellValue,
						rarity));
			}
			clearTerminal();

			this->player.push_back(Character(temp));

			cout << "Player " << temp.getName() << " loaded!\n";

			str.clear();
		}
	}

	inFile.close();

	if (this->player.size() <= 0)
	{
		throw "Error. No players found.";
	}
}

void Game::select()
{
	cout << "Select player: "
		 << "\n\n";

	for (size_t i = 0; i < this->player.size(); i++)
	{
		cout << "Index: " << i << " = " << this->player[i].getName() << " Level: " << this->player[i].getLevel() << "\n";
	}

	cout << "\n";

	cout << "Choice: ";

	cin >> this->choice;

	while (cin.fail() || this->choice >= this->player.size() || this->choice < 0)
	{
		cout << "Try again." << endl;
		cin.clear();
		cin.ignore(100, '\n');

		cout << "Select player: " << endl;
		cin >> this->choice;
	}

	cin.ignore(100, '\n');
	cout << endl;

	this->loadedPlayer = this->choice;

	cout << this->player[this->loadedPlayer].getName() << " is selected."
		 << "\n\n";
}

// This function generates a "random" event for the player to handle
// It takes the player as a parameter, as well as the array of
// enemies so that it can generate an appropriate event
void Game::travel()
{

	// "Generate" a new event.
	this->player[loadedPlayer].travel();

	// Create a new event object.
	Event ev;

	// "Generate" the event.
	ev.generate(this->player[loadedPlayer], this->enemies);
}
void Game::rest()
{
	// The resting cost is the amount of healthPoints the player needs to restore to full.
	int restingCost = this->player[this->loadedPlayer].getHealthPointsMax() - this->player[this->loadedPlayer].getHealthPoints();
	cout << "*** Sleep ***"
		 << "\n\n";
	cout << "Resting costs you: " << restingCost << "\n";
	cout << "Your currency: " << this->player[this->loadedPlayer].getShards() << "\n";
	cout << "healthPoints: " << this->player[this->loadedPlayer].getHealthPoints() << " / " << this->player[this->loadedPlayer].getHealthPointsMax() << "\n\n";

	if (this->player[this->loadedPlayer].getShards() < restingCost)
	{
		cout << "Not enough currency."
			 << "\n\n";
	}
	else if (this->player[this->loadedPlayer].getHealthPoints() >= this->player[this->loadedPlayer].getHealthPointsMax())
	{
		cout << "Health is full."
			 << "\n\n";
	}
	else
	{
		cout << "\n\n Rest? (1) Yes, (0) No..."
			 << "\n\n";

		cin >> this->choice;

		while (cin.fail() || this->choice > 1 || this->choice < 0)
		{
			cout << "Try again." << endl;
			cin.clear();
			cin.ignore(100, '\n');

			cout << "\n\n Rest? (1) Yes, (0) No..."
				 << "\n\n";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << endl;

		if (this->choice == 1)
		{
			this->player[this->loadedPlayer].resetHealthPoints();
			this->player[this->loadedPlayer].payShards(restingCost);
			cout << "Rested!"
				 << "\n\n";
		}
		else
		{
			cout << "..."
				 << "\n\n";
		}
	}
}