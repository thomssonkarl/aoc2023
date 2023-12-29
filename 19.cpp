#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

enum class CompOp {
    GreaterThan,
    LessThan
};

struct Rule {
    char variable;
    std::string target;
    CompOp op;
    uint32_t val;
};

struct Workflow {
    std::string src; 
    std::string dst;
    std::vector<Rule> rules;
};

struct Rating {
   int x, m, a, s; 
};

bool rule_satisfied(const Rule& rule, const Rating& rating) {
    switch (rule.variable) {
        case 'x':
            return (rule.op == CompOp::GreaterThan) ? (rating.x > rule.val) : (rating.x < rule.val);
        case 'm':
            return (rule.op == CompOp::GreaterThan) ? (rating.m > rule.val) : (rating.m < rule.val);
        case 'a':
            return (rule.op == CompOp::GreaterThan) ? (rating.a > rule.val) : (rating.a < rule.val);
        case 's':
            return (rule.op == CompOp::GreaterThan) ? (rating.s > rule.val) : (rating.s < rule.val);
        default:
            return false;
    }
}

std::vector<Rating> parse_raw_ratings(const std::vector<std::string>& rts_raw) {
    std::vector<Rating> ratings;

    for (const auto& str : rts_raw) {
        std::istringstream iss(str);
        Rating rating;
        char discard;
        iss.ignore(std::strlen("{x="));
        iss >> rating.x >> discard;
        iss.ignore(std::strlen("m=")) >> rating.m >> discard;
        iss.ignore(std::strlen("a=")) >> rating.a >> discard;
        iss.ignore(std::strlen("s=")) >> rating.s;
        iss.ignore();
        ratings.push_back(rating);
    }

    return ratings;
}

std::map<std::string, Workflow> parse_raw_workflows(const std::vector<std::string>& wfs_raw) {

    std::map<std::string, Workflow> workflow_map;

    for (const auto& line : wfs_raw) {
        size_t open = line.find_first_of('{');
        size_t close = line.find_first_of('}');
        size_t dst_i = line.find_last_of(',');
        std::string dst = line.substr(dst_i + 1, close-dst_i-1);//line.size()-(dst_i+2));
        std::string src = line.substr(0, open);
        std::string content = line.substr(open + 1, dst_i-open-1);
        
        std::istringstream iss(content);
        std::string token;
        Workflow workflow;

        while (getline(iss, token, ',')) {
            Rule rule;
            std::istringstream rss(token);
            rss >> rule.variable;

            char op;
            rss >> op;
            rule.op = (op == '>') ? CompOp::GreaterThan : CompOp::LessThan;
            rss >> rule.val;

            size_t colon = token.find(':');
            size_t comma = token.find(',');
            rule.target = token.substr(colon + 1, comma - colon - 1);
            workflow.rules.push_back(rule);
        }
        workflow.src = src;
        workflow.dst = dst;
        workflow_map[src] = workflow; 
    }
    return workflow_map;
}

bool check_accepted(const Workflow& workflow, const Rating& rating, std::map<std::string, Workflow> workflow_map) {
    
    for (auto rule : workflow.rules) {
        if (rule_satisfied(rule, rating)) {
            if (rule.target == "A") return true;
            if (rule.target == "R") return false;
            return check_accepted(workflow_map[rule.target], rating, workflow_map);
        }
    }

    if (workflow.dst == "A") return true;
    if (workflow.dst == "R") return false;
    return check_accepted(workflow_map[workflow.dst], rating, workflow_map);
}

int solve(const std::vector<std::string>& wfs_raw, const std::vector<std::string>& rts_raw) {
    uint32_t result{}; 

    std::map<std::string, Workflow> workflows = parse_raw_workflows(wfs_raw);  
    std::vector<Rating> ratings = parse_raw_ratings(rts_raw);  

    for (const auto& rating : ratings) {
        if (check_accepted(workflows["in"], rating, workflows)) {
            result += (rating.x + rating.m + rating.a + rating.s);
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
    std::vector<std::string> workflows;
    std::vector<std::string> ratings;
    std::string line;
    bool parse_workflows = true;
    while (getline(inputFile, line)) {
        if (line.empty()) {
            parse_workflows = false;
            continue;
        } 
        if (parse_workflows) {
            workflows.push_back(line);
        } else {
            ratings.push_back(line);
        }
    }

    inputFile.close();

    int result = solve(workflows, ratings);

    std::cout << "Solution: " << result << std::endl;

    return 0;

}

