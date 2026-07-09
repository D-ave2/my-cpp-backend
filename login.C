#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

// Helper function to decode URL formatting (e.g., turning '+' back into spaces)
std::string urlDecode(std::string str) {
    std::string ret;
    char ch;
    int i;
    for (size_t p = 0; p < str.length(); p++) {
        if (str[p] == '+') {
            ret += ' ';
        } else if (str[p] == '%') {
            sscanf(str.substr(p + 1, 2).c_str(), "%x", &i);
            ch = static_cast<char>(i);
            ret += ch;
            p += 2;
        } else {
            ret += str[p];
        }
    }
    return ret;
}

int main() {
    // 1. Tell the browser we are rendering an HTML response page
    std::cout << "Content-type:text/html\r\n\r\n";
    std::cout << "<html><head><title>Access Control</title></head><body style='background:black; color:white; text-align:center; font-family:sans-serif; margin-top:100px;'>";


    // 2. Allowed users list
    std::vector<std::string> allowed_users = {
        "ZIRIWA Patrick", "RWEMA Kyle", "GWIZA Dave", "Owen King", 
        "HIRWA Davy", "MUGISHA Herve", "CHANCE Prince", "CHRIS Isange", 
        "GOD Seba", "KENNY Shalom", "NIYIKIZA Floris", "DALTON RUBANGURA", "PACCY SHEMA"
    };

    // 3. Get form data via Standard Input
    char* contentLengthStr = std::getenv("CONTENT_LENGTH");
    if (contentLengthStr != nullptr) {
        int length = std::stoi(contentLengthStr);
        std::string rawData = "";
        char ch;
        for (int i = 0; i < length; ++i) {
            std::cin.get(ch);
            rawData += ch;
        }

        // rawData looks like: username=ZIRIWA+Patrick&password=SOCCER_LOVERS
        std::string userParam = "username=";
        std::string passParam = "password=";
        
        size_t userPos = rawData.find(userParam);
        size_t passPos = rawData.find(passParam);

        if (userPos != std::string::npos && passPos != std::string::npos) {
            // Extract and clean the Username
            size_t userStart = userPos + userParam.length();
            std::string rawUser = rawData.substr(userStart, passPos - userStart - 1);
            std::string inputUser = urlDecode(rawUser);

            // Extract and clean the Password
            size_t passStart = passPos + passParam.length();
            std::string rawPass = rawData.substr(passStart);
            std::string inputPass = urlDecode(rawPass);

            // 4. Verification Logic
            bool userFound = false;
            for (const auto& user : allowed_users) {
                if (inputUser == user) {
                    userFound = true;
                    break;
                }
            }

            if (userFound && inputPass == "SOCCER_LOVERS") {
                // Successful Access Screen
                std::cout << "<h1 style='color: #FF1493;'>ACCESS GRANTED</h1>";
                std::cout << "<h2>Welcome to the Room, " << inputUser << "!</h2>";
                std::cout << "<p>You have unlocked the soccer lovers portal.</p>";
		
		std::cout << "<br><br><br>";
        // NEW CODE (Replace Line 84):
        // NEW CODE (Replace Line 85 with this):
std::cout << "<a href='https://my-first-web-zhxa.onrender.com" << inputUser << "' style='background-color: #28a745; color: white; padding: 15px 35px; text-decoration: none; font-size: 18px; font-weight: bold; border-radius: 8px; display: inline-block;'>NEXT</a>";
            } else {
                // Denied Access Screen
                std::cout << "<h1 style='color: red;'>ACCESS DENIED</h1>";
                std::cout << "<p>Invalid Credentials or unauthorized user.</p>";
                // NEW CODE (Replace Line 90):
std::cout << "<br><a href='https://my-first-web-zhxa.onrender.com' style='color:yellow;'>Try Again</a>";

            }
        }
    } else {
        std::cout << "<h1>System Error: No input data detected.</h1>";
    }

    std::cout << "</body></html>";
    return 0;
}
