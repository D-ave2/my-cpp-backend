#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <map>

struct MVPPlayer { std::string name; int motm_count; int goals; int assists; };
struct MatchRecord { std::string winner_name; int winner_goals; std::string loser_name; int loser_goals; };

// Struct to hold calculated team/player performance records
struct PerformanceStats {
    std::string name;
    int wins = 0;
    int losses = 0;
    int total_goals = 0;
    double win_percentage = 0.0;
};

bool rankByMVP(const MVPPlayer& x, const MVPPlayer& y) {
    if (x.motm_count != y.motm_count) return x.motm_count > y.motm_count;
    return x.goals > y.goals;
}

bool rankByGoals(const PerformanceStats& x, const PerformanceStats& y) {
    if (x.total_goals != y.total_goals) return x.total_goals > y.total_goals;
    return x.win_percentage > y.win_percentage;
}

int main() {
    std::string username = "User";
    char* queryString = std::getenv("QUERY_STRING");
    std::string query = (queryString != nullptr) ? std::string(queryString) : "";
    
    size_t uPos = query.find("username=");
    if (uPos != std::string::npos) {
        size_t amp = query.find("&", uPos);
        username = (amp != std::string::npos) ? query.substr(uPos + 9, amp - (uPos + 9)) : query.substr(uPos + 9);
    }

    // Handle database truncation safely when Reset button is pressed
    if (query.find("action=reset") != std::string::npos) {
        std::ofstream f1("player_data.txt", std::ofstream::trunc); f1.close();
        std::ofstream f2("winners.txt", std::ofstream::trunc); f2.close();
        std::ofstream f3("losers.txt", std::ofstream::trunc); f3.close();
        std::ofstream f4("golden_boot.txt", std::ofstream::trunc); f4.close();
        
        std::cout << "Content-type:text/html\r\n\r\n";
        std::cout << "<html><head><meta http-equiv='refresh' content='0;url=leaderboard.cgi?username=" << username << "'></head></html>";
        return 0;
    }

    std::cout << "Content-type:text/html; charset=UTF-8\r\n\r\n";

    // 1. READ PLAYER MOTM DATA
    std::vector<MVPPlayer> roster;
    std::ifstream file("player_data.txt");
    std::string line;
    while (std::getline(file, line)) {
        if(line.empty()) continue;
        std::stringstream ss(line);
        std::string name, count, goals, assists;
        std::getline(ss, name, ','); std::getline(ss, count, ',');
        std::getline(ss, goals, ','); std::getline(ss, assists, ',');
        
        int c_count = 0, c_g = 0, c_a = 0;
        try { if (!count.empty()) c_count = std::stoi(count); } catch(...) {}
        try { if (!goals.empty()) c_g = std::stoi(goals); } catch(...) {}
        try { if (!assists.empty()) c_a = std::stoi(assists); } catch(...) {}
        roster.push_back({name, c_count, c_g, c_a});
    }
    file.close();
    std::sort(roster.begin(), roster.end(), rankByMVP);

    // 2. READ MATCHES AND COMPUTE LIVE STANDINGS (W/L Records)
    std::vector<MatchRecord> match_history;
    std::map<std::string, PerformanceStats> stats_map;
    
    // Seed initial roster list in map so everyone shows up
    std::vector<std::string> official_names = {
        "ZIRIWA Patrick", "RWEMA Kyle", "GWIZA Dave", "Owen King", 
        "HIRWA Davy", "MUGISHA Herve", "CHANCE Prince", "CHRIS Isange","KENNY SHALOM","MAOMBI DAVID","NYIRISHEMA PACCY","NIYIKIZA FLORIS"
    };
    for(const auto& name : official_names) { stats_map[name].name = name; }

    std::ifstream winFile("winners.txt"); std::ifstream loseFile("losers.txt");
    std::string wLine, lLine;
    while (std::getline(winFile, wLine) && std::getline(loseFile, lLine)) {
        if (wLine.empty() || lLine.empty()) continue;
        std::stringstream wSS(wLine); std::string wName, wGoalsStr;
        std::getline(wSS, wName, ','); std::getline(wSS, wGoalsStr, ',');
        std::stringstream lSS(lLine); std::string lName, lGoalsStr;
        std::getline(lSS, lName, ','); std::getline(lSS, lGoalsStr, ',');

        int wg = 0, lg = 0;
        try { if (!wGoalsStr.empty()) wg = std::stoi(wGoalsStr); } catch(...) {}
        try { if (!lGoalsStr.empty()) lg = std::stoi(lGoalsStr); } catch(...) {}

        match_history.push_back({wName, wg, lName, lg});

        // Compute performance metrics dynamically
        stats_map[wName].wins += 1;
        stats_map[wName].total_goals += wg;
        stats_map[lName].losses += 1;
        stats_map[lName].total_goals += lg;
    }
    winFile.close(); loseFile.close();

    std::vector<PerformanceStats> global_standings;
    for (auto& pair : stats_map) {
        int total_games = pair.second.wins + pair.second.losses;
        if (total_games > 0) {
            pair.second.win_percentage = (static_cast<double>(pair.second.wins) / total_games) * 100.0;
        } else {
            pair.second.win_percentage = 0.0;
        }
        global_standings.push_back(pair.second);
    }
    // Sort global standings by overall tournament goals for the Golden Boot table!
    std::sort(global_standings.begin(), global_standings.end(), rankByGoals);

    // HTML Rendering Output
    std::cout << "<html><head><meta charset='UTF-8'><title>Esports Tournament Arena</title><link rel='stylesheet' href='../stats.css'></head><body>";
    std::cout << "<div class='stats-container' style='background: rgba(0,0,0,0.85); min-height:100vh; padding-bottom: 50px;'>";
    
    std::cout << "<h1 style='color: #FF1493; font-size: 38px; text-shadow: 2px 2px 10px #000; padding-top:25px; margin:0;'>🏆 TOURNAMENT CHAMPIONSHIP STANDINGS 🏆</h1>";
    std::cout << "<p style='color: #aaa; font-size:16px;'>Live Updates & Interactive Performance Logs</p>";
    
    // TAB LAYOUT SYSTEM - TWO PREMIUM STANDINGS TABLES SIDE BY SIDE or STACKED
    std::cout << "<div style='margin: 30px auto; width: 95%; max-width: 1000px;'>";
    
    // TABLE 1: GLOBAL GOLDEN BOOT & PERFORMANCE RECORDS
    std::cout << "  <h2 style='color: #00ffcc; text-align: left; border-bottom: 2px solid #333; padding-bottom:5px;'>⚽ GOLDEN BOOT & LEAGUE PERFORMANCE</h2>";
    std::cout << "  <table class='leaderboard-table' style='margin-bottom: 40px;'>";
    std::cout << "    <tr><th>RANK</th><th>PLAYER NAME</th><th>MATCHES WON</th><th>MATCHES LOST</th><th>TOTAL GOALS ⚡</th><th>WIN RATIO</th></tr>";
    int gRank = 1;
    for(const auto& player : global_standings) {
        std::cout << "    <tr>";
        std::cout << "      <td style='color:#00ffcc; font-weight:bold;'>#" << gRank++ << "</td>";
        std::cout << "      <td style='color:white; font-weight:bold;'>" << player.name << "</td>";
        std::cout << "      <td style='color:#28a745; font-weight:bold;'>" << player.wins << " W</td>";
        std::cout << "      <td style='color:#dc3545; font-weight:bold;'>" << player.losses << " L</td>";
        std::cout << "      <td style='color:yellow; font-weight:bold; font-size:18px;'>" << player.total_goals << " Goals</td>";
        std::cout << "      <td style='color:cyan; font-weight:bold;'>" << static_cast<int>(player.win_percentage) << "%</td>";
        std::cout << "    </tr>";
    }
    std::cout << "  </table>";

    // TABLE 2: MOTM ACCUMULATION CROWN
    std::cout << "  <h2 style='color: #FF1493; text-align: left; border-bottom: 2px solid #333; padding-bottom:5px;'>⭐ MVP TITLES & PERFORMANCE STANDOUTS</h2>";
    std::cout << "  <table class='leaderboard-table' style='margin-bottom: 40px;'>";
    std::cout << "    <tr><th>RANK</th><th>PLAYER NAME</th><th>🥇 MOTM AWARDS</th><th>MVP GOALS</th><th>MVP ASSISTS</th></tr>";
    int mRank = 1;
    for (const auto& player : roster) {
        std::cout << "    <tr>";
        std::cout << "      <td style='color:#FF1493; font-weight:bold;'>#" << mRank++ << "</td>";
        std::cout << "      <td style='font-weight:bold; color:white;'>" << player.name << "</td>";
        std::cout << "      <td style='color:cyan; font-weight:bold; font-size:18px;'> " << player.motm_count << " Match MVP</td>";
        std::cout << "      <td style='color:#28a745;'> " << player.goals << "</td>";
        std::cout << "      <td style='color:#ffc107;'> " << player.assists << "</td>";
        std::cout << "    </tr>";
    }
    std::cout << "  </table>";
    std::cout << "</div>";

    // --- TIMELINE FEED: RECENT MATCHES ---
    std::cout << "<div style='margin: 40px auto; width: 90%; max-width: 900px;'>";
    std::cout << "  <h2 style='color: yellow; border-bottom: 2px solid #333; padding-bottom: 8px; text-align: left; letter-spacing: 1px;'>🏁 LIVE MATCH TIMELINE FEED</h2>";
    if (match_history.empty()) {
        std::cout << "  <p style='color: #888; text-align: left; font-style: italic;'>No fixtures completed in this session window yet.</p>";
    } else {
        for (auto it = match_history.rbegin(); it != match_history.rend(); ++it) {
            std::cout << "  <div style='background: rgba(255,255,255,0.03); border-left: 4px solid #00ffcc; margin-bottom: 12px; padding: 15px 20px; border-radius: 0 8px 8px 0; display: flex; justify-content: space-between; align-items: center;'>";
            std::cout << "    <div style='text-align: left; flex: 1;'><span style='color: #28a745; font-weight: bold;'>🏆 " << it->winner_name << "</span></div>";
            std::cout << "    <div style='background: #111; padding: 6px 16px; border-radius: 20px; font-weight: bold; font-size: 16px; border: 1px solid #333; color: yellow; min-width: 60px; text-align: center;'>" << it->winner_goals << " — " << it->loser_goals << "</div>";
            std::cout << "    <div style='text-align: right; flex: 1;'><span style='color: #dc3545; font-weight: bold;'> " << it->loser_name << " ❌</span></div>";
            std::cout << "  </div>";
        }
    }
    std::cout << "</div>";

    // --- FOOTER CONTROLS ---
    std::cout << "<div style='margin-top:30px; display:flex; gap:20px; justify-content:center;'>";
    std::cout << "  <a href='../index.html' style='color: #aaa; text-decoration: none; font-weight: bold; border:1px solid #444; padding:10px 20px; border-radius:4px;'>Logout / Return Home</a>";
    if (username == "Admin") {
        std::cout << "  <a href='leaderboard.cgi?username=" << username << "&action=reset' onclick=\"return confirm('Completely reset all tournament progress tables?');\" style='color: white; background-color:#dc3545; text-decoration: none; font-weight: bold; padding:10px 20px; border-radius:4px;'>⚠️ RESET DATABASE</a>";
    }
    std::cout << "</div>";

    std::cout << "</div></body></html>";
    return 0;
}
