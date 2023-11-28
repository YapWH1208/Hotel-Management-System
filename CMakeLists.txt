cmake_minimum_required(VERSION 3.26)
project(Algorithm C)

set(CMAKE_C_STANDARD 17)

add_executable(Algorithm
        Algorithm/QuickSort.c
        Algorithm/BubbleSort.c
        Algorithm/SortingAlgorithm.h
        Algorithm/MergeSort.c
        Panel.c
        Admin.c)
