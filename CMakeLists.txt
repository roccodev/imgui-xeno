cmake_minimum_required(VERSION 3.21)
project(imgui-xeno CXX)

## Error if not using switch toolchain file
if (NOT SWITCH AND NOT IMGUI_XENO_EXTERNAL_TOOLCHAIN)
  message(FATAL_ERROR "Not targeting switch, make sure to specify -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain.cmake")
endif ()

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23)

## ImGui user config
add_compile_definitions(IMGUI_USER_CONFIG="imgui_user_config.h")

## Project sources
include_directories(${PROJECT_SOURCE_DIR}/src_framework/lib)
include_directories(${PROJECT_SOURCE_DIR}/src_framework/nvn)
include_directories(${PROJECT_SOURCE_DIR}/src_framework/nn)
include_directories(${PROJECT_SOURCE_DIR}/src_framework/)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/extern/imgui)
include_directories(${PROJECT_SOURCE_DIR}/fonts/precompiled)
include_directories(${PROJECT_SOURCE_DIR}/shaders/precompiled)
include_directories(${PROJECT_SOURCE_DIR}/user_config)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES_ASM
        ${PROJECT_SOURCE_DIR}/src/*.s
        ${PROJECT_SOURCE_DIR}/src_framework/*.s
        )
file(GLOB_RECURSE SOURCES_H
        ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.hpp
        ${PROJECT_SOURCE_DIR}/src_framework/*.h ${PROJECT_SOURCE_DIR}/src_framework/*.hpp
        )
file(GLOB_RECURSE SOURCES_CXX
        ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.c
        ${PROJECT_SOURCE_DIR}/src_framework/*.cpp ${PROJECT_SOURCE_DIR}/src_framework/*.c
        )
file(GLOB IMGUI_SOURCES extern/imgui/*.cpp)
file(GLOB_RECURSE LOCAL_LIBRARIES ${PROJECT_SOURCE_DIR}/libs/*.a)

file(GLOB SOURCES_H ${PROJECT_SOURCE_DIR}/fonts/precompiled/*.h)
file(GLOB SOURCES_H ${PROJECT_SOURCE_DIR}/shaders/precompiled/*.h)
file(GLOB SOURCES_H ${PROJECT_SOURCE_DIR}/user_config/*.h)

## Include nx tools
if (NOT IMGUI_XENO_EXTERNAL_TOOLCHAIN)
  include(${CMAKE_SOURCE_DIR}/cmake/SwitchTools.cmake)
endif ()

## Build static lib
add_library(imgui_xeno STATIC ${SOURCES_ASM} ${SOURCES_C} ${SOURCES_H} ${SOURCES_CXX} ${IMGUI_SOURCES})
target_link_libraries(imgui_xeno ${LOCAL_LIBRARIES})
