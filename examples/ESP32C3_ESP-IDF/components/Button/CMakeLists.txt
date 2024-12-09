file(GLOB_RECURSE SRC_DIR_LIST "*.cpp" "*.c")

idf_component_register(SRCS ${SRC_DIR_LIST}
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES "driver" "MiaoUI"
)