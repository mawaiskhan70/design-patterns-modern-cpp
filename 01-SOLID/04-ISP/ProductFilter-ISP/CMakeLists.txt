project(ProductFilter-ISP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    model/product.cpp
    filters/ColorSpecification.cpp
    filters/SizeSpecification.cpp
    filters/BetterFilter.cpp
)

set(HEADERS
    model/product.h
    interfaces/ISpecification.h
    interfaces/IFilter.h
    interfaces/ICombiner.h
    filters/ColorSpecification.h
    filters/SizeSpecification.h
    filters/AndSpecification.h
    filters/BetterFilter.h
)

set(DOCS
    EXPLANATION.md
)

add_executable(ProductFilter-ISP ${SOURCES} ${HEADERS} ${DOCS})

target_include_directories(ProductFilter-ISP PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/filters
)
