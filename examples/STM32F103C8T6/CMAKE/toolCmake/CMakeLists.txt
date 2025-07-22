cmake_minimum_required(VERSION 3.12)

set(CMAKE_PROJECT_NAME user_src) 

# cmake FUNC
include(${CMAKE_CURRENT_LIST_DIR}/cmake_func/functions.cmake)

project(${CMAKE_PROJECT_NAME})
add_library(${CMAKE_PROJECT_NAME} INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(${CMAKE_PROJECT_NAME} INTERFACE 
    USE_STDPERIPH_DRIVER 
	STM32F10X_MD
    $<$<CONFIG:Debug>:DEBUG>
)

# 递归包含头文件
include_sub_directories_recursively(${CMAKE_CURRENT_LIST_DIR}/../../USER)
include_sub_directories_recursively(${CMAKE_CURRENT_LIST_DIR}/../../hal)

target_include_directories(${CMAKE_PROJECT_NAME} INTERFACE
    # 无CMAKE支持的库，自行引入
    # fatfs
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/fatfs/source
    # general-buzzer
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/general-buzzer
    # MPU6050
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/MPU6050
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/MPU6050/eMPL
    # MultiButton
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/MultiButton
)

# 递归查找所有源码文件
file(GLOB_RECURSE USER_SRC ${CMAKE_CURRENT_LIST_DIR}/../../USER/*.c)
file(GLOB_RECURSE HAL_SRC ${CMAKE_CURRENT_LIST_DIR}/../../hal/*.c)

target_sources(${CMAKE_PROJECT_NAME} PUBLIC
    ${USER_SRC}
    ${HAL_SRC}
    # CPU部分 CMAKE\GCC\startup_stm32f10x_gcc.s
    ${CMAKE_CURRENT_LIST_DIR}/../../CMAKE/GNU/startup_stm32f10x_gcc.s
    # 库支持部分
    ${CMAKE_CURRENT_LIST_DIR}/../../CMAKE/GNU/syscalls.c
    ${CMAKE_CURRENT_LIST_DIR}/../../CMAKE/GNU/sysmem.c
    # fatfs部分
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/fatfs/source/diskio.c
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/fatfs/source/ff.c
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/fatfs/source/ffsystem.c
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/fatfs/source/ffunicode.c
    # general-buzzer部分
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/general-buzzer/buzzer.c
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/general-buzzer/ringtones.c
    # MPU6050部分
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/MPU6050/mpuiic.c
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/MPU6050/mpu6050.c
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/MPU6050/eMPL/inv_mpu_dmp_motion_driver.c
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/MPU6050/eMPL/inv_mpu.c
    # MultiButton部分
    ${CMAKE_CURRENT_LIST_DIR}/../../lib/MultiButton/multi_button.c

)

target_link_directories(${CMAKE_PROJECT_NAME} INTERFACE

)

target_link_libraries(${CMAKE_PROJECT_NAME} INTERFACE
    # ${CMAKE_CURRENT_LIST_DIR}/../../../5_PhysicalChip/GD32F3x0/CMSIS/GD/arm_cortexM4lf_math.lib
)




