#При компиляции на Linux могут возникнуть проблемы, необходимо удалить лишнии инструкции дял CMake здесь
cmake_minimum_required(VERSION 3.16)
project(SDT)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
#add_compile_definitions(_WIN32_WINNT=0x0A00)
find_package(Boost REQUIRED)
find_package(FLTK REQUIRED)
add_executable(SDT
    main.cpp
    src/core.cpp
    src/network.cpp
    src/interface.cpp
)
set_target_properties(SDT PROPERTIES LINK_FLAGS "-mwindows")
target_include_directories(SDT PRIVATE include)
target_include_directories(SDT PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(SDT 
    ${FLTK_LIBRARIES} 
    ws2_32
)
