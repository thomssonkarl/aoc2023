#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <numeric>
#include <functional>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;

    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the input file!" << std::endl;
        return 1;

    }

    std::string line;
    std::vector<int> times;
    std::vector<int> distances;

    while (getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string category;
        ss >> category;
        int value;
        if (category == "Time:") {
            while (ss >> value) times.push_back(value);
        } else if (category == "Distance:") {
            while (ss >> value) distances.push_back(value);
        }
    }
    
    size_t race = 0;
    std::vector<uint32_t> numbers;
    for (auto time : times) {
        uint32_t wins = 0; 
        for (size_t i = 0; i < time; ++i) {
            uint32_t dist = i*(time-i);
            if (dist > distances[race]) ++wins;
        }
        numbers.push_back(wins); 
        ++race;
    }

    int product = std::accumulate(numbers.begin(), numbers.end(), 1, std::multiplies<int>()); 
    std::cout << product << std::endl;
    inputFile.close();

    return 0;

}

