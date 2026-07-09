#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    std::cout << "Content-type:text/html; charset=UTF-8\r\n\r\n";

    std::string username = "Unknown_User";
    char* queryString = std::getenv("QUERY_STRING");
    if (queryString != nullptr) {
        std::string query(queryString);
        size_t pos = query.find("username=");
        if (pos != std::string::npos) { username = query.substr(pos + 9); }
    }

    std::cout << "<html><head><meta charset='UTF-8'><title>Tournament Brackets</title><link rel='stylesheet' href='../stats.css'></head><body>";
    std::cout << "<div class='stats-container'>";
    
    // Generous top pacing layout buffer so your bracket text is fully readable
    std::cout << "<div style='height: 480px;'></div>"; 
    
    std::cout << "<h1 style='color: #FF1493; text-shadow: 3px 3px 10px #000; font-size: 38px; margin:0;'>⚽ TOURNAMENT FIXTURES TREE ⚽</h1>";
    std::cout << "<p style='color: yellow; font-size: 18px; text-shadow: 1px 1px 4px #000;'>Locate your match pairing up above!</p>";
    
    std::cout << "<div style='height: 60px;'></div>";

    // Direct launch routing connection card
    std::cout << "<a href='game_gateway.cgi?username=" << username << "' style='background-color: #28a745; color: white; padding: 18px 50px; text-decoration: none; font-size: 20px; font-weight: bold; border-radius: 8px; display: inline-block; box-shadow: 0 6px 12px rgba(0,0,0,0.6); text-transform: uppercase;'>TO-GAME</a>";
    
    std::cout << "</div></body></html>";
    return 0;
}
