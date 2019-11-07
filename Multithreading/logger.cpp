#include "logger.h"

#include <cassert>
#include <thread>
#include <mutex>

using std::ifstream;

logger::logger()
{
	fileName = "boop.txt";
}

logger::logger(string fileOut)
{
	fileName = fileOut;
}

void logger::accept(string value)
{
	data = value;
}

void logger::write()
{
	std::thread newThread(&logger::writeThread, this, fileName, data);
	newThread.join();
}

void logger::write(string curData)
{
	threadCountInside++;
	std::thread newThread(&logger::writeThread, this, fileName, curData);	
	newThread.detach();
}

void logger::writeThread(string fileName, string data)
{
	static std::mutex myMutex;
	static int lastData;
	int currentData = std::stoi(data);

	assert(currentData > lastData);

	std::lock_guard<std::mutex> guard(myMutex);

	ofstream myFile;
	myFile.open(fileName, ios::app);

	assert(myFile.is_open());

	myFile << data << "\n";
	myFile.close();

	threadCountOutside++;
	lastData = currentData;
}

bool logger::canExit()
{
	return threadCountInside == threadCountOutside;
}

void logger::assertCorrectOrder()
{
	ifstream myFile;
	myFile.open(fileName, ios::out);

	assert(myFile.is_open());

	string line;
	int currentLine, lastLine;
	currentLine = lastLine = 0;

	while (std::getline(myFile, line))
	{
		currentLine = std::stoi(line);
		assert(currentLine > lastLine);
		lastLine = currentLine;
	}
	myFile.close();
}
