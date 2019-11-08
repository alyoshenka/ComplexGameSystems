#pragma once

template<typename T>
class aCircularQueue
{
private:
	const static size_t defaultCapacity = 10;

	T *arr;
	size_t capacity;
	size_t size;

	size_t frontIndex;

	int getFront();
	int getBack();

public:

	aCircularQueue();
	aCircularQueue(size_t capacity);
	~aCircularQueue();

	T& front();
	T& back();

	bool push(const T& val);
	bool pop();

	bool isEmpty() const;
	size_t getSize() const;
};

template<typename T>
inline int aCircularQueue<T>::getFront()
{
	return frontIndex;
}

template<typename T>
inline int aCircularQueue<T>::getBack()
{
	if (frontIndex + size <= 0) { return 0; }

	return capacity % (frontIndex + size);
}

template<typename T>
inline aCircularQueue<T>::aCircularQueue() : aCircularQueue(defaultCapacity) { }

template<typename T>
inline aCircularQueue<T>::aCircularQueue(size_t setCapacity)
{
	capacity = setCapacity;
	arr = new T[setCapacity];

	size = 0;
	frontIndex = 0;
}

template<typename T>
inline aCircularQueue<T>::~aCircularQueue()
{
	delete[] arr;
}

template<typename T>
inline T & aCircularQueue<T>::front()
{
	return arr[frontIndex];
}

template<typename T>
inline T & aCircularQueue<T>::back()
{
	return arr[getBack()];
}

template<typename T>
inline bool aCircularQueue<T>::push(const T & val)
{
	if (size >= capacity) { return false; }

	arr[getBack()] = val;
	size++;

	T i = arr[frontIndex + size];

	return true;
}

template<typename T>
inline bool aCircularQueue<T>::pop()
{
	if (getSize <= 0) { return false; }

	front++;
	if (front > capacity) { front = 0; }
	size--;

	return true;
}

template<typename T>
inline bool aCircularQueue<T>::isEmpty() const
{
	return size == 0;
}

template<typename T>
inline size_t aCircularQueue<T>::getSize() const
{
	return size;
}
