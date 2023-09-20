# 这是一个 CMakeLists.txt 文件
cmake_minimum_required(VERSION 3.2)

#[[ 工程名称 ]]
project("cmake_project_static_library")

#set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
# 在CMake中指定可执行程序输出的路径，也对应一个宏

file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
#file(GLOB MAIN_HEAD ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
message("Building" , "${CMAKE_CURRENT_SOURCE_DIR}/*.c")


#set(HOME /mnt/e/workspace/c/ccode/cmake)
#set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)
# 可执行文件打包，生产可执行文件
# add_executable(可执行程序名 源文件名称)
#add_executable(app main.c add.c sub.c mult.c div.c)

# 加入头文件
include_directories(${HEAD_PATH})

#链接库
link_directories(${LIB_PATH})
link_libraries(${CALC_LIB})


# 设置编译文件目录
set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH})

# 编译静态文件
add_executable(${APP_NAME_STATIC} ${MAIN_SRC})
