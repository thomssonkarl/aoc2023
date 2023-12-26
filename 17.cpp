#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <queue>
#include <algorithm>
#include <limits>

using dir_t = std::pair<int, int>;

struct Node {
    int x, y, cost, steps;
    dir_t dir;

    Node(int x, int y, int cost, int steps, std::pair<int, int> dir)
        : x(x), y(y), cost(cost), steps(steps), dir(dir) {}

    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

struct State {
    int x, y, steps;
    std::pair<int, int> dir;

    State(int x, int y, int steps, std::pair<int, int> dir)
        : x(x), y(y), steps(steps), dir(dir) {}

    bool operator<(const State& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        if (y != other.y) {
            return y < other.y;
        }
        if (steps != other.steps) {
            return steps < other.steps;
        }
        return dir < other.dir;
    }
};

int solve(const std::vector<std::vector<int>>& input) {
    const size_t rows = input.size();
    const size_t cols = input[0].size();
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    std::map<State, int> seen;

    const Node start(0,0,0,0,{0,0});
    pq.push(start);

    while(!pq.empty()) {
        Node current = pq.top(); pq.pop();
        auto [x, y, cost, steps, dir] = current;
        State cs(x,y,steps,dir);

        if (seen.contains(cs)) continue;
        seen[cs] = cost;

        const std::vector<dir_t> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        for (const auto& direction : directions) {
            int nx = x + direction.first;
            int ny = y + direction.second;
            int new_steps = (direction != dir) ? 1 : steps+1;

            bool reverse = direction == std::make_pair(-dir.first, -dir.second);
            bool valid_steps = new_steps <= 3;

            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && !reverse && valid_steps) {
                int new_cost = cost + input[ny][nx];
                State new_state(nx,ny,new_steps,direction);
                if (seen.contains(new_state)) continue;
                pq.push(Node(nx,ny,new_cost,new_steps,direction));
            }
        }
    }
    int result = std::numeric_limits<int>::max();
    for (const auto& state : seen) {
        auto [x, y, steps, dir] = state.first;
        if (x == cols-1 && y == rows-1) {
            result = std::min(result, state.second);
        } 
    }
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

    std::vector<std::vector<int>> input;
    std::string line;
    
    while (getline(inputFile, line)) {
        std::vector<int> row;
        for (int i = 0; i < line.size(); ++i) row.push_back(line[i] - '0');
        input.push_back(row);
    }

    inputFile.close();

    int result = solve(input);

    std::cout << "Solution: " << result << std::endl;

    return 0;

}

