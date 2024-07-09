cmake_minimum_required(VERSION 3.10)
project(BookRecommendation)

set(CMAKE_CXX_STANDARD 17)

# Add the following lines to help CMake find MySQL
set(CMAKE_PREFIX_PATH "/usr/local/opt/mysql-client")
find_package(MySQL REQUIRED)

include_directories(${MYSQL_INCLUDE_DIR})
add_executable(BookRecommendation src/main.cpp src/recommendation.cpp)
target_link_libraries(BookRecommendation ${MYSQL_LIBRARIES})
