cmake_minimum_required(VERSION 3.16)

project(OCP_Demos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all OCP projects here
# As you add more projects, just add more lines
add_subdirectory(ProductFilter)
add_subdirectory(Journal-SRP-OCP)
# add_subdirectory(FutureProject2)
