#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

char& get_next(std::vector<std::string>& input, char direction, char& curr, size_t col, size_t row) {
    switch (direction) {
        case 'N':
            return row > 0 ? input[row-1][col] : curr;
            break;
        case 'W':
            return col > 0 ? input[row][col-1] : curr;
            break;
        case 'S':
            return row < input.size()-1 ? input[row+1][col] : curr;
            break;
        case 'E':
            return col < input[0].size()-1 ? input[row][col+1] : curr;
            break;
        default:
            std::cerr << "Invalid direction passed: " << direction << std::endl;
            return curr;
            break;
    }
}

bool tilt(std::vector<std::string>& input, char direction) {  
    bool changes_made = false;

    for (size_t col = 0; col < input[0].size(); ++col) {
        for (size_t row = 0; row < input.size(); ++row) {
            char& curr = input[row][col];
            char& next = get_next(input, direction, curr, col, row); 
            if (curr == 'O' && next == '.') {
                std::swap(curr, next);
                changes_made = true;
            }
        }
    } 

    return changes_made ? tilt(input, direction) : changes_made;
}

std::string stringify_grid(const std::vector<std::string>& grid) {
    std::string str;
    for (const auto& s : grid) str += s;

    return str;
}

uint64_t calc_beam_load(std::vector<std::string>& input) {
    uint64_t result{};
    for (size_t row = 0; row < input.size(); ++row) {
        size_t counter = 0;
        for(size_t ch = 0; ch < input[row].size(); ++ch) {
            if(input[row][ch] == 'O') counter++;
        }
        result += counter * (input.size() - row);
    }

    return result;
}

uint64_t solve(std::vector<std::string>& input) {
    tilt(input, 'N');

    return calc_beam_load(input);
}


uint64_t solve2(std::vector<std::string>& input) {
    size_t cycles = 1000000000;
    std::map<std::string, size_t> states;
    std::array<char, 4> directions = {'N', 'W', 'S', 'E'};
    for (size_t c = 0; c < cycles; ++c) {
        for (size_t i = 0; i < directions.size(); ++i) {
            tilt(input, directions[i]);
        }
        std::string sk = stringify_grid(input);
        if(!states.contains(sk)) {
            states[sk] = c;
        } else {
            size_t loop_length = c - states[sk];
            size_t remaining_cycles = cycles - c;
            size_t complete_loops = remaining_cycles / loop_length;
            c += complete_loops * loop_length;
        }
    }
    return calc_beam_load(input);
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

    uint64_t result = part2 ? solve2(input) : solve(input);

    std::cout << "Solution: " << result << std::endl;

    return 0;

}

