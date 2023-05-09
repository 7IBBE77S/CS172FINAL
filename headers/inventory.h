#ifndef INVENTORY_H
#define INVENTORY_H

#include "includes.h"
#include "weapon.h"
#include "gear.h"

class Inventory
{
private:
	int capacity;
	int numberOfItems;
	Item **ItemArray;
	void scaleUp();
	void initialize(const int F = 0);

public:
	// The default constructor creates a new empty inventory.
	Inventory();

	// The copy constructor creates a new inventory that is a copy
	// of the provided inventory.
	Inventory(const Inventory &object);

	// The destructor frees up any dynamically allocated memory.
	~Inventory();

	// The assignment operator assigns the provided inventory to
	// this inventory.
	void operator=(const Inventory &object);

	// This method returns the number of items in the inventory.
	inline int size() const { return this->numberOfItems; };

	// This method returns a reference to the item at the specified
	// index in the inventory.
	Item &operator[](const int index);

	// This method adds the specified item to the inventory.
	void addItem(const Item &item);

	// This method removes the item at the specified index from the
	// inventory.
	void removeItem(int index);
	inline void debugOutput() const
	{
		for (size_t i = 0; i < this->numberOfItems; i++)
		{
			std::cout << this->ItemArray[i]->debugOutput() << std::endl;
		}
	};
};

#endif