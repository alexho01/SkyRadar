# 🌦️ C++ Weather API Client

This project is a **C++ Weather API Client** that retrieves **real-time weather data** for any city using the [OpenWeather API](https://openweathermap.org/api). It ensures secure, reliable, and user-friendly access to weather information with robust error handling.

---

## 🔑 Key Features
- **Secure API Key Management** – Stores API keys in environment variables, with manual input as a fallback  
- **City Name Formatting** – Converts user input into URL-safe formats for API requests  
- **Secure HTTPS Requests** – Utilizes **libcurl** for reliable API communication  
- **JSON Parsing** – Processes responses using the **nlohmann JSON library**  
- **Clean Output** – Displays temperature (°C), humidity, and descriptive weather conditions in a user friendly format  
- **Robust Error Handling** – Gracefully manages API failures, parsing errors, and invalid inputs with informative feedback  

SkyRadar Example:

Input API key then Select a city name:


![image](https://github.com/user-attachments/assets/6353c645-8003-4633-9d5b-27a92d1d973a)

real-life comparison:


![image](https://github.com/user-attachments/assets/d691694b-5a27-4dda-aa9b-ad80128b1d09)





Another Example:

City Input New York:


![image](https://github.com/user-attachments/assets/5e5128f9-3469-4794-bde6-0d537e82fd7e)

real-life comparison:


![image](https://github.com/user-attachments/assets/8f3b2c84-6f27-4b2f-bfdb-7195462cefb1)
