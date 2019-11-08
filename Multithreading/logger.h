#pragma once

#include <string>
#include <fstream>
#include <thread>
#include <queue>

using std::string;
using std::ofstream;
using std::ios;

class logger
{
	string fileName;
	string data;

	ofstream writeFile;

	std::thread fileIOThread;
	std::queue<string> dataToWrite;

	logger();

public:

	logger(string fileOut);
	~logger();

	void accept(string value);
	void write();

	void write(string curData);
	void writeReusable(string curData);

	void writeThread(string fileName, string data);
	void writeThreadReusable(string fileName);

	void assertCorrectOrder();
	void clearFile();
};