cmake_minimum_required(VERSION 3.22.1)

project("androidcrystal")

add_library(${CMAKE_PROJECT_NAME}
        SHARED
        ${CMAKE_SOURCE_DIR}/../../src/Android/entryPoint.cc)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log)