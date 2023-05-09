#include "inventory.h"

Inventory::Inventory()
{
	// Create a new array of Items with the given capacity
	this->capacity = 5;
	this->numberOfItems = 0;
	this->ItemArray = new Item *[capacity];
	this->initialize();
}

Inventory::~Inventory()
{
	// This function deletes the ItemArray and frees the memory that it was using.
	// The variable numberOfItems keeps track of the number of items in the array.
	// When the destructor is called, it loops through the array and deletes each Item object.
	// It then deletes the array itself.
	for (size_t i = 0; i < this->numberOfItems; i++)
	{
		delete this->ItemArray[i];
	}
	delete[] this->ItemArray;
}

// This function allows the program to add items to the array, and keep track of how many items are in the array.
Inventory::Inventory(const Inventory &object)
{
	this->capacity = object.capacity;
	this->numberOfItems = object.numberOfItems;
	this->ItemArray = new Item *[this->capacity];

	for (size_t i = 0; i < this->numberOfItems; i++)
	{
		this->ItemArray[i] = object.ItemArray[i]->clone();
	}

	initialize(this->numberOfItems);
}

Item &Inventory::operator[](const int index)
{
	if (index < 0 || index >= this->numberOfItems)
	{
		throw("Out of range!");
	}

	return *this->ItemArray[index];
}

// Copies the contents of the object into the current object
void Inventory::operator=(const Inventory &object)
{
	// Deletes the current items
	for (size_t i = 0; i < this->numberOfItems; i++)
	{
		delete this->ItemArray[i];
	}
	delete[] this->ItemArray;

	// Copies the values from the object
	this->capacity = object.capacity;
	this->numberOfItems = object.numberOfItems;
	this->ItemArray = new Item *[this->capacity];

	// Clones each item in the object
	for (size_t i = 0; i < this->numberOfItems; i++)
	{
		this->ItemArray[i] = object.ItemArray[i]->clone();
	}

	initialize(this->numberOfItems);
}

// This code is used to scale up the inventory when the player picks up a new item.
// The purpose of the code is to make sure that the inventory can always hold the
// maximum number of items.

void Inventory::scaleUp()
{
	this->capacity *= 2;

	Item **tempArray = new Item *[this->capacity];

	for (size_t i = 0; i < this->numberOfItems; i++)
	{
		tempArray[i] = this->ItemArray[i];
	}

	delete[] this->ItemArray;

	this->ItemArray = tempArray;

	this->initialize(this->numberOfItems);
}

void Inventory::initialize(const int F) // initializes the inventory
{
	for (size_t i = F; i < capacity; i++) // loops through the inventory
	{
		this->ItemArray[i] = nullptr; // sets each item to null
	}
}

// This function adds an item to the inventory.
// It scales up the array if the capacity is reached.
void Inventory::addItem(const Item &item)
{
	if (this->numberOfItems >= this->capacity)
	{
		scaleUp();
	}

	this->ItemArray[this->numberOfItems] = item.clone();
	this->numberOfItems++;
}

void Inventory::removeItem(int index)
{
	if (index < 0 || index >= this->numberOfItems)
	{
		throw("Out of range!");
	}
	delete this->ItemArray[index];
	this->ItemArray[index] = this->ItemArray[this->numberOfItems - 1];
	this->ItemArray[this->numberOfItems - 1] = nullptr;
	this->numberOfItems--;
}