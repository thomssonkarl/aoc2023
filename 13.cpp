#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

bool single_smudge_r(std::string row1, std::string row2) {
    size_t counter = 0;
    for (size_t i = 0; i < row1.size(); ++i) {
        if (row1[i] != row2[i]) ++counter;
    }
    return counter == 1;
}

bool single_smudge_c(const std::vector<std::string>& pattern, size_t col1, size_t col2) {
    size_t counter = 0;
    for (size_t i = 0; i < pattern.size(); ++i) {
        if(pattern[i][col1] != pattern[i][col2]) ++counter;
    }
    return counter == 1;
}

bool valid_reflection(const std::vector<std::string>& pattern, size_t start, bool vertical, bool part2) {

    if (vertical) {
        int up = part2 ? start-1 : start-2;
        int down = part2 ? start : start+1;
        int smudges = 0;

        while((up >= 0) && (down != pattern.size())) {
            if(pattern[up] != pattern[down]) {
                if (part2 && single_smudge_r(pattern[up], pattern[down])) {
                   smudges++; 
                } else {
                    return false; 
                }
            } 
            --up;
            ++down;
        } 
        return part2 ? smudges == 1 : true;

    } else {
        int left = part2 ? start-1 : start - 2;
        int right = part2 ? start : start + 1;
        int smudges = 0;

        while ((left >= 0) && (right != pattern[0].size())) {
            for (size_t r = 0; r < pattern.size(); ++r) {
                if(pattern[r][left] != pattern[r][right]) {
                    if(part2 && single_smudge_c(pattern, right, left)) {
                        smudges++;
                    } else {
                        return false;
                    }
                }
            }
            --left;
            ++right;
        }
        return part2 ? smudges == 1 : true;
    }

    std::cout << "You should not be here..." << std::endl;
    return false;
}


uint64_t solve2(const std::vector<std::vector<std::string>>& input) {

    uint64_t result = 0;
    bool part2 = true;
    
    for(const auto& pattern : input) {

        bool vertical = true;
        for (size_t row = 0; row < pattern.size(); ++row) {
            if (valid_reflection(pattern, row, true, part2)) {
                result += (100*row); 
                vertical = false;
                break;
            } 
        }

        if (vertical) {
            for (size_t col = 0; col < pattern[0].size(); ++col) {
                if (valid_reflection(pattern, col, false, part2)) {
                    result += col;
                    break;
                }
            }
        }
    } 
    return result;
}

uint64_t solve(const std::vector<std::vector<std::string>>& input, bool part2) {

    uint64_t result = 0;
    
    for(const auto& pattern : input) {

        size_t rlr = 0;
        size_t rlc = 0;
        bool vertical = true;
        for (size_t row = 0; row < pattern.size()-1; ++row) {
            if(pattern[row] == pattern[row+1]) {
                if (valid_reflection(pattern, row+1, true, part2)) {
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
                    if (valid_reflection(pattern, col+1, false, part2)) {
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

    uint64_t result = part2 ? solve2(input) : solve(input, part2);


    inputFile.close();

    std::cout << "Solution: " << result << std::endl;

    return 0;

}
