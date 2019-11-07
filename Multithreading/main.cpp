#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#include "logger.h"

void print(int a)
{
	static std::mutex consoleLock; // same instance used between multiple calls
	
	consoleLock.lock();

	std::cout << "hello thread: " << a << std::endl;

	consoleLock.unlock();
}

int main()
{
	/*
	std::vector<std::thread> threads;
	for(int i = 0; i < 100; i++)
	{
		threads.emplace_back(print, i + 1); // variatic function
	}
	
	for (auto& t : threads) { t.join(); }
	*/

	logger log("output.txt");
	// log.clearFile();
	log.accept("-1");
	log.write();
	for (int i = 0; i < 5000; i++)
	{
		log.write(std::to_string(i + 1));
	}

	log.assertCorrectOrder();

	return 0;
}