cmake_minimum_required(VERSION 3.14)
project(OOP_Lab4 VERSION 1.0.0 LANGUAGES CXX)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Настройка путей
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

# Включение директорий с заголовочными файлами
include_directories(${INCLUDE_DIR})

# Основная программа (только заголовочные файлы для шаблонов)
add_executable(lab4_main ${SRC_DIR}/main.cpp)

# Опции для тестов
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    # Подключение Google Test
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    
    # Для Windows: предотвращение перезаписи параметров компилятора родительского проекта
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(googletest)
    
    # Включение тестирования
    enable_testing()
    
    # Список тестовых файлов
    set(TEST_SOURCES
        ${TEST_DIR}/test_rectangle.cpp
        ${TEST_DIR}/test_trapezoid.cpp
        ${TEST_DIR}/test_rhombus.cpp
        ${TEST_DIR}/test_array.cpp
    )
    
    # Создание исполняемого файла для тестов
    add_executable(lab4_tests ${TEST_SOURCES})
    
    # Линковка с Google Test
    target_link_libraries(lab4_tests 
        GTest::gtest_main
    )
    
    # Добавление тестов в CTest
    include(GoogleTest)
    gtest_discover_tests(lab4_tests)
    
    # Вывод сообщения
    message(STATUS "Tests enabled. Use 'ctest' to run tests.")
endif()

# Установка флагов компиляции
if(MSVC)
    target_compile_options(lab4_main PRIVATE /W4)
else()
    target_compile_options(lab4_main PRIVATE -Wall -Wextra -Wpedantic)
endif()
