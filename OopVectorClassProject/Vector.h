#pragma once

template <typename T>
class Vector;


template <typename T>
class VectorIterator
{
	Vector<T>* container;
	int indexCurrent{};
public:
	VectorIterator(Vector<T>* container) 
		: container{ container }{}

	void Set();
	void Next();
	bool EndOf();
	T Current();
};

template <typename T>
class Vector
{
	size_t size{};
	size_t capacity{ 4 };
	T* array{ new T[capacity] };

	void copy();
public:
	Vector() = default;
	Vector(size_t size);
	Vector(const Vector<T>& other);

	~Vector();

	Vector<T> operator=(const Vector<T> other);

	T& operator[](size_t index);
	T& At(size_t index);

	bool Emplty();
	size_t Size();
	size_t Capacity();

	void Srink();

	void Clear();
	void Insert(int index, T value);
	void PushBack(T value);
	T PopBack();
	void Remove(T value);
	T RemoveAt(size_t index);

	VectorIterator<T> GetIterator();
};

template<typename T>
inline void Vector<T>::copy()
{
	T* arrayNew = new T[capacity];
	for (int i{}; i < size; i++)
		arrayNew[i] = array[i];

	delete[] array;
	array = arrayNew;
}

template<typename T>
inline Vector<T>::Vector(size_t size)
	: size{ size },
	capacity{ size + size / 2 },
	array{ new T[capacity]{} } {}

template<typename T>
inline Vector<T>::Vector(const Vector<T>& other)
	: size{ other.size },
	capacity{ size + size / 2 },
	array{ new T[capacity] }
{
	for (int i{}; i < size; i++)
		array[i] = other.array[i];
}

template<typename T>
inline Vector<T>::~Vector()
{
	if (array)
		delete[] array;
}

template<typename T>
inline Vector<T> Vector<T>::operator=(const Vector<T> other)
{
	if (array)
		delete[] array;
	this->size = other.size;
	this->capacity = this->size + this->size / 2;
	this->array = new T[this->capacity];

	for (int i{}; i < size; i++)
		array[i] = other.array[i];

	return *this;
}

template<typename T>
inline T& Vector<T>::operator[](size_t index)
{
	return array[index];
}

template<typename T>
inline T& Vector<T>::At(size_t index)
{
	//static_assert(index >= 0 && index < size, "out of range");
	return array[index];
}

template<typename T>
inline bool Vector<T>::Emplty()
{
	return size == 0;
}

template<typename T>
inline size_t Vector<T>::Size()
{
	return size;
}

template<typename T>
inline size_t Vector<T>::Capacity()
{
	return capacity;
}

template<typename T>
inline void Vector<T>::Srink()
{
	if (size < capacity)
	{
		capacity = size;
		copy();
	}
}

template<typename T>
inline void Vector<T>::Clear()
{
	if (array)
		delete[] array;
	size = 0;
	capacity = 4;
	array = new T[capacity];
}

template<typename T>
inline void Vector<T>::Insert(int index, T value)
{
	static_assert(index >= 0 && index < size, "out of range");

	if (size >= capacity)
	{
		capacity = size + size / 2;
		copy();
	}

	for (int i{ size - 1 }; i >= index; i--)
		array[i + 1] = array[i];
	
	array[index] = value;
	size++;
}

template<typename T>
inline void Vector<T>::PushBack(T value)
{
	if (size >= capacity)
	{
		capacity = size + size / 2;
		copy();
	}

	array[size++] = value;
}

template<typename T>
inline T Vector<T>::PopBack()
{
	if (capacity > size + size / 2)
	{
		capacity = size + size / 2;
		copy();
	}
	return array[--size];
}

template<typename T>
inline void Vector<T>::Remove(T value)
{
	int index{};
	for (; index < size; index++)
		if (array[index] == value);
	if(index < size)
		RemoveAt(index);
}

template<typename T>
inline T Vector<T>::RemoveAt(size_t index)
{
	static_assert(index >= 0 && index < size, "out of range");
	if (capacity > size + size / 2)
	{
		capacity = size + size / 2;
		copy();
	}

	T value = array[index];
	for (int i{ index }; i < size - 1; i++)
		array[i] = array[i + 1];
	size--;
	return value;
}

template<typename T>
inline VectorIterator<T> Vector<T>::GetIterator()
{
	return VectorIterator<T>(this);
}




template<typename T>
inline void VectorIterator<T>::Set()
{
	indexCurrent = 0;
}

template<typename T>
inline void VectorIterator<T>::Next()
{
	if (indexCurrent < container->Size())
		indexCurrent++;
}

template<typename T>
inline bool VectorIterator<T>::EndOf()
{
	return indexCurrent >= container->Size();
}

template<typename T>
inline T VectorIterator<T>::Current()
{
	return container->At(indexCurrent);
}
