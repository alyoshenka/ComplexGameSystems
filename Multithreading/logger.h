#pragma once

#include <string>
#include <fstream>

using std::string;
using std::ofstream;
using std::ios;

class logger
{
	string fileName;
	string data;

	int threadCountInside;
	int threadCountOutside;

	logger();

public:

	logger(string fileOut);

	void accept(string value);
	void write();
	void write(string curData);

	void writeThread(string fileName, string data);

	bool canExit();

	void assertCorrectOrder();
};



