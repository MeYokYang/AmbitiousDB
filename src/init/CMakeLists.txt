project(atinit)

set(HOME ${PROJECT_CURRENT_SOURCE_DIR})

# 源文件路径
# 头文件
include_directories(${HEAD_PATH}/init)
include_directories(${MIX_HEAD_PATH})
# 源文件
file(GLOB_RECURSE SRC "*.cpp")

# 制作为可执行文件
# 输出位置
set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH})
# 生成可执行文件
add_executable(${ATINIT} ${SRC})

# 链接库
# 库路径
link_directories(${LIB_PATH})
# 链接
target_link_libraries(${ATINIT} PRIVATE ${AMBI})
