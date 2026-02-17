#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>
#include "Employee.h"

bool fileExists(const char* filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 3) {
            std::cerr << "Usage: Creator.exe file count" << std::endl;
            return 1;
        }

        int n = std::atoi(argv[2]);
        if (n <= 0) {
            throw std::runtime_error("Count must be positive");
        }

        if (fileExists(argv[1])) {
            std::cout << "File exists. Overwrite? (y/n): ";
            char c;
            std::cin >> c;
            if (c != 'y' && c != 'Y') return 0;
        }

        std::ofstream out(argv[1], std::ios::binary);
        if (!out) {
            throw std::runtime_error("Can't create file");
        }

        employee emp;
        for (int i = 0; i < n; i++) {
            std::cout << "Enter num name hours: ";
            std::cin >> emp.num >> emp.name >> emp.hours;
            out.write(reinterpret_cast<char*>(&emp), sizeof(emp));
        }

        out.close();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}