cmake_minimum_required(VERSION 3.1)

# так пишутся комментарии

project(cuda_second_program LANGUAGES CXX CUDA)

set(SOURCE_EXE main.cpp solver_file.cu)

find_package(CUDA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # задаем флаги компилятору

include_directories(include) # расположение основных заголовочных файлов

add_executable(run_file ${SOURCE_EXE}) # создает исполняемый файл run_file
