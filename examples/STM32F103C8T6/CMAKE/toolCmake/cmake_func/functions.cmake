# FUNC

# 递归包含头文件的函数
function(include_sub_directories_recursively root_dir)
    if (IS_DIRECTORY ${root_dir})               # 当前路径是一个目录吗，是的话就加入到包含目录
        #        if (${root_dir} MATCHES "include")
        message("include dir: " ${root_dir})
        target_include_directories(${PROJECT_NAME} INTERFACE
        ${root_dir}
        )
        #        endif()
    endif()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*) # 获得当前目录下的所有文件，让如ALL_SUB列表中
    foreach(sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
            include_sub_directories_recursively(${root_dir}/${sub}) # 对子目录递归调用，包含
        endif()
    endforeach()
endfunction()

# 给某个目标，路径带有关键词的源文件，添加期望添加的标签(例如"-w")
function(set_compile_flags_for_matching_files target_name keywords compile_flags)
    # 获取目标的原始源文件列表
    get_target_property(src_list ${target_name} SOURCES)

    # 检查目标是否存在并有源文件
    if(NOT src_list)
        message(WARNING "Target '${target_name}' does not exist or has no sources.")
        return()
    endif()

    # 创建一个新的列表用于存放需要设置编译标志的文件
    set(filtered_src_list)

    # 遍历原始的源文件列表，筛选出需要的文件
    foreach(src_file IN LISTS src_list)
        if("${src_file}" MATCHES "${keywords}")
            list(APPEND filtered_src_list ${src_file})
        endif()
    endforeach()

    # 为筛选出的源文件设置编译标志
    foreach(src_file IN LISTS filtered_src_list)
        set_source_files_properties(${src_file} PROPERTIES COMPILE_FLAGS "${compile_flags}")
    endforeach()
endfunction()


# FUNC END