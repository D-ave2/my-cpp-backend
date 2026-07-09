#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    std::cout << "Content-type:text/html\r\n\r\n";

    // Extract login name context
    std::string username = "Unknown_User";
    char* queryString = std::getenv("QUERY_STRING");
    if (queryString != nullptr) {
        std::string query(queryString);
        size_t pos = query.find("username=");
        if (pos != std::string::npos) {
            username = query.substr(pos + 9);
        }
    }

    std::cout << "<html><head><title>Match Desk</title><link rel='stylesheet' href='../stats.css'></head><body>";
    std::cout << "<div class='stats-container'>";
    
    std::cout << "<h1 style='color: #FF1493; font-size: 32px; text-shadow: 2px 2px 6px #000;'>🎮 eFOOTBALL 26 MATCH GATEWAY 🎮</h1>";
    std::cout << "<p style='color: yellow;'>Active Session User: " << username << "</p>";

    // DEEP LINK CONTAINER
    std::cout << "<div style='margin: 40px auto; width: 85%; max-width: 500px; background: rgba(0,0,0,0.85); padding: 20px; border-radius: 12px; border: 1px solid #FF1493;'>";
    std::cout << "  <h3>1. RUN CONSOLE APPARATUS</h3>";
    std::cout << "  <button onclick='fireDeepLink()' class='to-game-btn' style='border:none; cursor:pointer; margin-bottom:15px;'>LAUNCH eFOOTBALL 26</button>";
    std::cout << "  <div id='fallback-zone' style='display:none; margin-top:10px; background: rgba(255,20,147,0.1); padding: 10px; border-radius: 6px;'>";
    std::cout << "     <p style='color:#ffc107; margin:0 0 5px 0;'>Game did not open automatically?</p>";
    std::cout << "     <a href='https://www.konami.com/efootball/' target='_blank' style='color:#fff; font-weight:bold; text-decoration:underline;'>Download Game First Here</a>";
    std::cout << "  </div>";
    std::cout << "</div>";

    // MATCH REPORT GOAL FORM
    std::cout << "<div style='margin: 40px auto; width: 85%; max-width: 500px; background: rgba(0,0,0,0.85); padding: 25px; border-radius: 12px; border: 2px solid #28a745; text-align:left;'>";
    std::cout << "  <h3 style='color: #28a745; margin-top:0; text-align:center; text-transform:uppercase;'>📝 Report Match Metrics</h3>";
    std::cout << "  <form action='/cgi-bin/process_report.cgi' method='POST'>";
    std::cout << "    <input type='hidden' name='username' value='" << username << "'>";
    
    std::cout << "    <label style='display:block; margin-bottom:5px; font-weight:bold;'>Player Name:</label>";
    std::cout << "    <input type='text' name='player_name' placeholder='Type name exactly...' required style='width:100%; padding:10px; border-radius:6px; border:1px solid #ccc; box-sizing:border-box; margin-bottom:15px;'>";
    
    std::cout << "    <label style='display:block; margin-bottom:5px; font-weight:bold;'>Match Goals Scored:</label>";
    std::cout << "    <input type='number' name='goals' min='0' value='0' required style='width:100%; padding:10px; border-radius:6px; border:1px solid #ccc; box-sizing:border-box; margin-bottom:15px;'>";
    
    std::cout << "    <label style='display:block; margin-bottom:5px; font-weight:bold;'>Match Assists Made:</label>";
    std::cout << "    <input type='number' name='assists' min='0' value='0' required style='width:100%; padding:10px; border-radius:6px; border:1px solid #ccc; box-sizing:border-box; margin-bottom:20px;'>";
    
    std::cout << "    <button type='submit' style='background:#28a745; color:white; font-weight:bold; font-size:16px; border:none; padding:12px; width:100%; border-radius:6px; cursor:pointer;'>SUBMIT TO SCOREBOARD</button>";
    std::cout << "  </form>";
    std::cout << "</div>";

    // JAVASCRIPT EXECUTING REDIRECTION INTENTS
    std::cout << "<script>";
    std::cout << "function fireDeepLink() {";
    std::cout << "    document.getElementById('fallback-zone').style.display = 'block';";
    std::cout << "    window.location.href = 'jp.konami.pesam://';"; // Official eFootball Mobile system scheme pointer URI
    std::cout << "    setTimeout(function() {";
    std::cout << "        window.location.href = 'efootball://';"; // Generic PC/Desktop custom registry system scheme shortcut fallback
    std::cout << "    }, 500);";
    std::cout << "}";
    std::cout << "</script>";

    std::cout << "</div></body></html>";
    return 0;
}
