set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

find_package(Qt5 COMPONENTS Sql REQUIRED)

# set_target_properties(login_dialog PROPERTIES DEFINE_SYMBOL "LOGIN_DATABASE_MANAGER")
file(COPY my_library.db DESTINATION ${CMAKE_BINARY_DIR})
add_executable(sql_test test.cpp)

target_link_libraries(sql_test PRIVATE global_setting Qt5::Sql)
