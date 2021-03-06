cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(3RDPARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty")
set(TRANSFER_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../transfer_lib")

set(CMAKE_CXX_COMPILER "g++")

project(client)

set(ALL_SOURCES
    ${SOURCE_DIR}/Application/application.cpp
    ${SOURCE_DIR}/Base_manager/base_manager.cpp
    ${SOURCE_DIR}/Event/event.cpp
    ${SOURCE_DIR}/Game_context/game_context.cpp
    ${SOURCE_DIR}/Game_context/game_context_manager.cpp
    ${SOURCE_DIR}/Input/input.cpp
    ${SOURCE_DIR}/Input/input_manager.cpp
    ${SOURCE_DIR}/Loader/loader.cpp
    ${SOURCE_DIR}/Loader/loader_manager.cpp
    ${SOURCE_DIR}/Network/network.cpp
    ${SOURCE_DIR}/Network/network_manager.cpp
    ${SOURCE_DIR}/Renderer/renderer.cpp
    ${SOURCE_DIR}/Renderer/renderer_manager.cpp
    
    ${TRANSFER_LIB_DIR}/transfer/message.cpp
    ${TRANSFER_LIB_DIR}/transfer/command.cpp
)

set(ALL_HEADERS
    ${SOURCE_DIR}/Application/
    ${SOURCE_DIR}/Base_manager/
    ${SOURCE_DIR}/Event/
    ${SOURCE_DIR}/Event_throwable/
    ${SOURCE_DIR}/Game_context/
    ${SOURCE_DIR}/Input/
    ${SOURCE_DIR}/Loader/
    ${SOURCE_DIR}/Network/
    ${SOURCE_DIR}/Renderer/
    
    ${TINYXML_DIR}/
    ${TRANSFER_LIB_DIR}/config/
    ${TRANSFER_LIB_DIR}/transfer/
)

set(TEST_INTERNAL_SOURCES
    ${SOURCE_DIR}/Input/input_test.cpp
    ${SOURCE_DIR}/Input/input_manager.cpp
    ${SOURCE_DIR}/Network/network_test.cpp
    ${SOURCE_DIR}/Network/network_manager.cpp
    ${SOURCE_DIR}/Game_context/game_context_test.cpp
    ${SOURCE_DIR}/Game_context/game_context_manager.cpp
    ${SOURCE_DIR}/Event/event.cpp
)

set(TEST_EXTERNAL_SOURCES
    ${SOURCE_DIR}/Event/event.cpp
    ${SOURCE_DIR}/Loader/loader_manager.cpp
    ${SOURCE_DIR}/Loader/loader_test.cpp
    ${SOURCE_DIR}/Renderer/renderer_manager.cpp
    ${SOURCE_DIR}/Renderer/renderer_test.cpp
)


find_package(Boost REQUIRED)
find_package(SFML COMPONENTS graphics audio network window system REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

if (Boost_FOUND AND SFML_FOUND)

    include_directories(${SFML_INCLUDE_DIR})
    include_directories(${Boost_INCLUDE_DIR})
    include_directories(${ALL_HEADERS})

    add_executable(client.out ${SOURCE_DIR}/main.cpp ${ALL_SOURCES})
    target_link_libraries(client.out ${Boost_LIBRARIES})
    target_link_libraries(client.out ${SFML_LIBRARIES})
    target_link_libraries(client.out nlohmann_json::nlohmann_json)


    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    # add_executable(client_test_internal.out ${SOURCE_DIR}/main_test_internal.cpp ${TEST_INTERNAL_SOURCES})

    # target_link_libraries(client_test_internal.out ${GTEST_LIBRARIES})
    # target_link_libraries(client_test_internal.out pthread)
    # target_link_libraries(client_test_internal.out gmock)
    # target_link_libraries(client_test_internal.out ${Boost_LIBRARIES})
    # target_link_libraries(client_test_internal.out ${SFML_LIBRARIES})

    # add_executable(client_tests_external.out ${SOURCE_DIR}/main_test_external.cpp ${TEST_EXTERNAL_SOURCES})

    # target_link_libraries(client_tests_external.out ${GTEST_LIBRARIES})
    # target_link_libraries(client_tests_external.out pthread)
    # target_link_libraries(client_tests_external.out gmock)
    # target_link_libraries(client_tests_external.out ${Boost_LIBRARIES})
    # target_link_libraries(client_tests_external.out ${SFML_LIBRARIES})

else()
    if (Boost_FOUND)
        message("Boost library was not founded. Look there: https://github.com/boostorg/boost")
    endif()
    if (SFML_FOUND)
        message("SFML library was not founded. Look there: https://github.com/SFML/SFML")
    endif()
endif()

