#cmake_minimum_required(VERSION 2.8)

project(KerasToCpp)

#set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(SOURCE_FILES src/main.cpp inc/read.h inc/Convolution2D.h
        core/Convolution2D.cpp inc/MaxPooling.h core/MaxPooling.cpp inc/sigmoid.h inc/array4d.h core/array4d.cpp inc/BaseDataUnit.h inc/BatchNormalization.h inc/leakyReLu.h inc/matrix.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})


#include(FindPkgConfig)
#find_package(BelaMatrix REQUIRED)
#include_directories(${BELA_MATRIX_INCLUDE_DIR})
#target_link_libraries(${PROJECT_NAME} ${BELA_MATRIX_LIBRARY})
