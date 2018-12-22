cmake_minimum_required(VERSION 3.6)
project(ZAiSD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(lab1_main lab1/main.cpp)

add_executable(lab2_main lab2/main.cpp)

add_executable(lab3_main lab3/main.cpp)
add_executable(lab3_main2 lab3/main2.cpp)
add_executable(lab3_main3 lab3/main3.cpp)
add_executable(lab3_main4 lab3/main4.cpp)
add_executable(lab3_main5 lab3/main5.cpp)
add_executable(lab3_main6 lab3/main6.cpp)

add_executable(lab4_main lab4/main.cpp)

add_executable(lab5_encoder lab5/encoder.cpp)
add_executable(lab5_decoder lab5/decoder.cpp)