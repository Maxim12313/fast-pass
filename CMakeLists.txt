cmake_minimum_required(VERSION 3.22)
project(CoolGame)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wno-sign-compare -Wfloat-equal -fsanitize=undefined -Wno-switch -Wno-format")

include_directories(include)

add_executable(client.out src/client_app.cpp)
add_executable(server.out src/server_app.cpp)
add_executable(app.out src/main.cpp)

target_link_libraries(client.out raylib)
target_link_libraries(server.out raylib)
target_link_libraries(app.out raylib)

target_link_libraries(client.out enet)
target_link_libraries(server.out enet)
target_link_libraries(app.out enet)
