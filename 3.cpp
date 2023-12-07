#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <cmath>
#include <map>
#include <set>
#include <sstream>
#include <cstdlib>

const size_t dim = 140;

using schematic_t = std::array<std::array<char, dim>, dim>;

int solve2(const std::vector<std::string>& input) {
    uint32_t result{}; 

    for (const auto& str : input) {

    }

    return result;
}

bool is_symbol(char c) { 
    return !std::isdigit(c) && c != '.';
}

bool is_numeric_string(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return !str.empty();
}

int get_part_number(schematic_t& schematic, size_t row, size_t col) {
    size_t start = col;
    size_t end = col;
    std::string part_str;

    if (!std::isdigit(schematic[row][col])) {
        return -1;
    }

    while(start > 0 && std::isdigit(schematic[row][start-1])) {
        start--;
    }
        
    while(end < dim && std::isdigit(schematic[row][end])) {
        end++;
    }

    std::string row_as_string(schematic[row].begin(), schematic[row].end());
    part_str = row_as_string.substr(start, end-start);
    if (is_numeric_string(part_str)) {
        return std::stoi(part_str);
    } else {
        return -1;
    }
}

void check_neighbors(schematic_t& schematic, 
        size_t row, 
        size_t col,
        std::vector<int>& valid_parts) {

    const std::vector<std::pair<int, int>> neighbor_offsets = {
        {0, 1}, {0, -1}, {-1, 0}, {1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    std::set<int> part_set;

    for (const auto& offset : neighbor_offsets) {
        size_t neighbor_row = row + offset.first;
        size_t neighbor_col = col + offset.second;
        if (neighbor_row < dim && neighbor_col < dim) {
            int part_number = get_part_number(schematic, neighbor_row, neighbor_col);
            if (part_number != -1) {
                part_set.insert(part_number);
            }
        }
    }
    std::copy(part_set.begin(), part_set.end(), std::back_inserter(valid_parts));
        
}

int solve(const std::vector<std::string>& input) {
    uint32_t result{}; 
    schematic_t schematic;
    std::vector<int> valid_parts;

    for (size_t row = 0; row < input.size(); ++row) {
        const auto& str = input[row];
        for (size_t col = 0; col < dim; ++col) {
            schematic[row][col] = str[col];
        }
    }

    for (size_t row = 0; row < dim; ++row) {
        for (size_t col = 0; col < dim; ++col) {
            if(is_symbol(schematic[row][col])) {
                check_neighbors(schematic, row, col, valid_parts);
            }
        }
    }

    return std::accumulate(valid_parts.begin(), valid_parts.end(), 0);
}

int main() {
    std::ifstream inputFile("input3.txt");
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

    int result = solve(input);
    int result2 = solve2(input);

    std::cout << "Solution: " << result << std::endl;
    std::cout << "Solution 2: " << result2 << std::endl;

    return 0;

}


