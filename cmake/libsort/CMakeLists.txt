cmake_minimum_required(VERSION 3.2)

project(SORT_LIB)

# 遍历下面的全部文件
aux_source_directory(./ SRC)

#
include_directories(${HEAD_PATH})

# 设置库文件目录
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})

add_library(${SORT_LIB} SHARED ${SRC})