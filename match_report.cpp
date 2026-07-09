#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

int main() {
    std::cout << "Content-type:text/html; charset=UTF-8\r\n\r\n";

    std::string username = "";
    char* queryString = std::getenv("QUERY_STRING");
    if (queryString != nullptr) {
        std::string query(queryString);
        size_t pos = query.find("username=");
        if (pos != std::string::npos) { username = query.substr(pos + 9); }
    }

    // 100% STRICT ADMIN LOCK: If the URL string doesn't read exactly "Admin", drop execution
    if (username != "Admin") {
        std::cout << "<html><head><title>Access Denied</title><link rel='stylesheet' href='https://my-first-web-zhxa.onrender.com'></head><body>";

        std::cout << "<div class='stats-container' style='padding-top:100px;'>";
        std::cout << "  <div style='background:#111; padding:40px; border-radius:12px; border:3px solid red; max-width:500px; margin:0 auto; text-align:center;'>";
        std::cout << "    <h1 style='color:red; margin-top:0;'>🚫 100% ACCESS DENIED</h1>";
        std::cout << "    <p style='color:white; font-size:16px;'>Players are completely banned from viewing or modifying this administrative reporting page.</p>";
        std::cout << "    <br><a href='https://my-first-web-zhxa.onrender.com' style='color:yellow; text-decoration:none; font-weight:bold;'>← Return to Safety</a>";

        std::cout << "  </div>";
        std::cout << "</div></body></html>";
        return 0; // Kills the script right here
    }

    // Official list
    std::vector<std::string> roster = {
        "ZIRIWA Patrick", "RWEMA Kyle", "GWIZA Dave", "Owen King", 
        "HIRWA Davy", "MUGISHA Herve", "CHANCE Prince", "CHRIS Isange","KENNY SHALOM","NYIRISHEMA PACCY","MAOMBI DAVID","NIYIKIZA FLORIS"
    };

    // The rest of your functional form code goes here...
    std::cout << "<html><head><meta charset='UTF-8'><title>Match Sheet Input</title><link rel='stylesheet' href='https://my-first-web-zhxa.onrender.com'>";

    std::cout << "<script>"
                 "function validateForm() {"
                 "    var wg = parseInt(document.getElementsByName('winner_goals')[0].value) || 0;"
                 "    var lg = parseInt(document.getElementsByName('loser_goals')[0].value) || 0;"
                 "    var mg = parseInt(document.getElementsByName('motm_goals')[0].value) || 0;"
                 "    var wName = document.getElementsByName('winner_name')[0].value;"
                 "    var lName = document.getElementsByName('loser_name')[0].value;"
                 "    var mName = document.getElementsByName('motm_name')[0].value;"
                 "    if (wg < lg) { alert('❌ Winner cannot have fewer goals than Loser!'); return false; }"
                 "    if (wName === lName) { alert('❌ A player cannot match against themselves!'); return false; }"
                 "    return true;"
                 "}"
                 "</script></head><body>";
                 
    std::cout << "<div class='stats-container'>";
    std::cout << "  <div style='margin:10px auto; width:90%; max-width:650px; background:rgba(0,0,0,0.95); padding:25px; border-radius:12px; border:2px solid #FF1493;'>";
    std::cout << "    <h2 style='color:#FF1493; text-align:center; margin-top:0;'>📝 ADMINISTRATIVE CONTROL CARD</h2>";
    std::cout << "    <form action='https://my-cpp-backend-api.onrender.com' method='POST' onsubmit='return validateForm();'>";

    std::cout << "      <input type='hidden' name='submitter' value='Admin'>";
    
    // Form Dropdowns
    std::cout << "      <label style='color:cyan;'>🏆 WINNER:</label>";
    std::cout << "      <select name='winner_name' style='width:100%; padding:10px; margin-bottom:10px; background:#222; color:white;' required><option value=''>-- Select --</option>";
    for(auto& p : roster) std::cout << "<option value='"<<p<<"'>"<<p<<"</option>";
    std::cout << "      </select><input type='number' name='winner_goals' class='report-input' min='0' value='0' required><br><br>";

    std::cout << "      <label style='color:#dc3545;'>❌ LOSER:</label>";
    std::cout << "      <select name='loser_name' style='width:100%; padding:10px; margin-bottom:10px; background:#222; color:white;' required><option value=''>-- Select --</option>";
    for(auto& p : roster) std::cout << "<option value='"<<p<<"'>"<<p<<"</option>";
    std::cout << "      </select><input type='number' name='loser_goals' class='report-input' min='0' value='0' required><br><br>";

    std::cout << "      <label style='color:yellow;'>⭐ MAN OF THE MATCH:</label>";
    std::cout << "      <select name='motm_name' style='width:100%; padding:10px; margin-bottom:10px; background:#222; color:white;' required><option value=''>-- Select --</option>";
    for(auto& p : roster) std::cout << "<option value='"<<p<<"'>"<<p<<"</option>";
    std::cout << "      </select>";
    std::cout << "      <input type='number' name='motm_goals' class='report-input' min='0' value='0' placeholder='Goals' required>";
    std::cout << "      <input type='number' name='motm_assists' class='report-input' min='0' value='0' placeholder='Assists' required><br><br>";

    std::cout << "      <button type='submit' style='width:100%; background:#28a745; color:white; padding:15px; font-weight:bold;'>SUBMIT OFFICIAL MATCH DETAILS</button>";
    std::cout << "    </form>";
    std::cout << "  </div>";
    std::cout << "</div></body></html>";

    return 0;
}
