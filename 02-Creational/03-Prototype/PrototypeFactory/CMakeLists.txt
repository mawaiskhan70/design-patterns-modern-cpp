cmake_minimum_required(VERSION 3.16)
project(PrototypeFactory LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    model/Address.cpp
    model/Contact.cpp
    factory/EmployeeFactory.cpp
)

set(HEADERS
    model/Address.h
    model/Contact.h
    factory/EmployeeFactory.h
)

set(DOCS
    EXPLANATION.md
)

add_executable(PrototypeFactory ${SOURCES} ${HEADERS} ${DOCS})

target_include_directories(PrototypeFactory PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/factory
)
