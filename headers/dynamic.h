#ifndef DARR_H
#define DARR_H

// Dynamic generic array
// cant make cpp file because it is generic
// This class is a dynamic array that can be resized and expanded as needed.

// A fun custom simplified implementation of a "std::vector<> class" i.e. (resizable dynamic array) made specificity for this project. 

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
	Dynamic(unsigned size = 5); //creates a Dynamic object with an initial size (default size is 5).
	Dynamic(const Dynamic &object); //creates a new Dynamic object by copying the contents of another Dynamic object.
	~Dynamic(); // releases the memory allocated for the array and its elements.

	T &operator[](const unsigned index); // Overloaded [] operator for accessing elements of the array by index.
	void operator=(const Dynamic &object); // Overloaded assignment operator for assigning the contents of one Dynamic object to another.

	unsigned maxCapacity(); //  Returns the maximum capacity of the dynamic array.
	unsigned size(); // Returns the number of elements in the array.
	void push(const T element); // Adds an element to the end of the array, dynamically increasing the capacity if necessary.
	void remove(const unsigned index, bool ordered = false); // Removes the element at the specified index from the array, optionally maintaining the order of the remaining elements.

};

// Dynamic<T>::pop()
// {
// 	if (this->elementSize == 0)
// 		throw "Array is empty!";

// 	T element = *this->array[this->elementSize - 1];
// 	this->remove(this->elementSize - 1);

// 	return element;
// }

// Dynamic<T>::clear()
// {
// 	for (size_t i = 0; i < this->elementSize; i++)
// 	{
// 		delete this->array[i];
// 	}
// 	this->elementSize = 0;
// }



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
// Doubles the capacity of the array when it becomes full.
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

//  Initializes the array with nullptr values, starting from the specified index F.
//  The parameter F (from) is used to determine where to start initializing the array
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