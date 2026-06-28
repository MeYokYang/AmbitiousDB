project(ambi)

set(HOME ${PROJECT_CURRENT_SOURCE_DIR})

# 源文件
file(GLOB_RECURSE SRC *.cpp)

# 制作为库
# 输出位置
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})
# 生成动态库
add_library(${AMBI} SHARED ${SRC})

# 头文件目录设置
include_directories(${HEAD_PATH})
