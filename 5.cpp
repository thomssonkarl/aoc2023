#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <limits>
#include <set>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;

    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the input file!" << std::endl;
        return 1;

    }
    
    uint32_t result{};
    uint32_t result2{};

    std::string line;
    std::vector<std::string> parts;
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string file_str = buffer.str();

    size_t pos = 0;
    while ((pos = file_str.find("\n\n")) != std::string::npos) {
        parts.push_back(file_str.substr(0, pos));
        file_str.erase(0, pos + 2);
    }

    if (!file_str.empty()) parts.push_back(file_str);

    std::string seeds_str = parts[0]; 
    std::vector<uint32_t> seeds;
    size_t colon = seeds_str.find(":");
    seeds_str = seeds_str.substr(colon+2);
    std::stringstream ss(seeds_str);
    std::string n;
    while(getline(ss, n, ' ')) seeds.push_back(std::stol(n));

    
    result = std::numeric_limits<uint32_t>::max();
    
    for (auto& seed : seeds) {
        for (size_t i = 1; i < parts.size(); ++i) {
            std::stringstream pss(parts[i]);
            std::string p;
            std::vector<std::string> lines;  
            while(getline(pss, p , '\n')) lines.push_back(p);
            for (size_t j = 1; j < lines.size(); ++j) {
                std::string dst, src, len;
                std::stringstream lss(lines[j]);
                lss >> dst >> src >> len;
                uint32_t dst_v = std::stol(dst);
                uint32_t src_v = std::stol(src);
                uint32_t len_v = std::stol(len);
                if (seed >= src_v && seed <= (src_v + len_v - 1)) {
                    seed += (dst_v - src_v);
                    break;
                }
            }
        }
        if (seed < result) result = seed;
    }


    inputFile.close();

    std::cout << "Solution: " << result << std::endl;
    std::cout << "Solution 2: " << result2 << std::endl;

    return 0;

}

