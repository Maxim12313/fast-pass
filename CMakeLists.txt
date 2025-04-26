cmake_minimum_required(VERSION 3.22)
project(CoolGame)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wno-sign-compare -Wfloat-equal -fsanitize=undefined")

include_directories(include)

file(GLOB SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/main.cpp")

message(STATUS "Source files: ${SOURCE_FILES}")

add_executable(app.exe src/main.cpp ${SOURCE_FILES})

target_link_libraries(app.exe raylib)
