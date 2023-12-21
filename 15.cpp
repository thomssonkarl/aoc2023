#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

uint16_t hash(const std::string& str) {
    uint16_t current_value = 0;
    for(char c : str) {
        current_value += c;
        current_value *= 17;
        current_value = current_value % 256;
    }
    return current_value; 
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
    std::string input; 
    while (getline(inputFile, line)) input = line;
    
    inputFile.close();

    uint64_t result{};
    std::stringstream ss(input);
    std::string token;
    while(getline(ss, token, ',')) result += hash(token);

    std::cout << "Solution: " << result << std::endl;

    return 0;

}

