cmake_minimum_required(VERSION 3.21)
project(mp1r-practice-mod CXX C ASM)

## Error if not using switch toolchain file
if (NOT SWITCH)
  message(FATAL_ERROR "Not targeting switch, make sure to specify -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain.cmake")
endif ()

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23)

if (LOGGER_IP)
  add_compile_definitions(LOGGER_IP="${LOGGER_IP}")
endif ()

## Title Id
set(TITLE_ID 010012101468c000)
set(CONFIG_TITLE_ID 0x${TITLE_ID})
add_compile_definitions(EXL_PROGRAM_ID=${CONFIG_TITLE_ID} IMGUI_USER_CONFIG="imgui_backend/nvn_imgui_config.h")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/module/subsdk9.json.template ${CMAKE_CURRENT_BINARY_DIR}/subsdk9.json)

## Project sources
include_directories(${PROJECT_SOURCE_DIR}/src_framework/lib)
include_directories(${PROJECT_SOURCE_DIR}/src_framework/nvn)
include_directories(${PROJECT_SOURCE_DIR}/src_framework/nn)
include_directories(${PROJECT_SOURCE_DIR}/src_framework/)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/extern/imgui)
include_directories(${PROJECT_SOURCE_DIR}/extern/json/include)

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

## Include nx tools
include(${CMAKE_SOURCE_DIR}/cmake/SwitchTools.cmake)

## subsdk9
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#set_source_files_properties(${SOURCES_CXX} PROPERTIES LANGUAGE CXX)
add_library(imgui_nvn STATIC ${SOURCES_ASM} ${SOURCES_C} ${SOURCES_H} ${SOURCES_CXX} ${IMGUI_SOURCES})
add_compile_definitions(EXL_LOAD_KIND=Module EXL_LOAD_KIND_ENUM=EXL_LOAD_KIND_MODULE)
target_link_libraries(imgui_nvn ${LOCAL_LIBRARIES})