#!/bin/bash

main_file='../get_next_line.c'
utils_file='../get_next_line_utils.c'

usage()
{
    echo "Usage: ./compile.sh [bonus] <files...>"
}

exe()
{
    echo "\$ $@"
    "$@"
}

compile()
{
    file=$(echo "$1" | rev | cut -d '.' -f2- | rev)
    echo "Compiling $file"
    exe cc -Wall -Wextra -Werror ${main_file} ${utils_file} -o "$file" $1 -I..
}

if [ "$#" -eq 0 ]; then
    usage
    exit 1
fi

if [ "$1" = "bonus" ]; then
    main_file='../get_next_line_bonus.c'
    utils_file='../get_next_line_utils_bonus.c'
    shift
fi

if [ "$#" -eq 0 ]; then
    echo "compile.sh: Too few arguments"
    exit 1
fi

while (( "$#" )); do
    if [ -f "$1" ]; then
        compile "$1"
    else
        printf "compile.sh: %s: Missing file\n" "$1"
    fi
    shift
done
