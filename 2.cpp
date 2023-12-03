#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <cmath>
#include <map>
#include <sstream>
#include <string_view>


int solve2(const std::vector<std::string>& input) {
    uint32_t result{};

    for (auto& str : input) {
        size_t colon_index = str.find(":");
        std::string current_game = str.substr(colon_index+2, std::string::npos);
        std::cout << current_game << std::endl;
        std::stringstream ss(current_game);
        std::string game_set;
        std::map<std::string, int> color_map;

        color_map["red"] = 0;
        color_map["green"] = 0;
        color_map["blue"] = 0;

        while(getline(ss, game_set, ';')) {
            std::stringstream ss2(game_set);
            std::string token;
            while(getline(ss2, token, ',')) {
                size_t space = token.find_first_not_of(" \t");
                if (space != std::string::npos) {
                    token = token.substr(space);
                }
                size_t separator = token.find_first_of(" \t");
                uint16_t amount = std::stoi(token.substr(0, separator));
                std::string color = token.substr(separator + 1); 

                if(color_map[color] < amount) {
                    std::cout << "Current max val of " << color << " is " << color_map[color] << " but we found " << amount << " " << color << std::endl;
                    color_map[color] = amount;
                    std::cout << "New updated: " << color_map[color] << std::endl;
                } 
            } 
        }
        result += color_map["red"] * color_map["green"] * color_map["blue"];
    } 
    return result;
}


int solve(const std::vector<std::string>& input) {
    uint32_t result{};

    std::map<std::string, int> color_map;

    color_map["red"] = 12;
    color_map["green"] = 13;
    color_map["blue"] = 14;

    for (auto& str : input) {
        size_t colon_index = str.find(":");
        uint16_t game_id = std::stoi(str.substr(5, colon_index - 5));

        std::string current_game = str.substr(colon_index+2, std::string::npos);
        std::stringstream ss(current_game);
        std::string game_set;

        bool possible = true;

        while(getline(ss, game_set, ';')) {
            if (!possible) break;
            std::stringstream ss2(game_set);
            std::string token;
            while(getline(ss2, token, ',')) {
                size_t space = token.find_first_not_of(" \t");
                if (space != std::string::npos) {
                    token = token.substr(space);
                }

                size_t separator = token.find_first_of(" \t");

                uint16_t amount = std::stoi(token.substr(0, separator));
                std::string color = token.substr(separator + 1); 
                if (color_map[color] < amount) {
                    possible = false;
                    break;
                }
            } 
        }
        if (possible) {
            result += game_id;
        }
    } 
    return result;
}


int main() {
    std::ifstream inputFile("input2.txt");
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
