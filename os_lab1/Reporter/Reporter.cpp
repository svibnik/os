#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "Employee.h"

bool cmp(const employee& a, const employee& b) {
    return a.num < b.num;
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 4) {
            std::cerr << "Usage: Reporter.exe input output rate" << std::endl;
            return 1;
        }

        double rate = std::atof(argv[3]);
        if (rate <= 0) {
            throw std::runtime_error("Rate must be positive");
        }

        std::ifstream in(argv[1], std::ios::binary);
        if (!in) {
            throw std::runtime_error("Can't open input file");
        }

        std::vector<employee> v;
        employee emp;

        while (in.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
            v.push_back(emp);
        }
        in.close();

        std::sort(v.begin(), v.end(), cmp);

        std::ofstream out(argv[2]);
        if (!out) {
            throw std::runtime_error("Can't create output file");
        }

        out << "Отчет по файлу \"" << argv[1] << "\"\n";
        out << "Номер, Имя, Часы, Зарплата\n";

        for (size_t i = 0; i < v.size(); i++) {
            out << v[i].num << ", " << v[i].name << ", "
                << v[i].hours << ", " << v[i].hours * rate << "\n";
        }

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}