cmake_minimum_required(VERSION 3.14)

project(MIAOUI)
add_library(miaoui INTERFACE) # INTERFACE意味着这个库本身并不会被编译，而是作为依赖被其他目标使用，以便于引入不同平台头文件

# 递归查找所有源码文件
file(GLOB_RECURSE CORE_SRC ${CMAKE_CURRENT_LIST_DIR}/core/*.c)
file(GLOB_RECURSE DISPLAY_SRC ${CMAKE_CURRENT_LIST_DIR}/display/*.c)
file(GLOB_RECURSE FONTS_SRC ${CMAKE_CURRENT_LIST_DIR}/fonts/*.c)
file(GLOB_RECURSE IMAGES_SRC ${CMAKE_CURRENT_LIST_DIR}/images/*.c)
file(GLOB_RECURSE INDEV_SRC ${CMAKE_CURRENT_LIST_DIR}/indev/*.c)
file(GLOB_RECURSE WIDGET_SRC ${CMAKE_CURRENT_LIST_DIR}/widget/*.c)
# 非递归的案例
# file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/source/*.c)

target_include_directories(miaoui INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/core
    ${CMAKE_CURRENT_LIST_DIR}/display
    ${CMAKE_CURRENT_LIST_DIR}/fonts
    ${CMAKE_CURRENT_LIST_DIR}/images
    ${CMAKE_CURRENT_LIST_DIR}/indev
    ${CMAKE_CURRENT_LIST_DIR}/widget
)


target_sources(miaoui INTERFACE
    ${CORE_SRC}
    ${DISPLAY_SRC}
    ${FONTS_SRC}
    ${IMAGES_SRC}
    ${INDEV_SRC}
    ${WIDGET_SRC}
)

if(CMAKE_C_STANDARD LESS 99)
    message(ERROR "Generated code requires C99 or higher")
endif()
