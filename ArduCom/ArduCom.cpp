#include "pch.h"
#include "SerialPort.h"
#include <iostream>
#include <string>
#include <thread>


using namespace std;

string portName = "COM4";
SerialPort *portCOM;

int main()
{
	portCOM = new SerialPort(portName);

	if (portCOM->isConnected())
	{
		// Start Command
		char sendString[] = { 's', '\r', '\n' };
		int len = sizeof(sendString) / sizeof(char);
		// Loop until we have a Answer
		bool answer = false;
		char incData[10]; // we await 1 character as Answer
		while (!answer)
		{
			bool sendSuccess = portCOM->write(&(sendString[0]), len);
			int answerLength = portCOM->read(incData, MAX_DATA_LENGTH);
			std::cout << answerLength << std::endl;
			if (answerLength > 0) { answer = true; }
		}
		std::cout << "done" << endl;
		std::this_thread::sleep_for(500ms);
	}

}
