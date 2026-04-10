#[[
    AmbitiousDB
]]
cmake_minimum_required(VERSION 4.0.0)
project(AmbitiousDB VERSION 0.0)

SET(CMAKE_CXX_STANDARD 11)

message("AmbitiousDB build")
add_definitions(-DDEBUG -DM32)

set(PROJECT_HOME ${PROJECT_SOURCE_DIR})

# 头文件目录
set(HEAD_PATH ${PROJECT_HOME}/include)
# 库文件目录
set(LIB_PATH ${PROJECT_HOME}/lib)
# 可执行文件目录
set(EXEC_PATH ${PROJECT_HOME}/bin)

# 库名
set(ATBASE atbase)
# 可执行文件名
set(ATINIT atinit)
set(ATSERVER atserver)
set(ATCLIENT atclient)

# 子目录CMakeLists.txt
function(add_all_subdirectories)
    file(GLOB_RECURSE SUBDIRS RELATIVE ${PROJECT_HOME} */CMakeLists.txt)
    foreach(SUBDIR ${SUBDIRS})
        get_filename_component(DIR ${SUBDIR} DIRECTORY)
        add_subdirectory(${DIR})
    endforeach(SUBDIR ${})
endfunction(add_all_subdirectories)
add_all_subdirectories()

