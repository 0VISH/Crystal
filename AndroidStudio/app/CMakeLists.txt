cmake_minimum_required(VERSION 3.22.1)

project("androidcrystal")

add_library(engine
        SHARED
        ${CMAKE_SOURCE_DIR}/../../src/Android/entryPoint.cc)
	
add_definitions(-DANDROID=1)
add_definitions(-DGL=1)

target_include_directories(engine PRIVATE
	${CMAKE_SOURCE_DIR}/../../include/)
target_include_directories(engine PRIVATE
	${CMAKE_SOURCE_DIR}/../../vendor/glm/)
target_include_directories(engine PRIVATE
	${CMAKE_SOURCE_DIR}/../../vendor/box2d/include/)
target_include_directories(engine PRIVATE
	${CMAKE_SOURCE_DIR}/../../vendor/box2d/src/)
	
target_link_libraries(engine
        android
	GLESv3
        log)
