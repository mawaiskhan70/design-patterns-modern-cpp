cmake_minimum_required(VERSION 3.16)
project(Prototype LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    model/Address.cpp
    model/Contact.cpp
)

set(HEADERS
    model/Address.h
    model/Contact.h
)

set(DOCS
    EXPLANATION.md
)

add_executable(Prototype ${SOURCES} ${HEADERS} ${DOCS})

target_include_directories(Prototype PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/model
)
