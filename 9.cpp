#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <cmath>
#include <map>
#include <sstream>

int solve(const std::vector<std::vector<int>>& input) {
    int result{}; 

    auto is_zero = [](int e) { return e == 0; };

    for (auto &line : input) {
        std::vector<int> next_line = line;
        std::vector<std::vector<int>> seqs = {next_line};
        bool az = std::all_of(next_line.begin(), next_line.end(), is_zero);     
        while(!az) {
            std::vector<int> diffrences;
            for (size_t i = next_line.size()-1; i > 0; --i) {
                int diff = next_line[i] - next_line[i-1]; 
                diffrences.insert(diffrences.begin(), diff); 
            }
            seqs.insert(seqs.begin(), diffrences);
            next_line = diffrences;
            az = std::all_of(next_line.begin(), next_line.end(), is_zero);     
        }
        for (size_t i = 0; i < seqs.size() -1; ++i) {
            int a = seqs[i].back();
            int b = seqs[i+1].back();
            int next_n = a + b;
            seqs[i+1].push_back(next_n);
        }
        result += seqs.back().back();
    }

    return result;
}

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

    std::vector<std::vector<int>> input;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<int> numbers;
        int num;
        while (iss >> num) numbers.push_back(num);
        input.push_back(numbers);
    }


    inputFile.close();

    int result = solve(input);

    std::cout << "Solution: " << result << std::endl;

    return 0;

}

