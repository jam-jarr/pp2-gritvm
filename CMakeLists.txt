cmake_minimum_required(VERSION 3.29)
project(pp2_gritvm)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

# find_package(Catch2 REQUIRED)

add_executable(pp2_gritvm
        catch.hpp
        GritVMBase.hpp
        GritVM.cpp
        GritVM.hpp
        PP2Test.cpp
        GritVMBase.cpp)

# target_link_libraries(PP2Test Catch2::Catch2)