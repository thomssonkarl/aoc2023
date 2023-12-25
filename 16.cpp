#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <deque>
#include <set>
#include <thread>
#include <chrono>
#include <algorithm>

using coord_t = std::pair<int, int>;

struct Tile {
    int x;
    int y;
    int dx;
    int dy;

    bool operator<(const Tile& other) const {
        return std::tie(x, y, dx, dy) < std::tie(other.x, other.y, other.dx, other.dy);
    }
};

bool is_within_bounds(int x, int y, const std::vector<std::vector<char>>& input) {
    return (x >= 0 && y >= 0 && x < input[0].size() && y < input.size());
}

bool is_valid_move(char t, int dx, int dy) {
    return (t == '.' || (t == '-' && dx != 0) || (t == '|' && dy != 0));
}

void process_move(int x, int y, int dx, int dy, std::set<Tile>& visited, std::deque<Tile>& queue) {
    if (!visited.contains({x, y, dx, dy})) {
        visited.insert({x, y, dx, dy});
        queue.push_back({x, y, dx, dy});
    }
}


void show_simulation(std::vector<std::vector<char>>& simulation, int dx, int dy, int x, int y) {
    std::cout << "\033[2J\033[H";
    
    for (const auto& row : simulation) {
        for (char c : row) {
            std::cout << c;
        }
        std::cout << '\n';
    }
    std::cout.flush();
    if (simulation[y][x] == '.') {
        char laser;
        if (dx > 0) laser = '>';
        if (dx < 0) laser = '<';
        if (dy > 0) laser = 'v';
        if (dy < 0) laser = '^';
        simulation[y][x] = laser;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

size_t solve(std::vector<std::vector<char>>& input, Tile start, bool verbose) {
    std::deque<Tile> queue(1, start);
    std::set<Tile> visited;
    std::vector<std::vector<char>> copy = input;

    while (!queue.empty()) {
        Tile current = queue.front();
        queue.pop_front();

        int x = current.x + current.dx;
        int y = current.y + current.dy;

        if (!is_within_bounds(x, y, input)) {
            continue;
        }

        char tile_type = input[y][x];

        if (verbose)
            show_simulation(copy, current.dx, current.dy, current.x, current.y);
        
        if (is_valid_move(tile_type, current.dx, current.dy)) {
            process_move(x, y, current.dx, current.dy, visited, queue);
        } else if (tile_type == '\\') {
            process_move(x, y, current.dy, current.dx, visited, queue);
        } else if (tile_type == '/') {
            process_move(x, y, -current.dy, -current.dx, visited, queue);
        } else {
            if (tile_type == '|') {
                process_move(x, y, 0, 1, visited, queue);
                process_move(x, y, 0, -1, visited, queue);
            } else {
                process_move(x, y, 1, 0, visited, queue);
                process_move(x, y, -1, 0, visited, queue);
            }
        }
    }

    std::set<coord_t> energized;

    for (const auto& tile : visited) {
        energized.insert({tile.x, tile.y});
    }

    return energized.size();
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input_file>  <?part2> <?verbose>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the input file!" << std::endl;
        return 1;
    }

    bool part2 = std::stoi(argv[2]);
    bool verbose = std::stoi(argv[3]);
    std::vector<std::vector<char>> input;
    std::string line;
    
    while (getline(inputFile, line)) {
        std::vector<char> row(line.begin(), line.end());
        input.push_back(row);
    }

    inputFile.close();
    
    if(part2) {
        size_t curr_max = 0;
        Tile start;
        for (int row = 0; row < input.size(); ++row) {
            start = {-1, row, 1, 0};
            curr_max = std::max(curr_max, solve(input, start, verbose));
            start = {static_cast<int>(input[0].size()), row, -1, 0};
            curr_max = std::max(curr_max, solve(input, start, verbose));
        }
        for (int col = 0; col < input[0].size(); ++col) {
            start = {col, -1, 0, 1};
            curr_max = std::max(curr_max, solve(input, start, verbose));
            start = {col, static_cast<int>(input.size()), 0, -1};
        }
        std::cout << "Solution: " << curr_max << std::endl;
        return 0;
    }

    size_t result = solve(input, {-1,0,1,0}, verbose);

    std::cout << "Solution: " << result << std::endl;

    return 0;
}

