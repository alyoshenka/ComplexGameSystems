#pragma once

#define DebugValues true

template<typename T>
class aCircularQueue
{
private:
	const static size_t defaultCapacity = 10;
	const static size_t multiplier = 2;

	T *arr;
	size_t capacity;
	size_t size;

	size_t frontIndex;

	std::thread pushThread;
	std::thread popThread;

	size_t getFrontIndex() const;
	size_t getBackIndex() const;

public:

	aCircularQueue();
	aCircularQueue(size_t capacity);
	~aCircularQueue();

	T& front() const;
	T& back() const;

	bool push(const T& val);
	bool pop();

	void pushUsingThread(const T& val);
	void popUsingThread();

	bool isEmpty() const;
	size_t getSize() const;

	bool resize(size_t newSize);
};

template<typename T>
inline size_t aCircularQueue<T>::getFrontIndex() const
{
	return frontIndex;
}

template<typename T>
inline size_t aCircularQueue<T>::getBackIndex() const
{
	size_t ret = frontIndex + size - 1;

	if (ret < 0) { return 0; }
	if (ret >= capacity) { ret = ret % capacity; }

	return ret;
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

	// popThread = std::thread(&aCircularQueue::popUsingThread, this);
}

template<typename T>
inline aCircularQueue<T>::~aCircularQueue()
{
	delete[] arr;
}

template<typename T>
inline T & aCircularQueue<T>::front() const
{
	return arr[getFrontIndex()];
}

template<typename T>
inline T & aCircularQueue<T>::back() const
{
	return arr[getBackIndex()];
}

template<typename T>
inline bool aCircularQueue<T>::push(const T & val)
{
	if (size >= capacity) { return false; }

	size++;
	arr[getBackIndex()] = val;

	if (DebugValues) { std::cout << "pushed value " << val << " to index " << getBackIndex() << std::endl; }

	return true;
}

template<typename T>
inline bool aCircularQueue<T>::pop()
{
	if (size <= 0) { return false; }

	if (DebugValues) { std::cout << "popped value " << arr[getFrontIndex()] << " from index " << getFrontIndex() << std::endl; }

	frontIndex++;
	if (frontIndex >= capacity) { frontIndex = capacity % frontIndex; }
	size--;

	return true;
}

template<typename T>
inline void aCircularQueue<T>::pushUsingThread(const T & val)
{
	static std::mutex myMutex;
	std::lock_guard<std::mutex> guard(myMutex);

	pushThread = std::thread(&aCircularQueue::push, this, val);

	pushThread.join(); // this defeats the purpose
}

template<typename T>
inline void aCircularQueue<T>::popUsingThread()
{
	static std::mutex myMutex;
	std::lock_guard<std::mutex> guard(myMutex);

	popThread = std::thread(&aCircularQueue::pop, this);

	popThread.join();
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

template<typename T>
inline bool aCircularQueue<T>::resize(size_t newCapacity) // test
{
	if (newCapacity <= size) { return false; }

	size_t sizeHolder = size;

	T *newArr = new T[newCapacity];
	for (int i = 0; !isEmpty(); i++)
	{
		newArr[i] = front();
		pop();
	}

	delete[] arr;
	arr = newArr;
	size = sizeHolder;
	frontIndex = 0;
	capacity = newCapacity; 

	return true;
}
