# CMakeList.txt: MySort 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project ("MySort")

# 将源代码添加到此项目的可执行文件。
add_executable (MySort "MySort.cpp" "MySort.h" "bubble_sort.cpp" "select_sort.cpp" "heap_sort.cpp" "quick_sort.cpp" "insert_sort.cpp" "shell_sort.cpp")

# TODO: 如有需要，请添加测试并安装目标。

