#include "logger.h"

#include <cassert>
#include <mutex>

#include <iostream>

using std::ifstream;

logger::logger()
{
	fileName = "boop.txt";
	writeFile.open(fileName, ios::app);
}

logger::~logger()
{
	writeFile.close();
}

logger::logger(string fileOut)
{
	fileName = fileOut;
	writeFile.open(fileName, ios::app);
}

void logger::accept(string value)
{
	data = value;
}

void logger::write()
{
	write(data);
}

void logger::write(string curData)
{
	std::thread fileIOThread(&logger::writeThread, this, fileName, curData);
	fileIOThread.join(); // maintain order
}

void logger::writeThread(string fileName, string data)
{
	static std::mutex myMutex;

	std::lock_guard<std::mutex> guard(myMutex);

	assert(writeFile.is_open());

	writeFile << data << "\n";
}

void logger::assertCorrectOrder()
{
	ifstream myFile;
	myFile.open(fileName, ios::out);

	assert(myFile.is_open());

	string line;
	int currentLine, lastLine;
	currentLine = lastLine = -2;

	while (std::getline(myFile, line))
	{
		currentLine = std::stoi(line);
		assert(currentLine > lastLine);
		lastLine = currentLine;
	}
	myFile.close();	
}

void logger::clearFile()
{
	assert(remove(fileName.c_str()) == 0);
}
