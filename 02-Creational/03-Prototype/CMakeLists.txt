cmake_minimum_required(VERSION 3.16)
project(Prototype_Demos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Revision.md to Qt Creator project tree
add_custom_target(Prototype_Docs SOURCES Revision.md)

add_subdirectory(Prototype)
add_subdirectory(PrototypeFactory)
add_subdirectory(PrototypeSerialization)
