# CMakeList.txt: BankQueueSystem 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 定义项目的名称
project ("BankQueueSystem")
# 设置C语言标准为 C STANDARD 11
set(CMAKE_C_STANDARD 11)
# C-11标准是强制要求，不会衰退至低版本
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置 .c 文件路径为项目根目录下 /src 目录
aux_source_directory(${PROJECT_SOURCE_DIR}/src src_dirs)

# 定义MySQL库的路径变量
set(MYSQL_INC ${PROJECT_SOURCE_DIR}/libs/mysql-connector-c-6.1.11-winx64/include)
set(MYSQL_LIB ${PROJECT_SOURCE_DIR}/libs/mysql-connector-c-6.1.11-winx64/lib)
link_directories(${MYSQL_LIB})
# 将libmysql.dll 复制到 二进制目录中
file(COPY ${MYSQL_LIB}/libmysql.dll DESTINATION ${PROJECT_BINARY_DIR})
# 添加 src和include 目录及子目录下的所有.c/.h文件列表到SOURCES变量中
file(GLOB_RECURSE SOURCES "src/*.c" "include/*.h")
file(COPY banner.txt DESTINATION ${PROJECT_BINARY_DIR})

link_directories(${MYSQL_LIB})

# 将源代码添加到此项目的可执行文件 - 使用 SOURCES 变量中的文件来生成可执行文件
# 需要注意的是，使用 file(GLOB_RECURSE) 命令来自动查找文件是方便的，但不是最佳实践。这是因为它会在每次生成时重新扫描文件系统，这可能会导致不必要的重新编译，特别是当新的源文件被添加或删除时。
# 最好的做法是手动列出源文件，以确保只有真正需要的文件被编译。
add_executable (BankQueueSystem ${SOURCES} "main.c")

include_directories(${PROJECT_SOURCE_DIR}/include ${MYSQL_INC})
target_link_libraries(BankQueueSystem  ${MYSQL_LIB}/libmysql.lib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BankQueueSystem PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
