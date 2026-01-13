cmake_minimum_required(VERSION 3.14)
project(ListsLibrary)

set(CMAKE_CXX_STANDARD 20)

# Скачиваем Catch2
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Тесты
add_executable(tests_lists tests/tests_lists.cpp)
target_include_directories(tests_lists PRIVATE include)
target_link_libraries(tests_lists PRIVATE Catch2::Catch2WithMain)

# Включаем тесты в CTest
include(CTest)