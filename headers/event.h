#ifndef EVENT_H
#define EVENT_H

#include "includes.h"
#include "player.h"
#include "monster.h"


class Event
{
public:
	Event();
	~Event();
	void generate(Character &player, Dynamic<Monster> &enemies);
	void shop(Character &player);
	void enemy(Character &player, Dynamic<Monster> &enemies);

	static int numberOfEvents;
};

#endif

