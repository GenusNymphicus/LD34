#CockatooTest/
cmake_minimum_required(VERSION 2.8.11)
project(LD34)


option(RUN_TESTS "Run the gtests" OFF)

IF(EMSCRIPTEN)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/webGL/")
ELSE(EMSCRIPTEN)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/")
ENDIF(EMSCRIPTEN)

SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wall ")
SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
set(LIBRARIES ${LIBRARIES})
set(HEADER_FILES ${HEADER_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/include ../CockatooEngine/external/)
set(ENGINE_PATH "../CockatooEngine/")

add_subdirectory(${ENGINE_PATH} Cockatoo)
add_subdirectory(src)


SET(POSTFIX "")

IF (EMSCRIPTEN)

    #set to custom paths
    set(HEADER_FILES ${HEADER_FILES} "/home/kevin/Desktop/emsdk_portable/emscripten/master/system/include/" "/usr/local/include/")
    SET(POSTFIX ".bc")

ENDIF(EMSCRIPTEN)


add_executable(LD34${POSTFIX}  ${SOURCE_FILES})
include_directories( ${HEADER_FILES})


target_link_libraries(LD34${POSTFIX} ${LIBRARIES})
add_custom_command(TARGET LD34${POSTFIX} PRE_BUILD COMMAND ${PROJECT_SOURCE_DIR}/build/KTEResourcePacker)
