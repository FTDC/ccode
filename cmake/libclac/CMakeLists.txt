cmake_minimum_required(VERSION 3.0)

project(CALC_LIB)

# 遍历所有的文件 赋值给 SRC
AUX_SOURCE_DIRECTORY(./ SRC)

# 设置 Include 头文件夹
include_directories(${HEAD_PATH})

# 设置库文件目录
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})

# 生成静态块
add_library(${CALC_LIB} STATIC ${SRC})

