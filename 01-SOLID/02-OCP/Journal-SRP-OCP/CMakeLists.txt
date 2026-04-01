project(Journal-SRP-OCP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    journal.cpp
    persistence/filepersistence.cpp
    persistence/jsonpersistence.cpp
)

set(HEADERS
    journal.h
    persistence/ipersistence.h
    persistence/filepersistence.h
    persistence/jsonpersistence.h
)

# ── Add documentation/extra files here ──
set(DOCS
    EXPLANATION.md
)
add_executable(Journal-SRP-OCP ${SOURCES} ${HEADERS})

target_include_directories(Journal-SRP-OCP PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/persistence
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../external
)
