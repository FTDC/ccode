# 这是一个 CMakeLists.txt 文件
cmake_minimum_required(VERSION 3.0)

#[[ 工程名称 ]]
project("cmake_project")

#set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
# 在CMake中指定可执行程序输出的路径，也对应一个宏

#file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
#file(GLOB MAIN_HEAD ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
#message("Building" , "${CMAKE_CURRENT_SOURCE_DIR}/*.c")


#set(HOME /mnt/e/workspace/c/ccode/cmake)
#set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)


# 可执行文件打包，生产可执行文件
# add_executable(可执行程序名 源文件名称)
#add_executable(app main.c add.c sub.c mult.c div.c)

# ----------------------------------      预定义宏        --------------------------------------------------
#+  PROJECT_SOURCE_DIR	            |   使用cmake命令后紧跟的目录，一般是工程的根目录                            +
#+  PROJECT_BINARY_DIR	            |   执行cmake命令的目录                                                  +
#+  CMAKE_CURRENT_SOURCE_DIR        |	当前处理的CMakeLists.txt所在的路径                                    +
#+  CMAKE_CURRENT_BINARY_DIR	    |   target 编译目录                                                     +
#+  EXECUTABLE_OUTPUT_PATH	        |   重新定义目标二进制可执行文件的存放位置                                   +
#+  LIBRARY_OUTPUT_PATH	            |   重新定义目标链接库文件的存放位置                                        +
#+  PROJECT_NAME	                |   返回通过PROJECT指令定义的项目名称                                      +
#+  CMAKE_BINARY_DIR	            |   项目实际构建路径，假设在build目录进行的构建，那么得到的就是这个目录的路径     +
# ---------------------------------      预定义宏        ----------------------------------------------------


# -----------------------------      静态库        -----------------------------------

# 设置动态库/静态库生成路径
set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# 设置测试程序生成的路径
set(EXEC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# 设置头文件目录
set(HEAD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)


set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

# 设置库名
set(CALC_LIB calc)
set(SORT_LIB sort)

# 项目名称
set(APP_NAME_STATIC static_lib_test)
set(APP_NAME_DYNAMIC dynamic_lib_test)

# 在cmake中，如果要制作静态库，需要使用的命令如下：
# add_library(calc STATIC ${SRC_LIST})
#add_library(clac STATIC add.c sub.c mult.c div.c)
#add_library(sort STATIC libsort/sort.c)

# 在cmake中，链接静态库的命令如下：
# link_libraries(<static lib> [<static lib>...])

# 包含静态库路径
#link_directories(${PROJECT_SOURCE_DIR}/lib)

# -----------------------------      静态库        -----------------------------------


# -----------------------------      动态库        -----------------------------------

# 在cmake中，如果要制作动态库，需要使用的命令如下：
# add_library(库名称 SHARED 源文件1 [源文件2] ...)
#add_library(calc SHARED ${MAIN_SRC})

# 指定源文件或者动态库对应的头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

message(STATUS, ${PROJECT_SOURCE_DIR})

# 指定要链接的动态库的路径
#link_directories(${PROJECT_SOURCE_DIR}/lib)
#link_libraries(${CALC_LIB})
#link_libraries(${SORT_LIB})
#target_link_libraries(libsort)

# 在cmake中链接动态库的命令如下:
# target_link_libraries(
#    <target>
#    <PRIVATE|PUBLIC|INTERFACE> <item>...
#    [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)

# 动态库的链接具有传递性，如果动态库 A 链接了动态库B、C，动态库D链接了动态库A，
# target_link_libraries(A B C)
# 此时动态库D相当于也链接了动态库B、C，并可以使用动态库B、C中定义的方法。
# target_link_libraries(D A)

##### 指定可执行程序要链接的动态库名字
#target_link_libraries(app pthread)

# -----------------------------      动态库        -----------------------------------


# -----------------------------      动态库        -----------------------------------

#project(TEST)
#set(TEMP "hello,world")
#
#file(GLOB SRC_1 ${PROJECT_SOURCE_DIR}/*.c)
#file(GLOB SRC_2 ${PROJECT_SOURCE_DIR}/src2/*.cpp)
## 追加(拼接)
#set(SRC_1 ${SRC_1} ${SRC_2} ${TEMP})
#
## 移除 main.cpp
#list(REMOVE_ITEM SRC_1 ${PROJECT_SOURCE_DIR}/main.cpp)
## 移除 main.cpp
#list(REMOVE_ITEM SRC_1 ${PROJECT_SOURCE_DIR}/main.c)
## 移除后日志
#message(STATUS "message: ${SRC_1}")


# PROJECT_SOURCE_DIR 宏对应的值就是我们在使用cmake命令时，后面紧跟的目录，一般是工程的根目录。

#add_executable(app ${MAIN_SRC})

# # 指定要链接的动态库
#target_link_libraries(app pthread calc)


# 添加子目录
add_subdirectory(libclac)
add_subdirectory(libsort)
#add_subdirectory(static_lib_test)
add_subdirectory(dynamic_lib_test)




