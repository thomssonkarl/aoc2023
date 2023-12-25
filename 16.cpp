#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <deque>
#include <set>

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
    if (!visited.count({x, y, dx, dy})) {
        visited.insert({x, y, dx, dy});
        queue.push_back({x, y, dx, dy});
    }
}

size_t solve(std::vector<std::vector<char>>& input) {
    Tile start = {-1, 0, 1, 0};
    std::deque<Tile> queue(1, start);
    std::set<Tile> visited;

    while (!queue.empty()) {
        Tile current = queue.front();
        queue.pop_front();

        int x = current.x + current.dx;
        int y = current.y + current.dy;

        if (!is_within_bounds(x, y, input)) {
            continue;
        }

        char tile_type = input[y][x];

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
    std::vector<std::vector<char>> input;
    std::string line;
    
    while (getline(inputFile, line)) {
        std::vector<char> row(line.begin(), line.end());
        input.push_back(row);
    }

    inputFile.close();

    size_t result = solve(input);

    std::cout << "Solution: " << result << std::endl;

    return 0;
}

