set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set(SOURCE_FILES CDataBaseManager.cpp)
set(HEADER_FILES CDataBaseManager.h)

find_package(Qt5 COMPONENTS Sql REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})

add_library(database_manager SHARED ${SOURCE_FILES} ${HEADER_FILES})

set_target_properties(database_manager PROPERTIES DEFINE_SYMBOL "DATABASE_MANAGER_EXPORT")

add_executable(sql_test test.cpp ${SOURCE_FILES})

target_link_libraries(database_manager PRIVATE global_setting Qt5::Sql)

target_link_libraries(sql_test PRIVATE global_setting Qt5::Sql)
