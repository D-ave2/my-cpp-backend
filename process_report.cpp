#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

struct PlayerGoals {
    std::string name;
    int total_goals;
};

// Helper to update the global golden boot file
void updateGoldenBoot(const std::string& name, int goals_to_add) {
    if (goals_to_add <= 0) return;
    
    std::vector<PlayerGoals> records;
    std::ifstream infile("golden_boot.txt");
    std::string line;
    bool found = false;

    // Read current total goals database
    while (std::getline(infile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string pName, gStr;
        std::getline(ss, pName, ',');
        std::getline(ss, gStr, ',');
        
        int current_goals = 0;
        try { if (!gStr.empty()) current_goals = std::stoi(gStr); } catch(...) {}
        
        if (pName == name) {
            current_goals += goals_to_add;
            found = true;
        }
        records.push_back({pName, current_goals});
    }
    infile.close();

    if (!found) {
        records.push_back({name, goals_to_add});
    }

    // Write back updated totals
    std::ofstream outfile("golden_boot.txt", std::ios::trunc);
    for (const auto& r : records) {
        outfile << r.name << "," << r.total_goals << "\n";
    }
    outfile.close();
}

// Structure for MOTM stats
struct MOTMPlayer { std::string name; int count; int goals; int assists; };

int main() {
    // Read POST data from form
    std::string data = "";
    char* lenStr = std::getenv("CONTENT_LENGTH");
    if (lenStr != nullptr) {
        int length = std::stoi(lenStr);
        char ch;
        for (int i = 0; i < length; ++i) { std::cin.get(ch); data += ch; }
    }

    // Parse values
    std::string wName = "", lName = "", mName = "", submitter = "";
    int wGoals = 0, lGoals = 0, mGoals = 0, mAssists = 0;

    std::stringstream ss(data); std::string segment;
    while (std::getline(ss, segment, '&')) {
        size_t eq = segment.find('='); if (eq == std::string::npos) continue;
        std::string key = segment.substr(0, eq);
        std::string val = segment.substr(eq + 1);
        // Clean up URL encoding spaces
        for (size_t i = 0; i < val.length(); ++i) { if (val[i] == '+') val[i] = ' '; }

        if (key == "winner_name") wName = val;
        if (key == "winner_goals") wGoals = std::stoi(val);
        if (key == "loser_name") lName = val;
        if (key == "loser_goals") lGoals = std::stoi(val);
        if (key == "motm_name") mName = val;
        if (key == "motm_goals") mGoals = std::stoi(val);
        if (key == "motm_assists") mAssists = std::stoi(val);
        if (key == "submitter") submitter = val;
    }

    std::cout << "Content-type:text/html; charset=UTF-8\r\n\r\n";

    // BACKEND GUARDRAIL: Reject if not Admin
    if (submitter != "Admin") {
        std::cout << "<html><body><h2>❌ Unauthorized submission source blocked.</h2></body></html>";
        return 0;
    }

    // 1. Log chronological match history logs
    std::ofstream winF("winners.txt", std::ios::app);
    winF << wName << "," << wGoals << "\n"; winF.close();

    std::ofstream loseF("losers.txt", std::ios::app);
    loseF << lName << "," << lGoals << "\n"; loseF.close();

    // 2. NEW ELEMENT: Update Global Tournament Goals Tracker (Golden Boot)
    updateGoldenBoot(wName, wGoals);
    updateGoldenBoot(lName, lGoals);

    // 3. Update MOTM stand-alone stats file
    std::vector<MOTMPlayer> motm_roster;
    std::ifstream file("player_data.txt");
    std::string line;
    bool motm_found = false;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream mss(line);
        std::string pName, cStr, gStr, aStr;
        std::getline(mss, pName, ',');
        std::getline(mss, cStr, ',');
        std::getline(mss, gStr, ',');
        std::getline(mss, aStr, ',');

        int c = 0, g = 0, a = 0;
        try { if(!cStr.empty()) c = std::stoi(cStr); } catch(...) {}
        try { if(!gStr.empty()) g = std::stoi(gStr); } catch(...) {}
        try { if(!aStr.empty()) a = std::stoi(aStr); } catch(...) {}

        if (pName == mName) {
            c += 1; g += mGoals; a += mAssists;
            motm_found = true;
        }
        motm_roster.push_back({pName, c, g, a});
    }
    file.close();

    if (!motm_found && !mName.empty()) {
        motm_roster.push_back({mName, 1, mGoals, mAssists});
    }

    std::ofstream outfile("player_data.txt", std::ios::trunc);
    for (const auto& p : motm_roster) {
        outfile << p.name << "," << p.count << "," << p.goals << "," << p.assists << "\n";
    }
    outfile.close();

    // Redirect smoothly back to leaderboard view
    std::cout << "<html><head><meta http-equiv='refresh' content='0;url=leaderboard.cgi?username=Admin'></head></html>";
    return 0;
}
