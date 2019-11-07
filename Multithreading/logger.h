#pragma once

#include <string>
#include <fstream>
#include <thread>

using std::string;
using std::ofstream;
using std::ios;

class logger
{
	string fileName;
	string data;

	ofstream writeFile;

	std::thread fileIOThread;

	logger();

public:

	logger(string fileOut);
	~logger();

	void accept(string value);
	void write();
	void write(string curData);

	void writeThread(string fileName, string data);

	void assertCorrectOrder();
	void clearFile();
};