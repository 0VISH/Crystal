cmake_minimum_required(VERSION 3.22.1)

project("androidcrystal")

add_library(engine
        SHARED
        ${CMAKE_SOURCE_DIR}/../../src/Android/entryPoint.cc)
# You don't have to build sandbox. Ideally, create a seperate android studio project for your game, create .so and drop it in **TODO: WHERE?** with the name "gameAnd"
add_library(
		game
		SHARED
		${CMAKE_SOURCE_DIR}/../../sandbox/src/sandbox.cc
)

add_definitions(-DANDROID=1)
add_definitions(-DGL=1)

include_directories(PRIVATE
	${CMAKE_SOURCE_DIR}/../../include/)
include_directories(PRIVATE
	${CMAKE_SOURCE_DIR}/../../vendor/glm/)
include_directories(PRIVATE
	${CMAKE_SOURCE_DIR}/../../vendor/box2d/include/)
include_directories(PRIVATE
	${CMAKE_SOURCE_DIR}/../../vendor/box2d/src/)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

target_link_libraries(engine
        android
		GLESv3
        log)
