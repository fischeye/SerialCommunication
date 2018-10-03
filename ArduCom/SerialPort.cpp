#include "pch.h"
#include "SerialPort.h"

SerialPort::SerialPort(string portName)
{
	connected = false;
	// Initialize COM Port Communication Handler
	hCOM = CreateFileA(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hCOM == INVALID_HANDLE_VALUE) {
		std::cout << "ERROR: Connecting COM Port!" << std::endl;
		CloseHandle(hCOM);
	}
	else
	{
		// Setup COM Connection Parameters
		DCB serialParas = { 0 };
		serialParas.BaudRate = CBR_9600;
		serialParas.ByteSize = 8;
		serialParas.Parity = NOPARITY;
		serialParas.StopBits = ONESTOPBIT;

		// Set and Check the Parameters
		bool fSuccess = SetCommState(hCOM, &serialParas);
		if (!fSuccess)
		{
			std::cout << "ERROR: Could not setup Parameters" << std::endl;
		}
		else { connected = true; }
	}
}

SerialPort::~SerialPort()
{
	if (connected) {
		connected = false;
		CloseHandle(hCOM);
	}
}

int SerialPort::read(char *buffer, unsigned int buf_size)
{
	DWORD bytesRead;
	unsigned int toRead = 0;
	ClearCommError(hCOM, &errors, &status);
	if (status.cbInQue > 0) {
		if (status.cbInQue > buf_size) { toRead = buf_size; } else toRead = status.cbInQue;
	}
	memset(buffer, 0, buf_size);
	if (ReadFile(hCOM, buffer, toRead, &bytesRead, NULL)) return bytesRead;
	return 0;
}

bool SerialPort::write(char *buffer, unsigned int buf_size)
{
	DWORD bytesSend;

	if (!WriteFile(hCOM, (void*)buffer, buf_size, &bytesSend, 0)) {
		ClearCommError(hCOM, &errors, &status);
		return false;
	}
	else return true;
}

bool SerialPort::isConnected()
{
	if (!ClearCommError(hCOM, &errors, &status)) connected = false;
	return connected;
}