#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

size_t count_smudge_r(std::string row1, std::string row2) {
    size_t counter = 0;
    for (size_t i = 0; i < row1.size(); ++i) {
        if (row1[i] != row2[i]) ++counter;
    }
    return counter;
}

size_t count_smudge_c(const std::vector<std::string>& pattern, size_t col1, size_t col2) {
    size_t counter = 0;
    for (size_t i = 0; i < pattern.size(); ++i) {
        if(pattern[i][col1] != pattern[i][col2]) ++counter;
    }
    return counter;
}

bool valid_reflection(const std::vector<std::string>& pattern, size_t start, bool vertical, bool part2) {

    int p1 = start-1;
    int p2 = start;
    int smudges = 0;

    if (vertical) {
        while((p1 >= 0) && (p2 != pattern.size())) {
            smudges += count_smudge_r(pattern[p1], pattern[p2]);
            --p1;
            ++p2;
        } 
    } else {
        while ((p1 >= 0) && (p2 != pattern[0].size())) {
            smudges += count_smudge_c(pattern, p1, p2);
            --p1;
            ++p2;
        }
    }
    return part2 ? smudges == 1 : smudges == 0;
}

uint64_t solve(const std::vector<std::vector<std::string>>& input, bool part2) {

    uint64_t result = 0;
    
    for(const auto& pattern : input) {

        bool vertical = true;
        for (size_t row = 1; row < pattern.size(); ++row) {
            if (valid_reflection(pattern, row, true, part2)) {
                result += (100*row); 
                vertical = false;
                break;
            } 
        }

        if (vertical) {
            for (size_t col = 1; col < pattern[0].size(); ++col) {
                if (valid_reflection(pattern, col, false, part2)) {
                    result += col;
                    break;
                }
            }
        }
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

    uint64_t result = solve(input, part2);


    inputFile.close();

    std::cout << "Solution: " << result << std::endl;

    return 0;

}
