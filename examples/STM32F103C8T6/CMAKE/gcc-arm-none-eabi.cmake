# 设置系统名称和处理器架构
set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)        # 设置处理器架构为arm

# 强制指定编译器
set(CMAKE_C_COMPILER_FORCED TRUE)       # 强制指定C编译器
set(CMAKE_CXX_COMPILER_FORCED TRUE)     # 强制指定C++编译器
set(CMAKE_C_COMPILER_ID GNU)            # 设置C编译器ID为GNU
set(CMAKE_CXX_COMPILER_ID GNU)          # 设置C++编译器ID为GNU


# 一些默认的GCC设置，要求arm-none-eabi-xx必须在PATH环境变量中
set(TOOLCHAIN_PREFIX                arm-none-eabi-) # 设置工具链前缀为arm-none-eabi-

# 设置各个工具的路径和名称
set(CMAKE_C_COMPILER                ${TOOLCHAIN_PREFIX}gcc)     # 设置C编译器
set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})        # 设置汇编编译器，使用C编译器
set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_PREFIX}g++)     # 设置C++编译器
set(CMAKE_LINKER                    ${TOOLCHAIN_PREFIX}g++)     # 设置链接器
set(CMAKE_OBJCOPY                   ${TOOLCHAIN_PREFIX}objcopy) # 设置对象复制工具
set(CMAKE_SIZE                      ${TOOLCHAIN_PREFIX}size)    # 设置大小计算工具

# 设置生成的可执行文件的后缀
set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")     # 设置汇编可执行文件后缀为.elf
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")     # 设置C可执行文件后缀为.elf
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")     # 设置C++可执行文件后缀为.elf

# 设置尝试编译的目标类型为静态库
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)   # 设置尝试编译的目标类型为静态库

# MCU-specific 编译标志
set(TARGET_FLAGS "-mcpu=cortex-m3 -mfloat-abi=soft ")    # 设置目标平台的特定编译标志

# 设置C编译标志
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${TARGET_FLAGS}")   # 添加目标平台特定的编译标志到C编译器标志(基于原有标志添加)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -fdata-sections -ffunction-sections ") # 添加更多编译器标志
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-pedantic") # 忽略类似括号包裹大括号之类的警告(-Wpedantic开启了严格警告检查)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter") # 忽略定义但未使用的警告(-Wunused-parameter)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-sign-compare") # 忽略有符号与无符号对比的错误

# 根据构建类型设置不同的优化级别
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g3")    # 如果是Debug构建类型，设置为无优化并生成调试信息
endif()
if(CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g1")    # 如果是Release构建类型，设置为O3优化并生成少量调试信息
endif()

# 设置汇编编译标志
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp -MMD -MP ")  # 设置汇编编译标志

# 设置C++编译标志
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")   # 添加C++编译标志，禁用RTTI、异常和线程安全静态变量

set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} --specs=nano.specs")   # 使用nano.specs配置
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections")    # 生成映射文件并移除未使用的部分
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--start-group -lc -lm -Wl,--end-group")   # 链接C库和数学库
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--print-memory-usage")    # 打印内存使用情况s's


# 设置C++链接器标志
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--start-group -lstdc++ -lsupc++ -Wl,--end-group")   # 添加C++特定的链接标志，链接标准C++库

