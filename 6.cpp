#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <numeric>
#include <functional>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <?part2>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the input file!" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<uint64_t> times;
    std::vector<uint64_t> distances;
    bool p2 = std::stoi(argv[2]) != 0;

    while (getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string category;
        ss >> category;
        uint64_t value;

        if (category == "Time:") {
            if (p2) {
                line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
                value = std::stoul(line.substr(line.find(":") + 1));
                times.push_back(value);
            } else {
                while (ss >> value) times.push_back(value);
            }
        } else if (category == "Distance:") {
            if (p2) {
                line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
                value = std::stoul(line.substr(line.find(":") + 1));
                distances.push_back(value);
            } else {
                while (ss >> value) distances.push_back(value);
            }
        }
    }

    size_t race = 0;
    std::vector<uint32_t> numbers;
    for (auto time : times) {
        uint64_t wins = 0;
        for (size_t i = 0; i < time; ++i) {
            uint64_t dist = i * (time - i);
            if (dist > distances[race]) ++wins;
        }
        numbers.push_back(wins);
        ++race;
    }

    if (!p2) {
        uint64_t product = std::accumulate(numbers.begin(), numbers.end(), 1, std::multiplies<int>());
        std::cout << "Product: " << product << std::endl;
    } else {
        std::cout << "Amount of ways: " << numbers[0] << std::endl;
    }

    inputFile.close();
    return 0;
}

