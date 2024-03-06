set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set(SOURCE_FILES CLoginDialog.cpp CRegisterDialog.cpp)
set(HEADER_FILES CLoginDialog.h CRegisterDialog.h)
set(UI_FILES CLoginDialog.ui CRegisterDialog.ui)

include_directories(${CMAKE_SOURCE_DIR})

add_library(login_dialog SHARED ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES})

set_target_properties(login_dialog PROPERTIES DEFINE_SYMBOL "LOGIN_DIALOG_EXPORT")

target_link_libraries(login_dialog PRIVATE global_setting database_manager)
