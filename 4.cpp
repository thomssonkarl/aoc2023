#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <cmath>
#include <map>
#include <sstream>
#include <set>

int solve(const std::vector<std::string>& input, uint16_t part) {
    uint32_t result{}; 
    std::vector<int> matches_vec;

    for (const auto& str : input) {
        uint16_t colon = str.find_first_of(':');
        std::istringstream iss(str.substr(colon + 2));
        std::set<int> winning_nums;
        std::set<int> my_nums;
        bool winning = true;

        while (!iss.eof()) {
            std::string token;
            iss >> token;
            if (token.empty()) {
                continue;
            }
            if (token == "|") {
                winning = false;
                continue;
            }
            if (winning) {
                winning_nums.insert(std::stoi(token));
            } else {
                my_nums.insert(std::stoi(token));
            }
        }

        std::set<int> inter;
        std::set_intersection(winning_nums.begin(), winning_nums.end(),
                              my_nums.begin(), my_nums.end(),
                              std::inserter(inter, inter.begin()));
        
        uint32_t matches = inter.size();
        if (matches > 0) {
            result += std::pow(2, matches-1);
        }
        matches_vec.push_back(matches);
    }

    std::vector<size_t> match_c(matches_vec.size(), 1);

    for (size_t i = 0; i < matches_vec.size(); ++i) {
        for (size_t j = 0; j < matches_vec[i]; ++j) {
            match_c[i+j+1] += match_c[i];
        }
    }

    if (part == 2) {
        return std::accumulate(match_c.begin(), match_c.end(), 0);
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

    std::vector<std::string> input;
    std::string line;
    while (getline(inputFile, line)) {
        input.push_back(line);
    }

    inputFile.close();

    int result = solve(input, 1);
    int result2 = solve(input, 2);

    std::cout << "Solution: " << result << std::endl;
    std::cout << "Solution 2: " << result2 << std::endl;

    return 0;

}

