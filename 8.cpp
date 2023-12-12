#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <numeric>

size_t solve(const std::vector<std::string>& input, std::string LR, bool part2) {

    std::map<std::string, std::pair<std::string, std::string>> dir_map;

    for (const auto& str : input) {
        std::string key = str.substr(0, 3);
        std::string left = str.substr(7, 3);
        std::string right = str.substr(12, 3);
        dir_map[key] = std::make_pair(left, right);
    }
    
    size_t i = 0;

    if (part2) {
        std::vector<std::string> all_curr;
        std::vector<size_t> ns;

        for (const auto& entry : dir_map) {
            const std::string& key = entry.first;
            if (key.back() == 'A') all_curr.push_back(key);
        }

        for (auto &key : all_curr) {
            while(key[2] != 'Z') {
                switch(LR[i % (LR.size())]) {
                    case 'R':
                        key = dir_map[key].second;
                        break;
                    case 'L':
                        key = dir_map[key].first;
                        break;
                }
                ++i;
            }
            ns.push_back(i);
            i = 0;
        }

        size_t lc = 0;

        for(auto &n : ns) {
            if(lc == 0) lc = n;
            else lc = std::lcm(lc, n);
        }
        return lc;
    }

    std::string curr = "AAA";
    std::string goal = "ZZZ";

    while (curr != goal) {
        switch(LR[i % (LR.size())]) {
            case 'R':
                curr = dir_map[curr].second;
                break;
            case 'L':
                curr = dir_map[curr].first;
                break;
        }
        ++i;
    }

    return i;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> ?part2" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    bool part2 = std::stoi(argv[2]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the input file!" << std::endl;
        return 1;
    }

    std::vector<std::string> input;
    std::string line, LR;

    for (int i = 0; i < 2; ++i) {
        getline(inputFile, line);
        if (i == 0) LR = line;
    }

    while (getline(inputFile, line)) {
        input.push_back(line);
    }

    inputFile.close();

    size_t result = solve(input, LR, part2);

    std::cout << "Solution: " << result << std::endl;

    return 0;

}

