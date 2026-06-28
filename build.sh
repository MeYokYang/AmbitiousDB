#!/bin/bash

help()
{
    echo -e "help"
}

clean()
{
    echo -e "clean"
    rm -rf bin
    rm -rf lib
    rm -rf build
}

build()
{
    echo -e "build"
    rm -rf build
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    make
    ln -sf ${PROJECT_HOME}/build/compile_commands.json ${PROJECT_HOME}/compile_commands.json
}

PROJECT_HOME=$(cd "$(dirname "$0")" && pwd)

echo_err()
{
    echo -e "echo_err"
}

main()
{
    case "$1" in
        "-h" | "--help")
            help
            ;;
        "-c" | "--clean")
            clean
            ;;
        "-b" | "--build")
            build
            ;;
        "-r" | "--rebuild")
            clean
            build
            ;;
        *)
            echo_err
            help
            ;;
    esac
}

main "$@"
