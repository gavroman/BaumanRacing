cmake_minimum_required(VERSION 3.10)
project(Client)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")

include_directories(${SOURCE_DIR})

set(ALL_SOURCES ${SOURCE_DIR}/Application/application.cpp
                ${SOURCE_DIR}/Base_manager/base_manager.cpp
		${SOURCE_DIR}/Event/event.cpp
                ${SOURCE_DIR}/Game_context/game_context.cpp
		${SOURCE_DIR}/Game_context/game_context_manager.cpp
		${SOURCE_DIR}/Input/input.cpp
		${SOURCE_DIR}/Input/input_manager.cpp
		#${SOURCE_DIR}/Loader/loader.cpp
		${SOURCE_DIR}/Network/network.cpp
		${SOURCE_DIR}/Network/network_manager.cpp
		#${SOURCE_DIR}/Renderer/renderer.cpp
                )

set(ALL_HEADERS ${SOURCE_DIR}/Application/
                ${SOURCE_DIR}/Base_manager/
		${SOURCE_DIR}/Event/
		${SOURCE_DIR}/Event_manager/
                ${SOURCE_DIR}/Game_context/
		${SOURCE_DIR}/Input/
		#${SOURCE_DIR}/Loader/
		${SOURCE_DIR}/Network/
		#${SOURCE_DIR}/Renderer/
		${SOURCE_DIR}/Event_throwable/
                )

set(TEST_INTERNAL_SOURCES ${SOURCE_DIR}/Input/input_test.cpp
		${SOURCE_DIR}/Input/input_manager.cpp
		${SOURCE_DIR}/Network/network_test.cpp
		${SOURCE_DIR}/Network/network_manager.cpp
		${SOURCE_DIR}/Game_context/game_context_test.cpp
		${SOURCE_DIR}/Game_context/game_context_manager.cpp
		${SOURCE_DIR}/Event/event.cpp
                )

find_package(Boost REQUIRED)
find_package(SFML COMPONENTS graphics audio network window system REQUIRED)

if (Boost_FOUND AND SFML_FOUND)

    include_directories(${SFML_INCLUDE_DIR})
    include_directories(${Boost_INCLUDE_DIR})
    include_directories(${ALL_HEADERS})

    add_executable(Client.out ${SOURCE_DIR}/main.cpp ${ALL_SOURCES})
    target_link_libraries(Client.out ${Boost_LIBRARIES})
    target_link_libraries(Client.out ${SFML_LIBRARIES})


    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(Client_test_internal.out ${SOURCE_DIR}/main_test_internal.cpp ${TEST_INTERNAL_SOURCES})
    
    target_link_libraries(Client_test_internal.out ${GTEST_LIBRARIES})
	
    target_link_libraries(Client_test_internal.out pthread)
    target_link_libraries(Client_test_internal.out gmock)
    target_link_libraries(Client_test_internal.out ${Boost_LIBRARIES})
    target_link_libraries(Client_test_internal.out ${SFML_LIBRARIES})

else()
    if (Boost_FOUND)
        message("Boost library was not founded. Look there: https://github.com/boostorg/boost")
    endif()
    if (SFML_FOUND)
        message("SFML library was not founded. Look there: https://github.com/SFML/SFML")
    endif()
endif()
