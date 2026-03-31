project(DocumentMachine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SOURCES
    main.cpp
    )

set(HEADERS)

set(DOCS
    EXPLANATION.md)

add_executable(DocumentMachine ${SOURCES} ${HEADERS} ${DOCS}
    model/document.h model/document.cpp
    interfaces/IPrinter.h
    interfaces/IScanner.h
    IMachine.h
    machines/printer.h machines/printer.cpp
    machines/scanner.h machines/scanner.cpp
    machine.h machine.cpp)

target_include_directories(DocumentMachine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/machines
)
