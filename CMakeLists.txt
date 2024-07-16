cmake_minimum_required(VERSION 3.28)

project(frozesh
    VERSION 
        1.0
    DESCRIPTION
        "Yet another shell written in C"
    LANGUAGES
        C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Og -g -Wuninitialized")
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(frozesh
               src/main.c
               src/reader.c
               src/tokenizer.c
               src/parser.c
               src/executor.c
               )