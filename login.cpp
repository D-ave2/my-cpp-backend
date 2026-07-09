#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <sstream>

// Helper function to decode URL formatting (e.g., turning '+' back into spaces)
std::string urlDecode(std::string str) {
    std::string ret;
    char ch;
    int i;
    for (size_t p = 0; p < str.length(); p++) {
        if (str[p] == '+') {
            ret += ' ';
        } else if (str[p] == '%') {
            if (p + 2 < str.length()) {
                sscanf(str.substr(p + 1, 2).c_str(), "%x", &i);
                ch = static_cast<char>(i);
                ret += ch;
                p += 2;
            }
        } else {
            ret += str[p];
        }
    }
    return ret;
}

int main() {
    // 1. Declare CGI Headers first before any HTML content output to prevent Apache blank screens
    std::cout << "Content-type: text/html; charset=UTF-8\r\n\r\n";
    std::cout << "<html><head><meta charset='UTF-8'><title>Access Control</title></head><body style='background:black; color:white; text-align:center; font-family:sans-serif; margin-top:100px;'>";

    // 2. Allowed tournament competitors list
    std::vector<std::string> allowed_users = {
        "ZIRIWA Patrick", "RWEMA Kyle", "GWIZA Dave", "Owen King", 
        "HIRWA Davy", "MUGISHA Herve", "CHANCE Prince", "CHRIS Isange", 
        "GOD Seba", "KENNY Shalom", "NIYIKIZA Floris", "DALTON RUBANGURA", "PACCY SHEMA"
    };

    std::string inputUser = "";
    std::string inputPass = "";

    // 3. Process data incoming via Standard Input stream
    char* contentLengthStr = std::getenv("CONTENT_LENGTH");
    if (contentLengthStr != nullptr && std::string(contentLengthStr) != "0") {
        int length = 0;
        try {
            length = std::stoi(contentLengthStr);
        } catch(...) {
            length = 0;
        }

        if (length > 0) {
            std::string rawData = "";
            char ch;
            for (int i = 0; i < length; ++i) {
                if (std::cin.get(ch)) {
                    rawData += ch;
                }
            }

            std::stringstream ss(rawData);
            std::string segment;
            while (std::getline(ss, segment, '&')) {
                size_t eq = segment.find('=');
                if (eq == std::string::npos) continue;
                std::string key = segment.substr(0, eq);
                std::string val = segment.substr(eq + 1);

                if (key == "username") inputUser = urlDecode(val);
                if (key == "password") inputPass = urlDecode(val);
            }
        }
    }

    // 4. Verification Logic Execution Loop
    if (!inputUser.empty() && !inputPass.empty()) {
        
        // ADMIN / TOURNAMENT DIRECTOR ACCESS ROUTE
        if (inputUser == "Admin" && inputPass == "AdminPass123!") {
            std::cout << "<div style='margin: 30px auto; width: 85%; max-width: 500px; background: #111; padding: 30px; border-radius: 12px; border: 2px solid #28a745; text-align: center; box-shadow: 0 4px 15px rgba(0,0,0,0.5);'>";
            std::cout << "  <h1 style='color: #28a745; font-size: 28px; margin-top:0;'>🔒 OFFICIAL ACCESS GRANTED</h1>";
            std::cout << "  <p style='color: #aaa; font-size:16px; margin-bottom:25px;'>Welcome back, Tournament Director <strong>" << inputUser << "</strong>.</p>";
            std::cout << "  <div style='margin: 20px 0;'>";
            std::cout << "    <a href='https://onrender.com" << inputUser << "' style='display:block; background-color: #28a745; color: white; padding: 15px; text-decoration: none; font-size: 18px; font-weight: bold; border-radius: 6px; text-transform:uppercase; box-shadow: 0 3px 6px rgba(0,0,0,0.2);'>📝 Launch Match Report Room</a>";
            std::cout << "  </div>";
            std::cout << "</div>";
        }
        else {
            // STANDARD PLAYER VERIFICATION CHECK
            bool userFound = false;
            for (const auto& user : allowed_users) {
                if (inputUser == user) {
                    userFound = true;
                    break;
                }
            }

            if (userFound && inputPass == "SOCCER_LOVERS") {
                // Successful Player Access Screen
                std::cout << "<div style='margin: 30px auto; width: 85%; max-width: 500px; background: #111; padding: 30px; border-radius: 12px; border: 2px solid #FF1493; text-align: center; box-shadow: 0 4px 15px rgba(0,0,0,0.5);'>";
                std::cout << "<h1 style='color: #FF1493;'>ACCESS GRANTED</h1>";
                std::cout << "<h2>Welcome to the Room, " << inputUser << "!</h2>";
                std::cout << "<p>You have unlocked the soccer lovers portal.</p>";
                std::cout << "<br><br><br>";
                std::cout << "<a href='https://onrender.com" << inputUser << "' style='background-color: #28a745; color: white; padding: 15px 35px; text-decoration: none; font-size: 18px; font-weight: bold; border-radius: 8px; display: inline-block;'>NEXT</a>";
                std::cout << "</div>";
            } else {
                // Denied Access Screen
                std::cout << "<div style='margin: 30px auto; width: 85%; max-width: 500px; background: #111; padding: 30px; border-radius: 12px; border: 2px solid #dc3545; text-align: center; box-shadow: 0 4px 15px rgba(0,0,0,0.5);'>";
                std::cout << "<h1 style='color: red;'>ACCESS DENIED</h1>";
                std::cout << "<p>Invalid Credentials or unauthorized tournament user.</p>";
                std::cout << "<br><a href='https://onrender.com' style='color:yellow; text-decoration:none; font-weight:bold;'>← Try Again</a>";
                std::cout << "</div>";
            }
        }
    } else {
        // Fallback error presentation if processing loops failed to collect variables
        std::cout << "<div style='margin: 30px auto; width: 85%; max-width: 500px; background: #111; padding: 30px; border-radius: 12px; border: 2px solid yellow; text-align: center; box-shadow: 0 4px 15px rgba(0,0,0,0.5);'>";
        std::cout << "<h1 style='color: yellow;'>System Data Intercept</h1>";
        std::cout << "<p>No data payload detected. Please ensure you are logging in from the official dashboard interface screen.</p>";
        std::cout << "<br><a href='https://onrender.com' style='color:cyan; text-decoration:none; font-weight:bold;'>Return to Sign-In Box</a>";
        std::cout << "</div>";
    }

    std::cout << "</body></html>";
    return 0;
}
