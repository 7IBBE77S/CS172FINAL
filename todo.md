# ADD:


- [] give character starting gear.
- [] add a resurrection/revive token as an item drop check if you have one once you die. If you do have one then using it will restart the encounter.
- [] add flavor text.
- [] add colors (might cause issues with OS that do not support ANSI escape sequences.)
- [] add a way to save and load characters.
- [] add potion heals or activates defense .
- [] add the ability for monsters to poison you or apply bleed.
- [] maybe implement a counter to the monsters ability to poison by adding. 
- [] add delete functionality for players.
- [] maybe a special attack every third round.
- [] add classes (wizard, warrior, rogue, etc)
- [] if player has a full set of gear they will get a bonus
- [] add shielding it would essentially act as more health or add some sort of durability/resistance buff
- [] add a cool ascii art intro
- [] add a way to save and load characters
- [] replace missing health with underscores |▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓_____________|
- [] Somehow make more engaging. In terms of UI, gameplay/gameloop.
- [] DOCUMENTATION
- [] game just ends when you kill all the monsters it should take you back to the main menu.


## Code ideas:
```cpp
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









