#ifndef GAME_H
#define GAME_H

#include "includes.h"
#include "event.h"

using namespace std;

class Game
{
private:
	int choice;
	bool playing;

	int loadedPlayer;
	std::vector<Character> player;
	std::string fileName;

	Dynamic<Monster> enemies;

public:
	Game();
	~Game();

	void startGame();
	void mainMenu();
	void createCharacter();
	void levelUpCharacter();
	void characterMenu();
	void save();
	void load();
	void select();
	void travel();
	void rest();

	inline bool isPlaying() const { return this->playing; }
	// void clearTerminal()
	// {
	// 	if (system("cls"))
	// 		system("clear");
	// }

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
