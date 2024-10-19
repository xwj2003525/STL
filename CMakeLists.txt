# CMakeList.txt: stl 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (stl)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE HEADER_FILES "include/*.h" "include/*.hpp")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# 包含 include 目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 添加可执行文件
add_executable(stl ${SOURCE_FILES} ${HEADER_FILES})


# TODO: 如有需要，请添加测试并安装目标。
