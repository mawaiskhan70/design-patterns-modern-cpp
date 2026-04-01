project(HtmlBuilder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    tags/Tag.cpp
    tags/P.cpp
    tags/IMG.cpp
    builder/HtmlBuilder.cpp
)

set(HEADERS
    tags/Tag.h
    tags/P.h
    tags/IMG.h
    builder/HtmlBuilder.h
)

set(DOCS
    EXPLANATION.md
)

add_executable(HtmlBuilder ${SOURCES} ${HEADERS} ${DOCS})

target_include_directories(HtmlBuilder PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/tags
    ${CMAKE_CURRENT_SOURCE_DIR}/builder
)
