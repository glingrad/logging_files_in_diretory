cmake_minimum_required(VERSION 3.16)

project(proj LANGUAGES CXX)
cmake_policy(SET CMP0167 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем исполняемый файл
add_executable(proj main.cpp)

find_package(Threads REQUIRED)

# Добавляем директории для включения
target_include_directories(proj PRIVATE Threads::Threads)

# Установка
include(GNUInstallDirs)
install(TARGETS proj
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
