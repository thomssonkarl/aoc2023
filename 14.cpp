#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>


uint64_t solve(std::vector<std::string>& input) {
    uint64_t result{}; 
    
    for (size_t col = 0; col < input[0].size(); ++col) {
       for(size_t row = 1; row < input.size(); ++row) {
            if(input[row][col] == 'O') {
                size_t curr = row;
                while (input[curr-1][col] == '.') --curr;
                input[row][col] = '.';
                input[curr][col] = 'O';
            }
       } 
    }

    for (size_t row = 0; row < input.size(); ++row) {
        size_t counter = 0;
        for(size_t ch = 0; ch < input[row].size(); ++ch) {
            if(input[row][ch] == 'O') counter++;
        }
        result += counter * (input.size() - row);
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
    std::vector<std::string> input;
    std::string line;
    while (getline(inputFile, line)) {
        input.push_back(line);
    }

    inputFile.close();

    uint64_t result = solve(input);

    std::cout << "Solution: " << result << std::endl;

    return 0;

}

