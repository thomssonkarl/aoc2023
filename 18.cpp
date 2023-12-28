#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>


std::pair<uint64_t, uint64_t> get_coord(const char dir, const uint64_t num, const uint64_t x, const uint64_t y) {
    switch(dir) {
        case 'R':
            return std::make_pair(x+num, y);
        case 'L':
            return std::make_pair(x-num, y);
        case 'D':
            return std::make_pair(x, y+num);
        case 'U':
            return std::make_pair(x, y-num);
        default:
            std::cerr << "Invalid direction passed" << std::endl;
            return std::make_pair(0,0);
    }
}

std::pair<char, uint64_t> extract_hex(std::string color) {
    size_t open = color.find_first_of('(');
    size_t close = color.find_first_of(')');
    std::string stripped = color.substr(open + 2, close - open - 2);

    int dir_i = stripped.back() - '0'; 
    char dir;
    switch(dir_i) {
        case 0:
            dir = 'R';
            break;
        case 1: 
            dir = 'D';
            break;
        case 2: 
            dir = 'L';
            break;
        case 3: 
            dir = 'U';
            break;
        default:
            std::cerr << "Invalid direction parsed from hex" << std::endl;
            dir = 'X';
            break;
    }
    std::string num_str = stripped.substr(0, stripped.length() - 1);
    std::istringstream hexs(num_str);
    uint64_t num;
    hexs >> std::hex >> num;
    return std::make_pair(dir, num);
}

uint64_t solve(const std::vector<std::string>& input, bool part2) {
    uint64_t result{}; 

    std::pair<uint64_t, uint64_t> start = std::make_pair(0,0);

    std::vector<std::pair<uint64_t, uint64_t>> coords;
    coords.push_back(start);
    size_t i = 0;
    int circumference = 0;
    for (const auto& str : input) {
        std::istringstream iss(str);
        char dir;
        int num;
        std::string color;
        iss >> dir >> num >> color;
        if (part2) {
            std::pair<char, uint64_t> conv = extract_hex(color);
            dir = conv.first;
            num = conv.second;
        }
        std::pair<uint64_t, uint64_t> current = coords[i];
        std::pair<uint64_t, uint64_t> c = get_coord(dir, num, current.first, current.second);
        if (c != start)
            coords.push_back(c);
        circumference += num;
        ++i;
    }

    size_t n = coords.size();
    uint64_t area = 0;
    // Shoelace formula
    for(size_t i = 0; i < n; ++i) {
        size_t ni = (i + 1) % n;
        area += (coords[i].first * coords[ni].second - coords[ni].first * coords[i].second);
    }
    // Picks theorem
    result = (area / 2)  - (circumference / 2) + circumference + 1;

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

    uint64_t result = solve(input, part2);

    std::cout << "Solution: " << result << std::endl;

    return 0;

}

