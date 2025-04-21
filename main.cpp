#include <iostream>
#include <string>
#include <algorithm>  // For std::replace
#include <cstdlib>    // For getenv
#include <curl/curl.h>
#include "json.hpp"   // Include nlohmann JSON library

using json = nlohmann::json;

// Function to handle API response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void getWeather(const std::string& city, const std::string& apiKey) {
    // Replace spaces with '+' for URL encoding
    std::string formattedCity = city;
    std::replace(formattedCity.begin(), formattedCity.end(), ' ', '+');

    // Secure API request
    std::string url = "insderweatherapihere" + formattedCity + "&appid=" + apiKey + "&units=metric";

    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // Enable SSL verification
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);  // if it dosent work then debug to 0 0 instead but itll make it inseure

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "CURL request failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            try {
                json weatherData = json::parse(readBuffer);

                // Check if the API response contains an error
                if (weatherData.contains("cod") && weatherData["cod"] != 200) {
                    std::cerr << "Error: " << weatherData["message"] << std::endl;
                    return;
                }

                // Ensure valid data
                if (weatherData.contains("main") && weatherData["main"].contains("temp")) {
                    std::cout << "Weather in " << city << ":\n";
                    std::cout << "Temperature: " << weatherData["main"]["temp"] << " °C\n";
                    std::cout << "Humidity: " << weatherData["main"]["humidity"] << " %\n";
                    std::cout << "Weather: " << weatherData["weather"][0]["description"] << std::endl;
                } else {
                    std::cerr << "Error: Invalid weather data received.\n";
                }
            } catch (json::parse_error& e) {
                std::cerr << "JSON Parsing Error: " << e.what() << std::endl;
            }
        }

        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Error: Unable to initialize cURL.\n";
    }

    curl_global_cleanup();
}

int main() {
    // Use environment variable for security
    const char* apiKey = std::getenv("OPENWEATHER_API_KEY");
    std::string apiKeyStr;

    if (!apiKey) {
        std::cout << "Warning: API key not set in environment. Enter your API key manually: ";
        std::getline(std::cin, apiKeyStr);
        if (apiKeyStr.empty()) {
            std::cerr << "Error: No API key provided. Exiting.\n";
            return 1;
        }
    } else {
        apiKeyStr = apiKey;
    }

    std::string city;
    do {
        std::cout << "Enter the city name: ";
        std::getline(std::cin, city);

        if (city.empty()) {
            std::cerr << "Error: City name cannot be empty. Please enter a valid city.\n";
        }
    } while (city.empty()); // Keep asking until a valid city is entered.

    getWeather(city, apiKeyStr);

    return 0;
}
