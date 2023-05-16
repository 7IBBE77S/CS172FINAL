wiping equipped weapons/gear when loading a character.

Nic 1 100 1 0 3 4 7 10 28 7 0 Wizard 0 Staff 1 0 1 1 1 5 1 Hood 1 0 1 1 1 1 1 Robe 1 0 1 1 1 1 1 Gloves 1 0 1 1 1 1 1 Trousers 1 0 1 1 1 1 
0 Staff 1 0 1 1 1 5 
1 Hood 1 0 1 1 1 1 1 Robe 1 0 1 1 1 1 1 Gloves 1 0 1 1 1 1 1 Trousers 1 0 1 1 1 1 



Nic 1 100 1 0 3 4 7 10 28 7 0 Unknown 0 Nic 1 0 0 0 0 0 1 Nic 1 0 0 0 0 0 1 Nic 1 0 0 0 0 0 1 Nic 1 0 0 0 0 0 1 Nic 1 0 0 0 0 0 
0 Staff 1 0 1 1 1 5 
1 Hood 1 0 1 1 1 1 1 Robe 1 0 1 1 1 1 1 Gloves 1 0 1 1 1 1 1 Trousers 1 0 1 1 1 1 




# ADD:

- [/] give character starting gear.
- [] add a resurrection/revive token as an item drop check if you have one once you die. If you do have one then using it will restart the encounter.
- [] add flavor text.
- [] add colors (might cause issues with OS that do not support ANSI escape sequences.)
- [/] add a way to save and load characters.
- [] add potion heals or activates defense .
- [] add the ability for monsters to poison you or apply bleed.
- [] maybe implement a counter to the monsters ability to poison by adding. 
- [/] add delete functionality for players.
- [] maybe a special attack every third round.
- [] add classes (wizard, warrior, rogue, etc)
- [] if player has a full set of gear they will get a bonus
- [] add shielding it would essentially act as more health or add some sort of durability/resistance buff
- [] add a cool ascii art intro
- [] add a way to save and load characters
- [/] replace missing health with underscores |▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓_____________|
- [] Somehow make more engaging. In terms of UI, gameplay/gameloop.
- [] add items for battle options. Once option 3 is selected it will prompt the user to use a health potion, shield potion (resistance buff), flame, bleed, poison enchantment, etc. This will need to be added as item drops just like gear.
- [] beautify UI
- [] add boss fights. Derived from the monster class.
- [] maybe simplify/clean up player.cpp,event.cpp, and game.cpp. They are getting a little messy and the readability is lacking.
- [] unequip gear and it will go back into inventory.
- [] fix negative values on items.
- [] have different monster types
- [] DOCUMENTATION


## Code ideas:
```cpp

// implement heal in the same way sleep works maybe?
or
int HealPlayer(){

	int healValue = generateRandBetween(MIN_HEAL, MAX_HEAL);

	int healthDiff = PLAYER_HEALTH - currentPlayerHealth;
	if (healthDiff >= healValue) {
		currentPlayerHealth += healValue;
		return healValue;
	} else {
		currentPlayerHealth = PLAYER_HEALTH;
		return healthDiff;
	}
	// currentMonsterHealth = currentMonsterHealth - dmgValue

}
```cpp
player[loadedPlayer].getInventory().add(Gear::generateGear(0, 0));
```

FIX:

- [] -1 needs to be fixed
- [] fix colors for heath bar.
- [] when the player does have gear and you try to equip it you will not be able to leave. This can be fixed by adding default gear to the player.
- [] game just ends when you kill all the monsters it should take you back to the main menu... sometimes.
- [/] when equipping gear it will not display the gear type on some pieces.
- [] fix character names. Its not accounting for white spaces.










