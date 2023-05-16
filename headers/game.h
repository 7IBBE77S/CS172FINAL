#ifndef GAME_H
#define GAME_H

#include "includes.h"
#include "event.h"
#include "player.h"
#include "wizard.h"
#include "warrior.h"
#include "rogue.h"

using namespace std;

class Game
{
private:
	int choice;
	bool playing;

	int loadedPlayer;
	std::vector<Character> player;
	//wizard
	std::vector<Wizard> wizard;
	//warrior
	std::vector<Warrior> warrior;
	//rogue
	std::vector<Rogue> rogue;




	std::string fileName;

	Dynamic<Monster> enemies;



public:
	Game();
	~Game();
	// Event currentEvent;

	void startGame();
	void mainMenu();
	void createCharacter();
	void deleteCharacter();
	void levelUpCharacter();
	void characterMenu();
	void save();
	void load();
	void select();
	void travel();
	void rest();

	inline bool isPlaying() const { return this->playing; }

	void clearTerminal()
	{
#ifdef __APPLE__
		std::system("clear");

#else
		std::system("cls");

#endif
	}
};

#endif
