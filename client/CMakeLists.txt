cmake_minimum_required(VERSION 3.14.4)

add_executable(r-type_client
    src/main.cpp

    ../common/src/EntityLoader.cpp
    menu/src/SFMLMenu.cpp
    game/network/src/SFMLNetwork.cpp
    game/network/src/ANetwork.cpp
    game/graphics/src/SFMLGraphics.cpp
    game/spec/src/specification.cpp
    game/physic/src/SFMLPhysic.cpp
    game/entity/src/entity.cpp
    game/entityManager/src/entityManager.cpp
    game/gameGestion/src/SFMLGame.cpp





)


target_link_libraries(r-type_client ${CMAKE_DL_LIBS} ${CONAN_LIBS})
# target_link_libraries(r-type_client common ${CONAN_LIBS})
