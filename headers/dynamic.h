#ifndef DARR_H
#define DARR_H

// Dynamic generic array
// cant make cpp file because it is generic
// This class is a dynamic array that can be resized and expanded as needed.

// a fun custom simplified implementation of a "vector" i.e. (resizable dynamic array) made specificity this project. 
template <typename T>
class Dynamic
{
private:
	T **array;
	unsigned elementSize;
	unsigned startingCapacity;
	unsigned capacity;

	void scaleUp();
	void initialize(unsigned F);

public:
	Dynamic(unsigned size = 5);
	Dynamic(const Dynamic &object);
	~Dynamic();

	T &operator[](const unsigned index);
	void operator=(const Dynamic &object);

	unsigned maxCapacity();
	unsigned size();
	void push(const T element);
	void remove(const unsigned index, bool ordered = false);
};

template <typename T>
Dynamic<T>::Dynamic(unsigned size)
{
	this->startingCapacity = size;
	this->capacity = size;
	this->elementSize = 0;

	this->array = new T *[this->capacity];

	this->initialize(0);
}

template <typename T>
Dynamic<T>::Dynamic(const Dynamic &object)
{
	this->startingCapacity = object.startingCapacity;
	this->capacity = object.capacity;
	this->elementSize = object.elementSize;

	this->array = new T *[this->capacity];

	for (size_t i = 0; i < this->elementSize; i++)
	{
		this->array[i] = new T(*object.array[i]);
	}

	this->initialize(0);
}

template <typename T>
Dynamic<T>::~Dynamic()
{
	for (size_t i = 0; i < this->elementSize; i++)
	{
		delete this->array[i];
	}
	delete[] array;
}

template <typename T>
T &Dynamic<T>::operator[](const unsigned index)
{
	if (index < 0 || index >= this->elementSize)
		throw "Out of range!";

	return *this->array[index];
}

template <typename T>
void Dynamic<T>::operator=(const Dynamic &object)
{
	for (size_t i = 0; i < this->elementSize; i++)
	{
		delete this->array[i];
	}
	delete[] array;

	this->startingCapacity = object.startingCapacity;
	this->capacity = object.capacity;
	this->elementSize = object.elementSize;

	this->array = new T *[this->capacity];

	for (size_t i = 0; i < this->elementSize; i++)
	{
		this->array[i] = new T(*object.array[i]);
	}

	this->initialize(0);
}

template <typename T>
void Dynamic<T>::scaleUp()
{
	this->capacity *= 2; // double the capacity of the array

	T **tempArray = new T *[this->capacity]; // create a new array with the new capacity

	for (size_t i = 0; i < this->elementSize; i++)
	{
		tempArray[i] = this->array[i]; // copy the contents of the old array into the new array
	}

	delete[] array; // delete the old array

	this->array = tempArray; // set the array to the new array

	this->initialize(this->elementSize); // initialize the new array
}

// This function initializes the array with nullptrs to serve as placeholder values
// The parameter F (from) is used to determine where to start initializing the array
template <typename T>
void Dynamic<T>::initialize(unsigned F)
{
	for (size_t i = F; i < this->capacity; i++)
	{
		this->array[i] = nullptr;
	}
}

// This function returns the maximum capacity of the dynamic array.
template <typename T>
unsigned Dynamic<T>::maxCapacity()
{
	return this->capacity;
}
// Returns the number of elements in the array
template <typename T>
unsigned Dynamic<T>::size()
{

	return this->elementSize;
}

template <typename T>
void Dynamic<T>::push(const T element)
{
	// If the array is full, double the capacity
	if (this->elementSize >= this->capacity)
	{
		this->scaleUp();
	}
	// Insert the element at the end of the array
	this->array[this->elementSize++] = new T(element);
}

// This function deletes the element of the array in the index position and shifts the array's elements
// to the left to fill the gap. If ordered is true, the elements are shifted in order, if it is false,
// the last element is shifted to the index position.
template <typename T>
void Dynamic<T>::remove(const unsigned index, bool ordered)
{
	if (index < 0 || index >= this->elementSize)
		throw "Out of range!";

	if (ordered)
	{
		delete this->array[index];

		for (size_t i = 0; i < this->elementSize - 1; i++)
		{
			this->array[i] = this->array[i + 1];
		}

		this->array[this->elementSize] = nullptr;
		this->elementSize--;

	}
	else
	{
		delete this->array[index];

		this->array[index] = this->array[this->elementSize - 1];

		this->array[this->elementSize] = nullptr;
		this->elementSize--;
	}
}
#endif