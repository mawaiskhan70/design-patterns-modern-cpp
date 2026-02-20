project(Journal-SRP-OCP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    journal.cpp
)

set(HEADERS
    journal.h
    persistence/ipersistence.h
)

add_executable(Journal-SRP-OCP ${SOURCES} ${HEADERS}
    persistence/filepersistence.h persistence/filepersistence.cpp
    persistence/jsonpersistence.h persistence/jsonpersistence.cpp
     )

target_include_directories(Journal-SRP-OCP PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/persistence
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../external
)
