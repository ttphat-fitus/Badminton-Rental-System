cmake_minimum_required(VERSION 3.10)
project(BadmintonRentalSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create a console demo executable
add_executable(badminton_demo
    src/demo.cpp
)

# Set the executable name
set_target_properties(badminton_demo PROPERTIES OUTPUT_NAME "badminton_demo")
