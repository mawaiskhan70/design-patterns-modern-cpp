project(ProductFilter LANGUAGES CXX)


# List the source files
set(SOURCES
    main.cpp
    model/product.cpp

)

# List the header files
set(HEADERS
    model/product.h
    specification/specification.h
)

add_executable(ProductFilter ${SOURCES} ${HEADERS}
    specification/colorspecification.h specification/colorspecification.cpp
    sizespecification.h sizespecification.cpp
    specification/andspecification.h specification/andspecification.cpp
    filter/filter.h
    filter/betterfilter.h filter/betterfilter.cpp )

target_include_directories(ProductFilter PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/specification
    ${CMAKE_CURRENT_SOURCE_DIR}/filter
)
