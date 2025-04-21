cmake_minimum_required(VERSION 3.16)
project(SkyRadar)

set(CMAKE_CXX_STANDARD 17)

# Set the path to your extracted Curl directory
set(CURL_DIR "${CMAKE_SOURCE_DIR}/curl")

# Include Curl headers
include_directories(${CURL_DIR}/include)

# Link Curl library properly
find_library(CURL_LIB NAMES curl PATHS ${CURL_DIR}/lib)

# Include nlohmann JSON headers
include_directories("${CMAKE_SOURCE_DIR}/nlohmann_json")

# Create the executable
add_executable(SkyRadar main.cpp)

# Link external libraries correctly
target_link_libraries(SkyRadar PRIVATE ${CURL_LIB} ws2_32 crypt32)
