#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Employee.h"

int main() {
    try {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);

        std::string binFile, repFile;
        int count;
        double rate;

        std::cout << "Binary file name: ";
        std::cin >> binFile;
        std::cout << "Number of records: ";
        std::cin >> count;

        if (count <= 0) {
            throw std::runtime_error("Count must be positive");
        }

        std::string cmd = "Creator.exe " + binFile + " " + std::to_string(count);
        std::cout << "Running: " << cmd << std::endl;

        STARTUPINFOA si = { sizeof(si) };
        PROCESS_INFORMATION pi;

        if (!CreateProcessA(NULL, (LPSTR)cmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            DWORD err = GetLastError();
            std::cerr << "Error: " << err << std::endl;
            return 1;
        }

        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        std::cout << "\nFile contents:\n";
        std::ifstream f(binFile, std::ios::binary);
        if (!f) {
            std::cout << "File not found\n";
        }
        else {
            employee emp;
            while (f.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
                std::cout << emp.num << " " << emp.name << " " << emp.hours << std::endl;
            }
            f.close();
        }

        std::cout << "\nReport file: ";
        std::cin >> repFile;
        std::cout << "Hourly rate: ";
        std::cin >> rate;

        if (rate <= 0) {
            throw std::runtime_error("Rate must be positive");
        }

        cmd = "Reporter.exe " + binFile + " " + repFile + " " + std::to_string(rate);
        std::cout << "Running: " << cmd << std::endl;

        CreateProcessA(NULL, (LPSTR)cmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        std::cout << "\nReport:\n";
        std::ifstream r(repFile);
        if (r) {
            std::string line;
            while (std::getline(r, line)) std::cout << line << std::endl;
        }

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}