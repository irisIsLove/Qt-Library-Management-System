cmake_minimum_required(VERSION 3.15)

project(my_library)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(Qt5 COMPONENTS Core Widgets Sql REQUIRED)

add_library(global_setting INTERFACE ${RESOURCE_FILES})

set(CMAKE_AUTOUIC TRUE)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)

set(RESOURCE_FILES resource.qrc)

target_link_libraries(global_setting INTERFACE Qt5::Core Qt5::Widgets Qt5::Sql)

add_subdirectory(database_manager)

add_subdirectory(login_dialog)

add_subdirectory(main_window)

add_executable(my_library main.cpp logo.rc ${RESOURCE_FILES})

target_link_libraries(my_library PRIVATE
    global_setting
    login_dialog
    main_window
)
