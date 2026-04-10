cmake_minimum_required(VERSION 4.0.0)
project(atbase)

set(HOME ${PROJECT_CURRENT_SOURCE_DIR})

# 源文件
file(GLOB_RECURSE SRC *.cpp)

# 制作为库
# 输出位置
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})
# 生成动态库
add_library(${ATBASE} SHARED ${SRC})

# 头文件目录设置
set(BASE_INCLUDE_DIRS ${HEAD_PATH}/base)
file(GLOB SUBDIR_LIST RELATIVE ${HEAD_PATH}/base ${HEAD_PATH}/base/*/)
foreach(subdir ${SUBDIR_LIST})
  list(APPEND BASE_INCLUDE_DIRS ${HEAD_PATH}/base/${subdir})
endforeach()
include_directories(${BASE_INCLUDE_DIRS})


