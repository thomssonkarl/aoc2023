#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <string_view>


int solve2(const std::vector<std::string>& input) {
    uint32_t result{};
    std::array<std::string_view, 9> word_digits = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    for (const auto& str : input) {
        uint32_t current_digit{};
        for (size_t i = 0; i < str.size(); ++i) {
            const auto ch = str[i];
            if (std::isdigit(ch)) {
                if (current_digit == 0) {
                    result += 10 * (ch - '0');
                }
                current_digit = ch - '0';
            }
            else {
                for (size_t j = 0; j < word_digits.size(); ++j) {
                    const auto& word = word_digits[j];
                    if(str.compare(i, word.size(), word) == 0) {
                        i += word.size() - 2;
                        if (current_digit == 0) {
                            result += 10 * (j + 1);
                        }
                        current_digit = j + 1;
                        break;
                    }
                }
            }
        }
        result += current_digit;
    }
    return result;
}

int solve(const std::vector<std::string>& input) {
    int result = 0;

    for (const auto& str : input) {
        auto start = str.begin();
        auto end = str.end() - 1;
        int first_digit = -1;
        int second_digit = -1;
        std::string combined(2, 'x');

        while (start < end) {

            if (isdigit(*start) && first_digit == -1) {
                first_digit = *start;
                combined[0] = first_digit;
            }

            if (isdigit(*end) && second_digit == -1) {
                second_digit = *end;
                combined[1] = second_digit;
            }

            if (first_digit != -1 && second_digit != -1) {
                result += std::stoi(combined);
                break;
            } 

            if (first_digit == -1) {
                ++start;
            }

            if (second_digit == -1) {
                --end;
            }

        }

        if (first_digit == -1 || second_digit == -1) {
            combined[0] = *start;
            combined[1] = *start;
            result += std::stoi(combined);
        }
    }

    return result;
}


int main() {
    std::ifstream inputFile("input1.txt");

    if (!inputFile) {
        std::cerr << "Error opening the input file!" << std::endl;
        return 1;

    }

    std::vector<std::string> input;
    std::string line;

    while (std::getline(inputFile, line)) {
        input.push_back(line);

    }

    int result = solve(input);
    int result2 = solve2(input);

    std::cout << "Solution: " << result << std::endl;
    std::cout << "Solution 2: " << result2 << std::endl;

    return 0;

}

