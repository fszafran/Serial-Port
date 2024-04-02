#include <iostream>
#include <windows.h>

HANDLE hSerial;

void port_setup(std::string portName, int baudRate, int byteSize, int stopBits, char parity) {
    std::wstring widePortName = std::wstring(portName.begin(), portName.end());
    hSerial = CreateFileW(widePortName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            std::cerr << "ERROR: Serial port not found.\n";
        }
        std::cerr << "ERROR: Unable to open serial port.\n";
    }
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if(!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "ERROR: Unable to get current serial parameters.\n";
    }
    dcbSerialParams.BaudRate = baudRate;
    dcbSerialParams.ByteSize = byteSize;
    dcbSerialParams.StopBits = stopBits;
    dcbSerialParams.Parity = parity;
    if(!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "ERROR: Unable to set serial parameters.\n";
    }
    if(!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "ERROR: Unable to set serial port parameters.\n";
    }
    COMMTIMEOUTS timeouts = {0};
timeouts.ReadIntervalTimeout = 50;
timeouts.ReadTotalTimeoutConstant = 50;
timeouts.ReadTotalTimeoutMultiplier = 10;
timeouts.WriteTotalTimeoutConstant = 50;
timeouts.WriteTotalTimeoutMultiplier = 10;

if(!SetCommTimeouts(hSerial, &timeouts)) {
    std::cerr << "ERROR: Unable to set serial port timeouts.\n";
}}

std::string read_data(HANDLE hSerial) {
    DWORD dwBytesRead = 0;
    char data[256] = {0};
    if(!ReadFile(hSerial, data, 255, &dwBytesRead, NULL)) {
        std::cerr << "ERROR: Unable to read from serial port.\n";
    } else if (dwBytesRead > 0) {
        std::cerr << "INFO: Successfully read from serial port.\n";
    }
    return std::string(data);
}

bool write_string(HANDLE hSerial, const std::string& message) {
    DWORD dwBytesWritten = 0;

    if(!WriteFile(hSerial, message.c_str(), message.size(), &dwBytesWritten, NULL)) {
        std::cerr << "ERROR: Unable to write to serial port.\n";
        return false;
    } else {
        std::cerr << "INFO: Successfully wrote to serial port.\n";
        return true;
    }
}
bool write_data(HANDLE hSerial, const std::string& data) {
    DWORD dwBytesWritten = 0;

    if(!WriteFile(hSerial, data.c_str(), data.size(), &dwBytesWritten, NULL)) {
        std::cerr << "ERROR: Unable to write to serial port.\n";
        return false;
    } else {
        std::cerr << "INFO: Successfully wrote to serial port.\n";
        return true;
    }
}