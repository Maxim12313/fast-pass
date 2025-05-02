cmake_minimum_required(VERSION 3.22)
project(CoolGame)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wno-sign-compare -Wfloat-equal -fsanitize=undefined -Wno-switch -Wno-format -DDEBUG")

include_directories(include)

add_executable(app.out src/app.cpp)
add_executable(tests.out src/tests.cpp)

target_link_libraries(app.out raylib)
target_link_libraries(tests.out raylib)

target_link_libraries(app.out enet)
target_link_libraries(tests.out enet)
