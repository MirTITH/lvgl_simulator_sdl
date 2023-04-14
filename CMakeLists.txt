cmake_minimum_required(VERSION 3.12)

project(lvgl_simulator_sdl) # 项目名称

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS true)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS true)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
    set(SDL2_DIR SDL2-2.26.5/cmake)
    message("Platform is WIN32. Use builtin SDL2 at " ${SDL2_DIR})
endif()

find_package(SDL2 REQUIRED)

include_directories(.)
include_directories(glue_to_stm32)
include_directories(${SDL2_INCLUDE_DIRS})

if(WIN32)
    link_libraries(${SDL2_STATIC_LIBRARIES})
else()
    link_libraries(${SDL2_LIBRARIES})
endif()

option(LV_LVGL_H_INCLUDE_SIMPLE OFF)
option(LV_CONF_INCLUDE_SIMPLE OFF)

add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

# 在 SDL 中使用标准线程库创建线程会出问题，所以不使用标准线程库了
# find_package(Threads REQUIRED)

# 可执行文件输出路径
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    glue_to_stm32/*.cpp
    glue_to_stm32/*.c
    src/*.cpp
    src/*.c
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    # ${OpenCV_INCLUDE_DIRS}
    lvgl
    src
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    # 对 MSVC 开启 utf-8 支持
    "$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>"
    "$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    m
    # ${OpenCV_LIBS} gomp
    # ${CMAKE_THREAD_LIBS_INIT}
    lv_drivers
    lvgl::lvgl
    lvgl::demos
    lvgl::examples
)

target_link_options(${PROJECT_NAME} PRIVATE
    # -static
)
