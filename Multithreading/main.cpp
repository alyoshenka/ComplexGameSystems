#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cassert>

#include "logger.h"
#include "aCircularQueue.h"


void runLogger()
{
	logger log("output.txt");
	// log.clearFile();
	log.accept("-1");
	log.write();
	for (int i = 0; i < 5000; i++) { log.writeReusable(std::to_string(i + 1)); }

	// log.assertCorrectOrder();
}

void runCircleQueue()
{
	aCircularQueue<int> a;

	assert(a.getSize() == 0);
	assert(a.isEmpty());

	int count = 5;
	for (int i = 1; i <= count; i++) { a.push(i); }

	std::cout << std::endl;

	assert(a.getSize() == count);
	assert(!a.isEmpty());
	assert(a.front() == 1);
	assert(a.back() == 5);	

	a.pop();
	assert(a.getSize() == count - 1);
	assert(!a.isEmpty());
	assert(a.front() == 2);
	assert(a.back() == 5);

	for (int i = 0; i < 4; i++) { a.pop(); }

	std::cout << std::endl;

	assert(a.isEmpty());

	for (int i = 1; i <= 8; i++) 
	{ 
		a.push(i); 
	}

	std::cout << std::endl;

	// try to overflow
	for (int i = 1; i <= 5; i++)
	{
		if (a.push(i + 8)) { std::cout << "push successful" << std::endl; }
		else { std::cout << "push unsuccessful" << std::endl; }
	}

	std::cout << std::endl;
}

void runCircleQueueWithThreads()
{
	aCircularQueue<int> a;

	for (int i = 1; i <= 10; i++) { a.pushUsingThread(i); }

}

int main()
{
	// runLogger();
	// runCircleQueue();
	runCircleQueueWithThreads();

	char n;
	std::cin >> n;
	return 0; 
}

