cmake_minimum_required(VERSION 3.29)
project(pp2_gritvm)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(pp2_gritvm
        catch.hpp
        GritVMBase.cpp
        GritVMBase.hpp
        GritVM.cpp
        GritVM.hpp
        PP2Test.cpp)
