project(BuilderFacets LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    model/Person.cpp
    builder/PersonBuilderBase.cpp
)

set(HEADERS
    model/Person.h
    builder/PersonBuilderBase.h
    builder/PersonBuilder.h
    builder/PersonAddressBuilder.h
    builder/PersonJobBuilder.h
)

set(DOCS
    EXPLANATION.md
    Revision_Notes.md
)

add_executable(BuilderFacets ${SOURCES} ${HEADERS} ${DOCS})

target_include_directories(BuilderFacets PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/builder
)
