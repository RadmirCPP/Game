cmake_minimum_required(VERSION 3.16)
project(Game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка SFML_DIR вручную, если нужно
if(WIN32)
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-3.0.0/lib/cmake/SFML")
elseif(UNIX)
    # Можно использовать find_package без SFML_DIR, если установлен через пакетный менеджер
endif()

# Поиск SFML

# Исходники
add_executable(Game

    Game.cpp Game.h
    Player.cpp Player.h
    Enemy.cpp Enemy.h 
    MapMaker.cpp MapMaker.h 
    WindowHelpLogic.cpp WindowHelpLogic.h
 )

# Линковка SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

target_link_libraries(Game PRIVATE SFML::Graphics SFML::Window SFML::System)
if(SFML_STATIC_LIBRARIES)
    target_compile_definitions(Game PRIVATE SFML_STATIC)
endif()
# SFML_STATIC — если используешь статическую линковку

# Копирование ассетов после сборки
add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Game>/assets
)

add_subdirectory(${CMAKE_SOURCE_DIR}/nativefiledialog-extended-master)

target_link_libraries(Game PRIVATE nfd)


