#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

std::string urlDecode(std::string str) {
    std::string ret;
    char ch; int i;
    for (size_t p = 0; p < str.length(); p++) {
        if (str[p] == '+') ret += ' ';
        else if (str[p] == '%') {
            sscanf(str.substr(p + 1, 2).c_str(), "%x", &i);
            ch = static_cast<char>(i); ret += ch; p += 2;
        } else ret += str[p];
    }
    return ret;
}

struct Player { std::string name; int goals; int assists; };

int main() {
    std::string winner = "", goalsStr = "", submitter = "";
    char* lenStr = std::getenv("CONTENT_LENGTH");
    
    if (lenStr != nullptr) {
        int length = std::stoi(lenStr);
        std::string data = ""; char ch;
        for (int i = 0; i < length; ++i) { std::cin.get(ch); data += ch; }
        
        std::stringstream ss(data); std::string segment;
        while (std::getline(ss, segment, '&')) {
            size_t eq = segment.find('=');
            if (eq == std::string::npos) continue;
            std::string key = segment.substr(0, eq);
            std::string val = urlDecode(segment.substr(eq + 1));
            if (key == "winner_name") winner = val;
            if (key == "goals_scored") goalsStr = val;
            if (key == "username") submitter = val;
        }
    }

    if (!winner.empty() && !goalsStr.empty()) {
        int newGoals = std::stoi(goalsStr);
        std::vector<Player> squad;
        std::ifstream inFile("player_data.txt");
        std::string line;
        bool found = false;

        while (std::getline(inFile, line)) {
            if (line.empty()) continue;
            std::stringstream lineSS(line);
            std::string name, g, a;
            std::getline(lineSS, name, ',');
            std::getline(lineSS, g, ',');
            std::getline(lineSS, a, ',');
            
            int currentGoals = std::stoi(g);
            int currentAssists = std::stoi(a);
            
            if (name == winner) {
                currentGoals += newGoals; // Add new goals to existing ones
                found = true;
            }
            squad.push_back({name, currentGoals, currentAssists});
        }
        inFile.close();

        // Write the data back down to the text database
        std::ofstream outFile("player_data.txt");
        for (const auto& p : squad) {
            outFile << p.name << "," << p.goals << "," << p.assists << "\n";
        }
        outFile.close();
    }

    // Refresh and return smoothly to the control room
    std::cout << "Content-type:text/html\r\n\r\n";
    std::cout << "<html><head><meta http-equiv='refresh' content='0;url=https://my-cpp-backend-api.onrender.com" << submitter << "'></head></html>";

    return 0;
}
