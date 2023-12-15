#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <cstdlib>

using coord_t = std::pair<size_t, size_t>;

bool poss_conn(coord_t curr, coord_t neighbor, const std::vector<std::string>& input) {

    bool above = curr.first < neighbor.first;
    bool below = curr.first > neighbor.first;
    bool right = curr.second > neighbor.second;
    bool left = curr.second < neighbor.second;

    char c_pipe = input[curr.first][curr.second]; 
    char n_pipe = input[neighbor.first][neighbor.second];    
    
    // I have sinned..
    if(n_pipe == '.') return false; 

    if(c_pipe == 'F' && n_pipe == '-' && left) return true;
    if(c_pipe == 'F' && n_pipe == '|' && above) return true;
    if(c_pipe == 'F' && n_pipe == 'J' && left) return true;
    if(c_pipe == 'F' && n_pipe == '7' && left) return true;
    if(c_pipe == 'F' && n_pipe == 'J' && above) return true;
    if(c_pipe == 'F' && n_pipe == 'L' && above) return true;

    if(c_pipe == '|' && n_pipe == 'L' && above) return true;
    if(c_pipe == '|' && n_pipe == '7' && below) return true;
    if(c_pipe == '|' && n_pipe == 'J' && above) return true;
    if(c_pipe == '|' && n_pipe == 'F' && below) return true;
    if(c_pipe == '|' && n_pipe == '|' && (below || above)) return true;

    if(c_pipe == 'L' && n_pipe == '-' && left) return true;
    if(c_pipe == 'L' && n_pipe == '|' && below) return true;
    if(c_pipe == 'L' && n_pipe == 'J' && left) return true;
    if(c_pipe == 'L' && n_pipe == 'F' && below) return true;
    if(c_pipe == 'L' && n_pipe == '7' && (left || below)) return true;

    if(c_pipe == 'J' && n_pipe == '|' && below) return true;
    if(c_pipe == 'J' && n_pipe == '-' && right) return true;
    if(c_pipe == 'J' && n_pipe == 'F' && right) return true;
    if(c_pipe == 'J' && n_pipe == 'L' && right) return true;
    if(c_pipe == 'J' && n_pipe == 'F' && below) return true;
    if(c_pipe == 'J' && n_pipe == '7' && below) return true;

    if(c_pipe == '7' && n_pipe == '-' && right) return true;
    if(c_pipe == '7' && n_pipe == '|' && above) return true;
    if(c_pipe == '7' && n_pipe == 'F' && right) return true;
    if(c_pipe == '7' && n_pipe == 'J' && above) return true;
    if(c_pipe == '7' && n_pipe == 'L' && (right || above)) return true;

    if(c_pipe == '-' && n_pipe == '7' && left) return true;
    if(c_pipe == '-' && n_pipe == 'J' && left) return true;
    if(c_pipe == '-' && n_pipe == 'L' && right) return true;
    if(c_pipe == '-' && n_pipe == 'F' && right) return true;
    if(c_pipe == '-' && n_pipe == '-' && (right || left)) return true;
    

    return false;
}

bool valid_n(const coord_t& n) {
    return (n.first >= 0 && n.first <= 140 && n.second >= 0 && n.second <= 140);
}

coord_t find_next(coord_t node, 
                  std::set<coord_t> visited_set,
                  coord_t start,
                  const std::vector<std::string>& input) {

    coord_t w = std::make_pair(node.first + 1, node.second);
    coord_t a = std::make_pair(node.first, node.second - 1);
    coord_t s = std::make_pair(node.first - 1, node.second);
    coord_t d = std::make_pair(node.first, node.second + 1);

    std::array<coord_t, 4> neighbors = {w, a, s, d};

    for (coord_t &neighbor : neighbors) {
        if (valid_n(neighbor)) {
            bool visited = visited_set.count(neighbor) > 0; 
            bool done = start == neighbor;
            if (poss_conn(node, neighbor, input) && (!visited || done)) return neighbor;
        }
    }
    return node;
}


int solve(std::vector<std::string>& input) {
    uint32_t result{}; 

    coord_t sc;
    size_t row = 0;
    size_t col = 0;
    for (const auto& str : input) {
        col = str.find('S');
        if (col != std::string::npos) sc = std::make_pair(row, col);
        else ++row;
    }

    input[sc.first][sc.second] = '-'; //TODO: find_start_char

    coord_t nc = sc;
    std::set<coord_t> visited;

    do {
        visited.insert(nc); 
        nc = find_next(nc, visited, sc, input);
        ++result;

    } while(nc != sc);

    return (result / 2) + (result % 2);
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

    int result = solve(input);

    std::cout << "Solution: " << result << std::endl;

    return 0;

}

