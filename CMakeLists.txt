cmake_minimum_required(VERSION 3.14)

project(GetPathWaypoint VERSION 1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(CURL REQUIRED)

find_path(CURLPP_INCLUDE_DIR curlpp/Easy.hpp)
find_library(CURLPP_LIBRARY curlpp)

include_directories(include)

add_executable(GetPathWaypoint main.cpp)

target_include_directories(GetPathWaypoint PRIVATE ${CURLPP_INCLUDE_DIR})

target_link_libraries(GetPathWaypoint PRIVATE CURL::libcurl ${CURLPP_LIBRARY})
