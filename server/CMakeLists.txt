cmake_minimum_required(VERSION 3.14.4)

add_executable(r-type_server
    ../common/src/EntityLoader.cpp
    src/main.cpp
    src/Network.cpp
    src/Server.cpp
    src/UDPServer.cpp
    src/ParseRequest.cpp
    src/UDPGame.cpp
    src/Player.cpp
)

target_compile_options(r-type_server PUBLIC -W -Wextra -Wall)
target_link_libraries(r-type_server ${CMAKE_DL_LIBS} ${CONAN_LIBS} boost_system)
# target_link_libraries(r-type_server common ${CONAN_LIBS} boost_system)
