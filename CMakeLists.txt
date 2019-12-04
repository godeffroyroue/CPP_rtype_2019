cmake_minimum_required(VERSION 3.14.4)

project(RType)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
endif()

set(THREADS_PREFER_PTHREADS_FLAG ON)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

include_directories(common/include)
include_directories(client/include)
include_directories(client/menu/include)
include_directories(client/game/network/include)
include_directories(client/game/graphics/include)
include_directories(client/game/spec/include)
include_directories(client/game/physic/include)
include_directories(client/game/entity/include)
include_directories(client/game/entityManager/include)
include_directories(client/game/gameGestion/include)
include_directories(server/include)

subdirs(common)
subdirs(client)
subdirs(server)

# ----------------- [ Miscellaneous] ------------------


# INSTALL(TARGETS r-type_client DESTINATION ${RType_SOURCE_DIR}/)
# INSTALL(TARGETS r-type_server DESTINATION ${RType_SOURCE_DIR}/)