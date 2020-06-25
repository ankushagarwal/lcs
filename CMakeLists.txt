cmake_minimum_required(VERSION 3.16)
project(lcs)

set(CMAKE_CXX_STANDARD 17)

add_executable(lcs main.cpp lcs.hpp libra_types.hpp serde.hpp move.hpp)