cmake_minimum_required(VERSION 3.26)
project(untitled C)

set(CMAKE_C_STANDARD 17)

add_executable(untitled
        Admin.c
        Panel.c
        Panel_Reception.c
        Algorithm/BinarySearch.c
        Algorithm/BubbleSort.c
        Algorithm/LinearSearch.c
        Algorithm/MergeSort.c
        Algorithm/Min_max.c
        Algorithm/QuickSort.c
        Algorithm/SearchingAlgorithm.h
        Algorithm/Selection_Sort.c
        Algorithm/SortingAlgorithm.h
        Panel_revised.c
        Last.c)
