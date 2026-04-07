project(AbstractFactory LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    drinks/Tea.cpp
    drinks/Coffee.cpp
    factories/DrinkFactory.cpp
)

set(HEADERS
    drinks/HotDrink.h
    drinks/Tea.h
    drinks/Coffee.h
    factories/HotDrinkFactory.h
    factories/TeaFactory.h
    factories/CoffeeFactory.h
    factories/DrinkFactory.h
)

set(DOCS
    EXPLANATION.md
)

add_executable(AbstractFactory ${SOURCES} ${HEADERS} ${DOCS})

target_include_directories(AbstractFactory PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/drinks
    ${CMAKE_CURRENT_SOURCE_DIR}/factories
)
