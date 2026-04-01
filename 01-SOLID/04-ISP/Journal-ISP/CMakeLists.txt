project(Journal-ISP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp)

set(HEADERS

)

set(DOCS
    EXPLANATION.md)

add_executable(Journal-ISP ${SOURCES} ${HEADERS} ${DOCS}
    model/journal.h model/journal.cpp
    interfaces/ISaver.h
    interfaces/ILoader.h
    interfaces/IPersistence.h
    persistence/filesaver.h persistence/filesaver.cpp
    persistence/fileloader.h persistence/fileloader.cpp
    persistence/jsonsaver.h persistence/jsonsaver.cpp
    persistence/filepersistence.h persistence/filepersistence.cpp)

target_include_directories(Journal-ISP PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/persistence
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../external
)
