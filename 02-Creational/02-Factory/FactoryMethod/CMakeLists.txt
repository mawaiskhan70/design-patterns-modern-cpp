project(FactoryMethod LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    model/Point.cpp
    factory/PointFactory.cpp
)

set(HEADERS
    model/Point.h
    factory/PointFactory.h
)

set(DOCS
    EXPLANATION.md
)

add_executable(FactoryMethod ${SOURCES} ${HEADERS} ${DOCS})

target_include_directories(FactoryMethod PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/factory
)
