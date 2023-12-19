#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

bool valid_reflection(const std::vector<std::string>& pattern, size_t start, bool vertical) {

    if (vertical) {

        int up = start-2;
        int down = start+1;

        while((up >= 0) && (down != pattern.size())) {
            if(pattern[up] != pattern[down]) return false; 
            --up;
            ++down;
        } 

        return true;

    } else {

        int left = start - 2;
        int right = start + 1;

        while ((left >= 0) && (right != pattern[0].size())) {
            for (size_t r = 0; r < pattern.size(); ++r) {
                if(pattern[r][left] != pattern[r][right]) return false;
            }
            --left;
            ++right;
        }

        return true;
    }

    std::cout << "You should not be here..." << std::endl;
    return false;
}

uint64_t solve(const std::vector<std::vector<std::string>>& input) {

    uint64_t result = 0;
    
    for(const auto& pattern : input) {
        size_t rlr = 0;
        size_t rlc = 0;
        bool vertical = true;
        for (size_t row = 0; row < pattern.size()-1; ++row) {
            if(pattern[row] == pattern[row+1]) {
                if (valid_reflection(pattern, row+1, true)) {
                    rlr = row + 1; 
                    vertical = false;
                    break;
                } 
            }
        }
        if (vertical) {
            bool found = false;
            for (size_t col = 0; col < pattern[0].size()-1; ++col) {
                for (size_t row = 0; row < pattern.size(); ++row) {
                    if(pattern[row][col] != pattern[row][col+1]) break;
                    if (row == pattern.size()-1) found = true;      
                }
                if (found) {
                    if (valid_reflection(pattern, col+1, false)) {
                        rlc = col + 1;
                        break;
                    } else {
                        found = false;
                    }
                }
            }
        }
        result += (rlr*100) + rlc;
    } 
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> " << "<?part2>" << std::endl;
        return 1;

    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the input file!" << std::endl;
        return 1;

    }
    bool part2 = std::stoi(argv[2]);
    std::string line;
    size_t i = 0;
    std::vector<std::vector<std::string>> input = {{}};
    while (getline(inputFile, line)) {
        if (line.empty()) {
            ++i;
            std::vector<std::string> pattern = {};
            input.push_back(pattern);
            continue;
        }
        input[i].push_back(line); 
    }

    uint64_t result = solve(input);

    inputFile.close();

    std::cout << "Solution: " << result << std::endl;

    return 0;

}

