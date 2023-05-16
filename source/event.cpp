#include "event.h"
#include "functions.h"
#include <unistd.h>
// #include <term.h>
#include <map>
#include <string>
#include "wizard.h"
using namespace std;

struct Colors
{
	std::string LightRed;
	std::string Red;
	std::string Green;
	std::string Yellow;
	std::string Blue;
	std::string Magenta;
	std::string Purple;
	std::string Cyan;
	std::string White;
	std::string Grey;
	std::string Clean;
};

const Colors colors = {
	.LightRed = "\033[1;31m",
	.Red = "\x1b[31m",
	.Green = "\x1b[32m",
	.Yellow = "\x1b[33m",

	.Blue = "\x1b[34m",
	.Magenta = "\x1b[35m",
	.Purple = "\x1b[36m",
	.Cyan = "\x1b[36m",
	.White = "\x1b[37m",
	.Grey = "\x1b[90m",
	.Clean = "\x1b[0m",
};
Event::Event()
{
}

Event::~Event()
{
}
int Event::numberOfEvents = 4;

void Event::generate(Character &player, Dynamic<Monster> &enemies)
{

	int i = rand() % Event::numberOfEvents;
	if (i == 0)
	{
		this->enemy(player, enemies);
	}
	else if (i == 1)
	{
		this->shop(player);
	}
	else if (i == 2)
	{
		this->deadNPC(player);
	}
	else if (i == 3)
	{
		if (player.getLevel() > 14)
		{
			this->boss(player, enemies);
		}
		else
		{
			this->enemy(player, enemies);
		}
	}
}
void generateWeapon(Inventory &shop, Character &player)
{
	shop.addItem(Weapon(player.getLevel() + rand() % 5, rand() % 4));
}
void generateGear(Inventory &shop, Character &player)
{
	shop.addItem(Gear(player.getLevel() + rand() % 5, rand() % 4));
}
void Event::shop(Character &player)
{
	int choice = 0;
	bool inShop = true;
	Inventory shopInventory;
	string inv;

	int numberOfItems = rand() % 20 + 10;
	bool toss = false;

	for (int i = 0; i < numberOfItems; i++)
	{
		toss = rand() % 2;
		// Add the player's level to a random number from 0 to 4 to create a random weapon level.
		// Add a random number from 0 to 3 to create a random weapon type
		// shopInventory.addItem(generateWeapon());.
		if (toss > 0)
		{
			generateWeapon(shopInventory, player);
		}
		else
		{
			generateGear(shopInventory, player);
		}
	}

	while (inShop)
	{

		clearTerminal();
		cout << "*** Welcome to the Shop! ***"
			 << endl;

		cout << "1: Buy"
			 << "\n";
		cout << "2: Sell"
			 << "\n";
		cout << "0: Leave"
			 << "\n";
		cout << endl;

		cout << "Choice: ";

		cin >> choice;

		while (cin.fail() || choice > 3 || choice < 0)
		{
			clearTerminal();

			cout << "Try again." << endl;
			cin.clear();
			cin.ignore(100, '\n');

			cout << "*** Shop ***"
				 << endl;

			cout << "1: Buy"
				 << "\n";
			cout << "2: Sell"
				 << "\n";
			cout << "0: Leave"
				 << "\n";
			cout << "\n";

			cout << "Choice: ";
			cin >> choice;
		}

		cin.ignore(100, '\n');
		cout << endl;

		switch (choice)
		{
		case 0:
			inShop = false;
			break;

		case 1:

			cout << "*** Available Items ***"
				 << endl;

			cout << " - Shards: " << player.getShards() << endl;

			inv.clear();

			for (int i = 0; i < shopInventory.size(); i++)
			{
				inv += to_string(i) + ": " + shopInventory[i].toString() + "\n - PRICE: " + to_string(shopInventory[i].getBuyValue()) + "\n";
			}

			cout << inv << "\n";

			cout << "Shards: " << player.getShards() << "\n";
			cout << "Choose item to buy (-1 to cancel): ";

			cin >> choice;

			while (cin.fail() || choice > shopInventory.size() || choice < -1)
			{
				clearTerminal();

				cout << "Try again."
					 << "\n";
				cin.clear();
				cin.ignore(100, '\n');

				cout << "Shards: " << player.getShards() << "\n";
				cout << "Choice of item (-1 to cancel): ";
				cin >> choice;
			}

			cin.ignore(100, '\n');
			cout << "\n";

			if (choice == -1)
			{
				cout << "Cancelled..."
					 << "\n";
			}
			else if (player.getShards() >= shopInventory[choice].getBuyValue())
			{
				player.payShards(shopInventory[choice].getBuyValue());
				player.addItem(shopInventory[choice]);

				cout << "Bought item " << shopInventory[choice].getName() << " -" << shopInventory[choice].getBuyValue() << "\n";

				shopInventory.removeItem(choice);
			}
			else
			{
				cout << "Can't afford this item!"
					 << "\n";
			}

			break;

		case 2:

			cout << player.getInventoryToString(true) << "\n";

			cout << "*** Do you have anything to sell? ***"
				 << endl;

			cout << " - Shards: " << player.getShards() << endl;

			if (player.getInventorySize() > 0)
			{
				cout << "Shards: " << player.getShards() << "\n";
				cout << "Choice of item (-1 to cancel): ";

				cin >> choice;

				while (cin.fail() || choice > player.getInventorySize() || choice < -1)
				{
					clearTerminal();

					cout << "Try again."
						 << "\n";
					cin.clear();
					cin.ignore(100, '\n');

					cout << "Shards: " << player.getShards() << "\n";
					cout << "Choice of item (-1 to cancel): ";
					cin >> choice;
				}

				cin.ignore(100, '\n');
				cout << "\n";

				if (choice == -1)
				{
					cout << "Cancelled..."
						 << "\n";
				}
				else
				{
					player.gainShards(player.getItem(choice).getSellValue());

					cout << "Item sold!"
						 << "\n";
					cout << "Shards earned: " << player.getItem(choice).getSellValue() << endl;
					player.removeItem(choice);
				}
			}
			else
			{
				cout << "Inventory empty..."
					 << "\n";
			}

			break;

		default:
			break;
		}

		cout << "ENTER to continue..."
			 << "\n";
		cin.get();
	}

	cout << "You left the shop.."
		 << endl;
}
void Event::deadNPC(Character &player)
{
	char ans;
	Inventory found;
	clearTerminal();
	cout << "You find the body of another adventurer!"
		 << endl;
	cout << "Continue..."
		 << endl;
	cin.get();
	int toss = rand() % 2;
	if (toss > 0)
	{
		generateWeapon(found, player);
	}
	else
	{
		generateGear(found, player);
	}
	clearTerminal();
	cout << "You found a " << found[0].toString() << "." << '\n';
	cout << "Do you wish to take this item?" << '\n';
	cin.get(ans);
	clearTerminal();
	if (ans == 'y' || ans == 'Y')
	{
		cout << found[0].toString() << " has been collected." << '\n';
		player.addItem(found[0]);
	}
	else
	{
		cout << "You leave this warriors body undisturbed." << '\n';
	}
	cin.ignore(100, '\n');
}

void Event::enemy(Character &player, Dynamic<Monster> &enemies)
{
	cout << "You have stumbled upon monsters!"
		 << endl;

	// get player subclass

	// playerType subclass = player.getSubclassType();
	// player type to string

	bool playerTurn = false;
	int choice = 0;

	int toss = rand() % 2 + 1;

	if (toss == 1)
		playerTurn = true;
	else
		playerTurn = false;

	bool escape = false;
	bool playerDefeated = false;
	bool enemiesDefeated = false;

	int numberOfEnemies = rand() % 5 + 1;

	for (size_t i = 0; i < numberOfEnemies; i++)
	{
		enemies.push(Monster(player.getLevel() + rand() % 3));
	}

	int damage = 0;
	int gainExperience = 0;
	int gainShards = 0;
	int playerTotal = 0;
	int enemyTotal = 0;
	int combatTotal = 0;
	int combatRollPlayer = 0;
	int combatRollMonster = 0;

	while (!escape && !playerDefeated && !enemiesDefeated)
	{
		if (playerTurn && !playerDefeated)
		{

			cout << "Prepare for battle!"
				 << endl;
			cout << "Continue..."
				 << endl;
			cin.get();
			clearTerminal();

			cout << "*** Battle Options ***"
				 << endl;

			cout << "1: Attack"
				 << "\n";
			cout << "2: Defend"
				 << "\n";
			cout << "3: Use Item"
				 << "\n";
			if (player.getSubclassType() == playerType::WIZARD)
			{
				cout << "4: Restore health"
					 << "\n";
			}
			else if (player.getSubclassType() == playerType::WARRIOR)
			{
				cout << "4: Heavy Attack"
					 << "\n";
			}
			else if (player.getSubclassType() == playerType::ROGUE)
			{
				cout << "4: Attack with dagger"
					 << "\n";
			}

			cout << "0: Escape"
				 << "\n";
			cout << endl;

			cout << "Choice: ";

			cin >> choice;

			std::string healthColor;
			int health = player.getHealthPoints();

			std::string healthBars;

			if (choice == 2)
			{
				healthColor = colors.Cyan;
				for (int i = 0; i < health; i++)
				{
					healthBars += "#";
				}
			}
			else
			{

				if (health >= player.getHealthPointsMax() * 0.75)
				{
					for (int i = 0; i < health; i++)
					{
						healthBars += "#";
					}
					for (int i = health; i < player.getHealthPointsMax(); i++)
					{
						healthBars += "_";
					}
					healthColor = colors.White;
				}
				else if (health >= player.getHealthPointsMax() / 2)
				{
					for (int i = 0; i < health; i++)
					{
						healthBars += "#";
					}
					for (int i = health; i < player.getHealthPointsMax(); i++)
					{
						healthBars += "_";
					}
					healthColor = colors.Yellow;
				}
				else if (health >= player.getHealthPointsMax() / 4)
				{
					for (int i = 0; i < health; i++)
					{
						healthBars += "#";
					}
					for (int i = health; i < player.getHealthPointsMax(); i++)
					{
						healthBars += "_";
					}
					healthColor = colors.LightRed;
				}
				else
				{
					for (int i = 0; i < health; i++)
					{
						healthBars += "#";
					}
					for (int i = health; i < player.getHealthPointsMax(); i++)
					{
						healthBars += "_";
					}
					healthColor = colors.Red;
				}
			}

			// If using defense, the health bar is cyan
			cout << "Health: " << healthColor << health << colors.Clean << " / " << player.getHealthPointsMax() << " " << healthColor << "|" << healthBars << "|" << colors.Clean << endl;

			while (cin.fail() || choice > 4 || choice < 0)
			{
				clearTerminal();

				cout << "Try again."
					 << "\n";
				cin.clear();
				cin.ignore(100, '\n');

				cout << "*** Battle Options ***"
					 << endl;

				cout << "1: Attack"
					 << "\n";
				cout << "2: Defend"
					 << "\n";
				cout << "3: Use Item"
					 << "\n";
				if (player.getSubclassType() == playerType::WIZARD)
				{
					cout << "4: Restore health"
						 << "\n";
				}
				else if (player.getSubclassType() == playerType::WARRIOR)
				{
					cout << "4: Heavy Attack"
						 << "\n";
				}
				else if (player.getSubclassType() == playerType::ROGUE)
				{
					cout << "4: Attack with dagger"
						 << "\n";
				}
				cout << "0: Escape"
					 << "\n";
				cout << endl;

				cout << "Choice: ";
				cin >> choice;
			}

			cin.ignore(100, '\n');
			cout << endl;

			switch (choice)
			{
			case 0:
				escape = true;
				break;

			case 1:

				// Select enemy
				cout << "Select enemy: "
					 << endl;

				for (int i = 0; i < enemies.size(); i++)
				{
					cout << i << ": "
						 << "Level: " << enemies[i].getLevel() << " - "
						 << "healthPoints: " << enemies[i].getHealthPoint() << "/" << enemies[i].getHealthPointMax() << " - "
						 << "defense: " << enemies[i].getDefense() << " - "
						 << "Accuracy: " << enemies[i].getAccuracy() << " - "
						 << "Damage: " << enemies[i].getMinAttack() << " - " << enemies[i].getMaxAttack() << "\n";
				}

				cout << endl;
				cout << "Choice: ";

				cin >> choice;

				while (cin.fail() || choice >= enemies.size() || choice < 0)
				{
					cout << "Try again."
						 << "\n";
					cin.clear();
					cin.ignore(100, '\n');

					cout << "Select enemy: "
						 << endl;
					cout << "Choice: ";
					cin >> choice;
				}

				cin.ignore(100, '\n');
				cout << endl;

				// Attack roll
				combatTotal = enemies[choice].getDefense() + player.getAccuracy();
				enemyTotal = enemies[choice].getDefense() / (double)combatTotal * 100;
				playerTotal = player.getAccuracy() / (double)combatTotal * 100;
				combatRollPlayer = rand() % playerTotal + 1;
				combatRollMonster = rand() % enemyTotal + 1;

				cout << "Combat total: " << combatTotal << "\n";
				cout << "Monster percent: " << enemyTotal << "\n";
				cout << "Player percent: " << playerTotal << endl;
				cout << "Player roll: " << combatRollPlayer << "\n";
				cout << "Monster roll: " << combatRollMonster << endl;

				if (combatRollPlayer > combatRollMonster) // Hit
				{
					cout << "HIT! "
						 << endl;

					damage = player.getDamage();
					enemies[choice].Damaged(damage);

					cout << "Damage: " << damage << "!"
						 << endl;

					if (!enemies[choice].isAlive())
					{
						cout << "Monster Slain!"
							 << endl;
						gainExperience = enemies[choice].getExperience();
						player.gainExperience(gainExperience);
						gainShards = rand() % enemies[choice].getLevel() * 10 + 1;
						player.gainShards(gainShards);
						cout << "Experience Gained: " << gainExperience << "\n";
						cout << "Shards Gained: " << gainShards << endl;

						// Item roll
						int roll = rand() % 100 + 1;
						int rarity = -1;

						// Rarity determination
						if (roll > 20)
						{
							// Common
							rarity = 0;
							if (roll > 30)
							{
								// Uncommon
								rarity = 1;
								if (roll > 50)
								{ // Rare
									rarity = 2;
									if (roll > 70)
									{
										// Legendary
										rarity = 3;
										if (roll > 90)
										{
											// Mythic
											rarity = 4;
										}
									}
								}
							}
						}

						if (roll >= 0)
						{
							roll = rand() % 100 + 1;

							if (roll > 50)
							{
								Weapon tempW(player.getLevel(), rarity);
								player.addItem(tempW);
								cout << "A weapon drop."
									 << "\n";
							}
							else
							{
								Gear tempG(player.getLevel(), rarity);
								player.addItem(tempG);
								cout << "A piece of gear drop."
									 << "\n";
							}
						}

						enemies.remove(choice);
					}
				}
				else
				{
					cout << "Monster dodged attack! \n\n";
				}

				break;

			case 2:

				break;

			case 3:

				break;
			case 4:
				if (player.getSubclassType() == playerType::WIZARD)
				{
					if (health == player.getHealthPointsMax())
					{
						cout << "You are already at full health! \n\n";
						break;
					}
					else
					{
						player.restoreHealth();
						cout << "You have been healed! \n\n";
						break;
					}
				}
				else if (player.getSubclassType() == playerType::WARRIOR)
				{
					// player.heavyAttack(&enemies[choice]);
					damage = player.getMaxDamage();
					enemies[choice].Damaged(damage);
					cout << "You used heavy attack! \n\n";
					break;
				}
				else if (player.getSubclassType() == playerType::ROGUE)
				{
					break;
				}
				break;

			default:
				break;
			}

			// End turn
			playerTurn = false;
		}
		else if (!playerTurn && !playerDefeated && !escape && !enemiesDefeated)
		{
			cout << "Monsters turn!"
				 << "\n";

			cout << "Continue..."
				 << endl;
			cin.get();
			clearTerminal();

			for (int i = 0; i < enemies.size(); i++)
			{
				cout << "Continue..."
					 << endl;
				cin.get();
				clearTerminal();

				cout << "Monster: " << i << endl;

				combatTotal = enemies[i].getAccuracy() + (player.getDefense() + player.getAdditionalDefense());
				enemyTotal = enemies[i].getAccuracy() / (double)combatTotal * 100;
				playerTotal = (player.getDefense() + player.getAdditionalDefense()) / (double)combatTotal * 100;
				combatRollPlayer = rand() % playerTotal + 1;
				combatRollMonster = rand() % enemyTotal + 1;

				cout << "Combat total: " << combatTotal << "\n";
				cout << "Monster percent: " << enemyTotal << "\n";
				cout << "Player percent: " << playerTotal << endl;
				cout << "Player roll: " << combatRollPlayer << "\n";
				cout << "Monster roll: " << combatRollMonster << endl;

				if (combatRollPlayer < combatRollMonster)
				{
					cout << "HIT! " << endl;

					damage = enemies[i].getDamage();
					player.Damaged(damage);

					cout << "Damage: " << damage << "!" << endl;
					std::string healthColor;
					int health = player.getHealthPoints();

					std::string healthBars;

					if (choice == 2)
					{
						for (int i = 0; i < health; i++)
						{
							healthBars += "#";
						}
						for (int i = health; i < player.getHealthPointsMax(); i++)
						{
							healthBars += "_";
						}
						healthColor = colors.Cyan;
					}
					else
					{

						if (health >= player.getHealthPointsMax() * 0.75)
						{
							for (int i = 0; i < health; i++)
							{
								healthBars += "#";
							}
							for (int i = health; i < player.getHealthPointsMax(); i++)
							{
								healthBars += "_";
							}
							healthColor = colors.White;
						}
						else if (health >= player.getHealthPointsMax() / 2)
						{
							for (int i = 0; i < health; i++)
							{
								healthBars += "#";
							}
							for (int i = health; i < player.getHealthPointsMax(); i++)
							{
								healthBars += "_";
							}
							healthColor = colors.Yellow;
						}
						else if (health >= player.getHealthPointsMax() / 4)
						{
							for (int i = 0; i < health; i++)
							{
								healthBars += "#";
							}
							for (int i = health; i < player.getHealthPointsMax(); i++)
							{
								healthBars += "_";
							}
							healthColor = colors.LightRed;
						}
						else
						{
							for (int i = 0; i < health; i++)
							{
								healthBars += "#";
							}
							for (int i = health; i < player.getHealthPointsMax(); i++)
							{
								healthBars += "_";
							}
							healthColor = colors.Red;
						}
					}

					// If using defense, the health bar is cyan
					cout << "Health: " << healthColor << health << colors.Clean << " / " << player.getHealthPointsMax() << " " << healthColor << "|" << healthBars << "|" << colors.Clean << endl;

					if (!player.isAlive())
					{
						cout << "YOU DIED"
							 << endl;
						cout << "Goodbye World..." << endl;
						playerDefeated = true;
					}
				}
				else
				{
					cout << "Monster dodged attack! \n\n";
				}
			}

			playerTurn = true;
		}

		if (!player.isAlive())
		{
			playerDefeated = true;
		}
		// else all enemies are defeated meaning you cant be dead
		else if (enemies.size() <= 0)
		{
			enemiesDefeated = true;
		}
	}
}

void Event::boss(Character &player, Dynamic<Monster> &enemies)
{
	cout << "You have stumbled upon the Boss!"
		 << endl;

	int maxHealth = player.getHealthPointsMax();
	int health = player.getHealthPoints();

	bool playerTurn = false;
	int choice = 0;

	int toss = rand() % 2 + 1;

	if (toss == 1)
		playerTurn = true;
	else
		playerTurn = false;

	bool escape = false;
	bool playerDefeated = false;
	bool enemiesDefeated = false;

	int numberOfEnemies = rand() % 5 + 1;

	enemies.push(Boss());
	if (player.getLevel() > 20)
	{
		for (size_t i = 0; i < numberOfEnemies; i++)
		{
			enemies.push(Monster(player.getLevel() + rand() % 3));
		}
	}

	int damage = 0;
	int gainExperience = 0;
	int gainShards = 0;
	int playerTotal = 0;
	int enemyTotal = 0;
	int combatTotal = 0;
	int combatRollPlayer = 0;
	int combatRollMonster = 0;

	while (!escape && !playerDefeated && !enemiesDefeated)
	{
		if (playerTurn && !playerDefeated)
		{

			cout << "Prepare for battle!"
				 << endl;
			cout << "Continue..."
				 << endl;
			cin.get();
			clearTerminal();

			cout << "*** Battle Options ***"
				 << endl;

			cout << "1: Attack"
				 << "\n";
			cout << "2: Defend"
				 << "\n";
			cout << "3: Use Item"
				 << "\n";
			if (player.getSubclassType() == playerType::WIZARD)
			{
				cout << "4: Restore health"
					 << "\n";
			}
			else if (player.getSubclassType() == playerType::WARRIOR)
			{
				cout << "4: Heavy Attack"
					 << "\n";
			}
			else if (player.getSubclassType() == playerType::ROGUE)
			{
				cout << "4: Attack with dagger"
					 << "\n";
			}

			cout << "0: Escape"
				 << "\n";
			cout << endl;

			cout << "Choice: ";

			cin >> choice;

			std::string healthColor;
			std::string healthBars;

			if (choice == 2)
			{
				healthColor = colors.Cyan;
				for (int i = 0; i < health; i++)
				{
					healthBars += "#";
				}
			}
			else
			{

				if (health >= maxHealth * 0.75)
				{
					for (int i = 0; i < health; i++)
					{
						healthBars += "#";
					}
					for (int i = health; i < maxHealth; i++)
					{
						healthBars += "_";
					}
					healthColor = colors.White;
				}
				else if (health >= maxHealth / 2)
				{
					for (int i = 0; i < health; i++)
					{
						healthBars += "#";
					}
					for (int i = health; i < maxHealth; i++)
					{
						healthBars += "_";
					}
					healthColor = colors.Yellow;
				}
				else if (health >= maxHealth / 4)
				{
					for (int i = 0; i < health; i++)
					{
						healthBars += "#";
					}
					for (int i = health; i < maxHealth; i++)
					{
						healthBars += "_";
					}
					healthColor = colors.LightRed;
				}
				else
				{
					for (int i = 0; i < health; i++)
					{
						healthBars += "#";
					}
					for (int i = health; i < maxHealth; i++)
					{
						healthBars += "_";
					}
					healthColor = colors.Red;
				}
			}

			// If using defense, the health bar is cyan
			cout << "Health: " << healthColor << health << colors.Clean << " / " << maxHealth << " " << healthColor << "|" << healthBars << "|" << colors.Clean << endl;

			while (cin.fail() || choice > 4 || choice < 0)
			{
				clearTerminal();

				cout << "Try again."
					 << "\n";
				cin.clear();
				cin.ignore(100, '\n');

				cout << "*** Battle Options ***"
					 << endl;

				cout << "1: Attack"
					 << "\n";
				cout << "2: Defend"
					 << "\n";
				cout << "3: Use Item"
					 << "\n";
				if (player.getSubclassType() == playerType::WIZARD)
				{
					cout << "4: Restore health"
						 << "\n";
				}
				else if (player.getSubclassType() == playerType::WARRIOR)
				{
					cout << "4: Heavy Attack"
						 << "\n";
				}
				else if (player.getSubclassType() == playerType::ROGUE)
				{
					cout << "4: Attack with dagger"
						 << "\n";
				}
				cout << "0: Escape"
					 << "\n";
				cout << endl;

				cout << "Choice: ";
				cin >> choice;
			}

			cin.ignore(100, '\n');
			cout << endl;

			switch (choice)
			{
			case 0:
				escape = true;
				enemies.remove(0);
				if (player.getLevel() > 20)
				{
					for (size_t i = 0; i < numberOfEnemies; i++)
					{
						enemies.remove(0);
					}
				}
				break;

			case 1:

				// Select enemy
				cout << "Select enemy: "
					 << endl;

				for (int i = 0; i < enemies.size(); i++)
				{
					cout << i << ": "
						 << "Level: " << enemies[i].getLevel() << " - "
						 << "healthPoints: " << enemies[i].getHealthPoint() << "/" << enemies[i].getHealthPointMax() << " - "
						 << "defense: " << enemies[i].getDefense() << " - "
						 << "Accuracy: " << enemies[i].getAccuracy() << " - "
						 << "Damage: " << enemies[i].getMinAttack() << " - " << enemies[i].getMaxAttack() << "\n";
				}

				cout << endl;
				cout << "Choice: ";

				cin >> choice;

				while (cin.fail() || choice >= enemies.size() || choice < 0)
				{
					cout << "Try again."
						 << "\n";
					cin.clear();
					cin.ignore(100, '\n');

					cout << "Select enemy: "
						 << endl;
					cout << "Choice: ";
					cin >> choice;
				}

				cin.ignore(100, '\n');
				cout << endl;

				// Attack roll
				combatTotal = enemies[choice].getDefense() + player.getAccuracy();
				enemyTotal = enemies[choice].getDefense() / (double)combatTotal * 100;
				playerTotal = player.getAccuracy() / (double)combatTotal * 100;
				combatRollPlayer = rand() % playerTotal + 1;
				combatRollMonster = rand() % enemyTotal + 1;

				cout << "Combat total: " << combatTotal << "\n";
				cout << "Monster percent: " << enemyTotal << "\n";
				cout << "Player percent: " << playerTotal << endl;
				cout << "Player roll: " << combatRollPlayer << "\n";
				cout << "Monster roll: " << combatRollMonster << endl;

				if (combatRollPlayer > combatRollMonster) // Hit
				{
					cout << "HIT! "
						 << endl;

					damage = player.getDamage();
					enemies[choice].Damaged(damage);

					cout << "Damage: " << damage << "!"
						 << endl;

					if (!enemies[choice].isAlive())
					{
						cout << "Monster Slain!"
							 << endl;
						gainExperience = enemies[choice].getExperience();
						player.gainExperience(gainExperience);
						gainShards = rand() % enemies[choice].getLevel() * 10 + 1;
						player.gainShards(gainShards);
						cout << "Experience Gained: " << gainExperience << "\n";
						cout << "Shards Gained: " << gainShards << endl;

						// Item roll
						int roll = rand() % 100 + 1;
						int rarity = -1;

						// Rarity determination
						if (roll > 20)
						{
							// Common
							rarity = 0;
							if (roll > 30)
							{
								// Uncommon
								rarity = 1;
								if (roll > 50)
								{ // Rare
									rarity = 2;
									if (roll > 70)
									{
										// Legendary
										rarity = 3;
										if (roll > 90)
										{
											// Mythic
											rarity = 4;
										}
									}
								}
							}
						}

						if (roll >= 0)
						{
							roll = rand() % 100 + 1;

							if (roll > 50)
							{
								Weapon tempW(player.getLevel(), rarity);
								player.addItem(tempW);
								cout << "A weapon drop."
									 << "\n";
							}
							else
							{
								Gear tempG(player.getLevel(), rarity);
								player.addItem(tempG);
								cout << "A piece of gear drop."
									 << "\n";
							}
						}

						enemies.remove(choice);
					}
				}
				else
				{
					cout << "Monster dodged attack! \n\n";
				}

				break;

			case 2:

				break;

			case 3:

				break;
			case 4:
				if (player.getSubclassType() == playerType::WIZARD)
				{
					if (health == maxHealth)
					{
						cout << "You are already at full health! \n\n";
						break;
					}
					else
					{
						player.restoreHealth();
						cout << "You have been healed! \n\n";
						break;
					}
				}
				else if (player.getSubclassType() == playerType::WARRIOR)
				{
					player.heavyAttack(&enemies[choice]);
					cout << "You used heavy attack! \n\n";
					break;
				}

			default:
				break;
			}

			// End turn
			playerTurn = false;
		}
		else if (!playerTurn && !playerDefeated && !escape && !enemiesDefeated)
		{
			cout << "Monsters turn!"
				 << "\n";

			cout << "Continue..."
				 << endl;
			cin.get();
			clearTerminal();

			for (int i = 0; i < enemies.size(); i++)
			{
				cout << "Continue..."
					 << endl;
				cin.get();
				clearTerminal();

				cout << "Monster: " << i << endl;

				combatTotal = enemies[i].getAccuracy() + (player.getDefense() + player.getAdditionalDefense());
				enemyTotal = enemies[i].getAccuracy() / (double)combatTotal * 100;
				playerTotal = (player.getDefense() + player.getAdditionalDefense()) / (double)combatTotal * 100;
				combatRollPlayer = rand() % playerTotal + 1;
				combatRollMonster = rand() % enemyTotal + 1;

				cout << "Combat total: " << combatTotal << "\n";
				cout << "Monster percent: " << enemyTotal << "\n";
				cout << "Player percent: " << playerTotal << endl;
				cout << "Player roll: " << combatRollPlayer << "\n";
				cout << "Monster roll: " << combatRollMonster << endl;

				if (combatRollPlayer < combatRollMonster)
				{
					cout << "HIT! " << endl;

					damage = enemies[i].getDamage();
					player.Damaged(damage);

					cout << "Damage: " << damage << "!" << endl;
					std::string healthColor;
					std::string healthBars;

					if (choice == 2)
					{
						for (int i = 0; i < health; i++)
						{
							healthBars += "#";
						}
						for (int i = health; i < maxHealth; i++)
						{
							healthBars += "_";
						}
						healthColor = colors.Cyan;
					}
					else
					{

						if (health >= maxHealth * 0.75)
						{
							for (int i = 0; i < health; i++)
							{
								healthBars += "#";
							}
							for (int i = health; i < maxHealth; i++)
							{
								healthBars += "_";
							}
							healthColor = colors.White;
						}
						else if (health >= maxHealth / 2)
						{
							for (int i = 0; i < health; i++)
							{
								healthBars += "#";
							}
							for (int i = health; i < maxHealth; i++)
							{
								healthBars += "_";
							}
							healthColor = colors.Yellow;
						}
						else if (health >= maxHealth / 4)
						{
							for (int i = 0; i < health; i++)
							{
								healthBars += "#";
							}
							for (int i = health; i < maxHealth; i++)
							{
								healthBars += "_";
							}
							healthColor = colors.LightRed;
						}
						else
						{
							for (int i = 0; i < health; i++)
							{
								healthBars += "#";
							}
							for (int i = health; i < maxHealth; i++)
							{
								healthBars += "_";
							}
							healthColor = colors.Red;
						}
					}

					// If using defense, the health bar is cyan
					cout << "Health: " << healthColor << health << colors.Clean << " / " << maxHealth << " " << healthColor << "|" << healthBars << "|" << colors.Clean << endl;

					if (!player.isAlive())
					{
						cout << "YOU DIED"
							 << endl;
						cout << "Goodbye World..." << endl;
						playerDefeated = true;
					}
				}
				else
				{
					cout << "You dodged the attack! \n\n";
				}
			}

			playerTurn = true;
		}

		if (!player.isAlive())
		{
			playerDefeated = true;
		}
		// else all enemies are defeated meaning you cant be dead
		else if (enemies.size() <= 0)
		{
			enemiesDefeated = true;
		}
	}
}