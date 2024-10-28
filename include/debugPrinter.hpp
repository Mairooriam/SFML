#ifndef DEBUG_PRINTER_HPP
#define DEBUG_PRINTER_HPP

#include <iostream>
#include <string>

class DebugPrinter {
public:
    static void setDebugMode(bool mode) {
        debugMode = mode;
    }

    static void print(const std::string& message) {
        if (debugMode) {
            std::cout << "[DEBUG]: " << message << std::endl;
        }
    }

    static void printError(const std::string& message) {
        if (debugMode) {
            std::cerr << "[ERROR]: " << message << std::endl;
        }
    }

    static void printWarning(const std::string& message) {
        if (debugMode) {
            std::cout << "[WARNING]: " << message << std::endl;
        }
    }

private:
    static bool debugMode;
};

// Initialize the static member
bool DebugPrinter::debugMode = true;

#endif // DEBUG_PRINTER_HPP