
#ifndef SERIALPORT_H
#define SERIALPORT_H

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

class SerialPort
{
private:
	HANDLE hCOM;
	bool connected;
	COMSTAT status;
	DWORD errors;
public:
	SerialPort(string);
	~SerialPort();

	int read(char *buffer, unsigned int buf_size);
	bool write(char *buffer, unsigned int buf_size);
	bool isConnected();
};

#endif // SERIALPORT_H