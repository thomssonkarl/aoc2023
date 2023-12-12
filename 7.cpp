#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

struct Hand {
    std::string str;
    uint16_t type;
    int bid;
};

bool cgt(char rank1, char rank2, bool part2) {
    std::string card_order = part2 ? "J23456789TQKA" : "23456789TJQKA";
    size_t p1 = card_order.find(rank1);
    size_t p2 = card_order.find(rank2);
    return p1 > p2;
}

uint16_t check_hand(std::string hand, bool part2) {
    std::map<char, uint16_t> c_count;
    for (char c : hand) c_count[c]++;

    std::vector<uint16_t> values;
    for (const auto& pair : c_count) values.push_back(pair.second);
    std::sort(values.begin(), values.end());

    if(part2 && c_count.contains('J')) {
        uint16_t amount_j = c_count['J'];
        auto it = std::find(values.begin(), values.end(), amount_j);
        values.erase(it);
        values[values.size() - 1] += amount_j;
    }

    if(values.size() == 2) return (values[0] == 2) ? 5 : 6; 
    if(values.size() == 3) return (values[2] == 3) ? 4 : 3;
    if(values.size() == 5) return 1;
    if(values.size() == 4) return 2;

    return 7;
}

int compare_hands(std::string h1, std::string h2, bool part2) {
    if (check_hand(h1, part2) > check_hand(h2, part2)) return -1;
    if (check_hand(h2, part2) > check_hand(h1, part2)) return 1;
    for(size_t c = 0; c < 5; c++) {
        if (cgt(h1[c], h2[c], part2)) return -1;
        if (cgt(h2[c], h1[c], part2)) return 1;
    } 
    return 0;
}

void sort_hands(std::vector<Hand>& arr, bool part2) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (compare_hands(arr[j].str, arr[j + 1].str, part2) < 0) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}


int solve(const std::vector<std::string>& input, bool part2) {
    uint32_t result{}; 

    std::vector<Hand> hands;

    for (const auto& str : input) {
        std::stringstream ss(str);
        std::string hand, ba;
        ss >> hand >> ba;
        hands.push_back({hand, check_hand(hand, part2), std::stoi(ba)});
    }

    sort_hands(hands, part2);
    
    for (size_t i = 0; i < hands.size(); ++i) result += hands[i].bid * (i+1);
    
    return result;
}

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

    std::vector<std::string> input;
    std::string line;

    while (getline(inputFile, line)) {
        input.push_back(line);

    }

    inputFile.close();

    int result = solve(input, false);
    int result2 = solve(input, true);

    std::cout << "Solution: " << result << std::endl;
    std::cout << "Solution 2: " << result2 << std::endl;

    return 0;

}

