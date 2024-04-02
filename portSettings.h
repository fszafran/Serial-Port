#include <windows.h>
#include <iostream>
struct PortSettings {
    std::string port = "COM6";
    int baudRate = 9600; // default baud rate
    int byteSize = 8; // default byte size
    int stopBits = ONESTOPBIT; // default stop bits
    char parity = NOPARITY; // default parity
};

PortSettings getPortSettings(int argc, char* argv[]) {
    PortSettings settings;
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-port") {
            if (i + 1 < argc) {
                settings.port = argv[i + 1];
            }
            else {
                std::cerr << "No port specified\n";
            }
        }
        else if (std::string(argv[i]) == "-baudrate") {
            if (i + 1 < argc) {
                settings.baudRate = std::stoi(argv[i + 1]);
            }
            else {
                std::cerr << "No baud rate specified\n";
            }
        }
        else if (std::string(argv[i]) == "-bytesize") {
            if (i + 1 < argc) {
                settings.byteSize = std::stoi(argv[i + 1]);
            }
            else {
                std::cerr << "No byte size specified\n";
            }
        }
        else if (std::string(argv[i]) == "-stopbits") {
            if (i + 1 < argc) {
                settings.stopBits = std::stoi(argv[i + 1]);
            }
            else {
                std::cerr << "No stop bits specified\n";
            }
        }
        else if (std::string(argv[i]) == "-parity") {
            if (i + 1 < argc) {
                settings.parity = argv[i + 1][0];
            }
            else {
                std::cerr << "No parity specified\n";
            }
        }
    }
    return settings;
}