cmake_minimum_required(VERSION 3.16)

project(SRP_Demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SRP_Demo main.cpp
    journal/journal.h journal/journal.cpp
    journal/persistencemanager.h journal/persistencemanager.cpp)

target_include_directories(SRP_Demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/journal
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../external    # Points to external/
)
include(GNUInstallDirs)
install(TARGETS SRP_Demo
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
