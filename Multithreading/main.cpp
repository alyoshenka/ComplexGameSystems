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
	for (int i = 0; i < 5000; i++)
	{
		log.writeReusable(std::to_string(i + 1));
	}

	// log.assertCorrectOrder();
}

void runCircleQueue()
{
	aCircularQueue<int> a;

	assert(a.getSize() == 0);
	assert(a.isEmpty());

	int count = 5;
	for (int i = 1; i <= count; i++) { a.push(i); }

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

	assert(a.isEmpty());

	for (int i = 1; i <= 8; i++) 
	{ 
		std::cout << i << std::endl;
		a.push(i); 
	}
}

int main()
{
	// runLogger();
	runCircleQueue();

	return 0; 
}

