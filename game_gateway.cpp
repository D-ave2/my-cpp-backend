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

    std::cout << "<html><head><meta charset='UTF-8'><title>eFootball 26 Launcher</title><link rel='stylesheet' href='../stats.css'></head><body>";
    std::cout << "<div class='stats-container' style='background: rgba(0,0,0,0.8); min-height:100vh;'>";
    
    std::cout << "<h1 style='color: #FF1493; font-size: 34px; padding-top: 50px; text-shadow: 2px 2px 5px #000;'>🎮 INITIALIZING eFOOTBALL 26 🎮</h1>";
    std::cout << "<p style='font-size: 18px; color: #eee;'>Standby, " << username << "... Dispatching Engine boot sequences.</p>";

    // DESKTOP DOWNLOAD CORNER
    std::cout << "<div style='margin: 30px auto; max-width: 550px; background: rgba(15,15,15,0.9); padding: 20px; border-radius: 12px; border: 1px solid #007edd; text-align:center;'>";
    std::cout << "  <p style='color: #007edd; font-weight:bold; margin-top:0;'>💻 DESKTOP SYSTEMS PLATFORM</p>";
    std::cout << "  <a href='https://store.steampowered.com/app/1665460/eFootball/' target='_blank' style='background: #007edd; color: white; padding: 10px 18px; display: inline-block; text-decoration: none; border-radius: 4px; font-weight: bold; font-size:14px;'>Download eFootball on Steam</a>";
    std::cout << "</div>";

    // MOBILE PHONE ACCESS POINT (Play Store & App Store support)
    std::cout << "<div style='margin: 30px auto; max-width: 550px; background: rgba(15,15,15,0.9); padding: 20px; border-radius: 12px; border: 1px solid #28a745; text-align:center;'>";
    std::cout << "  <p style='color: #28a745; font-weight:bold; margin-top:0;'>📱 MOBILE SMARTPHONE PLATFORMS</p>";
    std::cout << "  <p style='font-size:14px; color:#bbb; margin-bottom:15px;'>Playing on a phone? Fire up the app store setup linkages below:</p>";
    std::cout << "  <a href='https://play.google.com/store/apps/details?id=jp.konami.pesam' target='_blank' style='background: #28a745; color: white; padding: 10px 15px; display: inline-block; text-decoration: none; border-radius: 4px; font-weight: bold; font-size:13px; margin-right:10px;'>Google Play Store (Android)</a>";
    std::cout << "  <a href='https://apps.apple.com/us/app/efootball/id1117270713' target='_blank' style='background: #fff; color: #000; padding: 10px 15px; display: inline-block; text-decoration: none; border-radius: 4px; font-weight: bold; font-size:13px;'>Apple App Store (iOS)</a>";
    std::cout << "</div>";

    // PROGRESSION ACTION NAVIGATION BUTTON
    std::cout << "<div style='margin-top: 50px;'>";
    std::cout << "  <h3 style='color: yellow;'>Finished playing your tournament fixture?</h3>";
    std::cout << "  <a href='match_report.cgi?username=" << username << "' style='background-color: #FF1493; color: white; padding: 14px 40px; text-decoration: none; font-weight: bold; font-size:18px; border-radius: 6px; display: inline-block; box-shadow: 0 4px 10px rgba(255,20,147,0.4);'>GO TO REPORT ROOM →</a>";
    std::cout << "</div>";

    // AUTOMATED SYSTEM APP LAUNCH SCHEME TRIGGER
    std::cout << "<script>";
    std::cout << "window.onload = function() {";
    std::cout << "    if (/Android|iPhone|iPad|iPod/i.test(navigator.userAgent)) {";
    std::cout << "        window.location.href = 'pesmobile://';"; // Launches the native mobile app on device
    std::cout << "    } else {";
    std::cout << "        window.location.href = 'steam://rungameid/1665460';"; // Launches desktop build via Steam
    std::cout << "    }";
    std::cout << "};";
    std::cout << "</script>";

    std::cout << "</div></body></html>";
    return 0;
}
