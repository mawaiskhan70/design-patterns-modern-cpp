cmake_minimum_required(VERSION 3.16)

project(Factory_Demos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_custom_target(Factory_Docs SOURCES
    Revision.md
)

add_subdirectory(FactoryMethod)
add_subdirectory(InnerFactory)
add_subdirectory(AbstractFactory)
