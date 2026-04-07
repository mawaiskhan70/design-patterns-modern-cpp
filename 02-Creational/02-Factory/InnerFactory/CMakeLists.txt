project(InnerFactory LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    model/Point.cpp
)

set(HEADERS
    model/Point.h
)

set(DOCS
    EXPLANATION.md
)

add_executable(InnerFactory ${SOURCES} ${HEADERS} ${DOCS})

target_include_directories(InnerFactory PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/model
)
