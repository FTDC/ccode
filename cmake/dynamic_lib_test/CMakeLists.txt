cmake_minimum_required(VERSION 3.2)

project(${APP_NAME_DYNAMIC})

# 包含头部
include_directories(${HEAD_PATH})

# 遍历文件
file(GLOB SRC ./*.c)

# 静态库的目录
LINK_DIRECTORIES(${LIB_PATH})
#  链接库
link_libraries(${SORT_LIB})

# 设置输出文件目录
set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH})

# 编译可执行文件
add_executable(${APP_NAME_DYNAMIC} ${SRC})
