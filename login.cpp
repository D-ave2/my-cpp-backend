#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>

// Helper function to decode URL-encoded form strings
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

// Function checking if username belongs to the official team list
bool isAllowedPlayer(const std::string& user, const std::string& pass) {
    // Official Player list array matching your registration system
    std::vector<std::string> players = {
        "ZIRIWA Patrick", "RWEMA Kyle", "GWIZA Dave", "Owen King", 
        "HIRWA Davy", "MUGISHA Herve", "CHANCE Prince", "CHRIS Isange", "KENNY SHALOM" , "NYIRISHEMA PACCY", "MAOMBI DAVID", "NIYIKIZA FLORIS"
    };
    
    // Default test password for players
    if (pass != "player123") return false;

    for (const auto& player : players) {
        if (player == user) return true;
    }
    return false;
}

int main() {
    std::string username = "";
    std::string password = "";
    
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
            
            if (key == "username") username = val;
            if (key == "password") password = val;
        }
    }

    std::cout << "Content-type:text/html; charset=UTF-8\r\n\r\n";
    // NEW CODE (Replace Line 61):
    std::cout << "<html><head><meta charset='UTF-8'><title>Verification Portal</title><link rel='stylesheet' href='https://my-first-web-zhxa.onrender.com'></head><body>";


    std::cout << "<div class='stats-container' style='background: rgba(0,0,0,0.9); min-height: 100vh; padding-top: 50px;'>";
    std::cout << "<div style='margin: 30px auto; width: 85%; max-width: 500px; background: #111; padding: 30px; border-radius: 12px; border: 2px solid #FF1493; text-align: center; box-shadow: 0 4px 15px rgba(0,0,0,0.5);'>";

    // ROLE SEGREGATION FLOW
    if (username == "Admin" && password == "AdminPass123!") {
        // 1. NEUTRAL REFEREE / ADMIN ACCESS 
        std::cout << "  <h1 style='color: #28a745; font-size: 28px; margin-top:0;'>🔒 OFFICIAL ACCESS GRANTED</h1>";
        std::cout << "  <p style='color: #aaa; font-size:16px; margin-bottom:25px;'>Welcome back, Tournament Director <strong>" << username << "</strong>.</p>";
        std::cout << "  <div style='margin: 20px 0;'>";
        // NEW CODE (Replace Line 69 - Keep your style settings exactly as they are):
        std::cout << "    <a href='https://my-cpp-backend-api.onrender.com" << username << "' style='display:block; background-color: #28a745; color: white; padding: 15px; text-decoration: none; font-size: 18px; font-weight: bold; border-radius: 6px; text-transform:uppercase; box-shadow: 0 3px 6px rgba(0,0,0,0.2);'>📝 Launch Match Report Room</a>";


        std::cout << "  </div>";
    } 
    else if (isAllowedPlayer(username, password)) {
        // 2. READ-ONLY PLAYER VIEWER ACCESS
        std::cout << "  <h1 style='color: cyan; font-size: 28px; margin-top:0;'>🔓 PLAYER ACCESS GRANTED</h1>";
        std::cout << "  <p style='color: #aaa; font-size:16px; margin-bottom:25px;'>Welcome, Player <strong>" << username << "</strong>.</p>";
        std::cout << "  <div style='margin: 20px 0;'>";
        // CURRENT CODE (Line 76):
        // NEW CODE (Replace Line 76 - Keep your style settings exactly as they are):
        std::cout << "    <a href='https://my-cpp-backend-api.onrender.com" << username << "' style='display:block; background-color: #007bff; color: white; padding: 15px; text-decoration: none; font-size: 18px; font-weight: bold; border-radius: 6px; text-transform:uppercase; box-shadow: 0 3px 6px rgba(0,0,0,0.2);'>📊 View Live Leaderboard & Feed</a>";


        std::cout << "  </div>";
    } 
    else {
        // 3. INVALID CREDENTIALS DROP (Fixed and fully closed)
        std::cout << "  <h1 style='color: #dc3545; font-size: 28px; margin-top:0;'>❌ AUTHENTICATION DENIED</h1>";
        std::cout << "  <p style='color: #eee; font-size:15px; line-height:1.5; margin: 15px 0 25px 0;'>The username or password combination entered is incorrect, or you are unauthorized to access this tournament tier.</p>";
        // NEW CODE (Replace Line 82):
std::cout << "  <a href='https://my-first-web-zhxa.onrender.com' style='color: yellow; text-decoration: none; font-weight: bold; border: 1px solid yellow; padding: 8px 20px; border-radius: 4px; display: inline-block;'>← Try Again</a>";

    }

    std::cout << "</div>";
    std::cout << "</div></body></html>";
    return 0;
}
