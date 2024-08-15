cmake_minimum_required(VERSION 3.21)
project(GPTManager)

set(CMAKE_CXX_STANDARD 17)

set(CURL_INCLUDE_DIR "C:/Users/protr/Downloads/curl-8.5.0_1-win64-mingw/curl-8.5.0_1-win64-mingw/include")
set(CURL_LIBRARY "C:/Users/protr/Downloads/curl-8.5.0_1-win64-mingw/curl-8.5.0_1-win64-mingw/lib/libcurl.a")

add_executable(GPTManager main.cpp Model.cpp ModelManager.cpp Directory.cpp
        APIKey.cpp
        APIKey.h)

target_include_directories(GPTManager PRIVATE ${CURL_INCLUDE_DIR})

# Link against libcurl
target_link_libraries(GPTManager PRIVATE ${CURL_LIBRARY})

# Add other necessary libraries
target_link_libraries(GPTManager PRIVATE -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32)