cmake_minimum_required(VERSION 3.16)

project(SDT)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost
find_package(Boost REQUIRED)
find_package(FLTK REQUIRED)

add_executable(SDT
    src/main.cpp
    src/relay_server.cpp
    src/client.cpp
)

target_include_directories(SDT PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(SDT ${FLTK_LIBRARIES})
