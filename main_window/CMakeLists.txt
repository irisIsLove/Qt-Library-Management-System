set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set(SOURCE_FILES CMainWindow.cpp)
set(HEADER_FILES CMainWindow.h)
set(UI_FILES CMainWindow.ui)

include_directories(${CMAKE_SOURCE_DIR})

add_library(main_window SHARED ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES})

set_target_properties(main_window PROPERTIES DEFINE_SYMBOL "MAIN_WINDOW_EXPORT")

target_link_libraries(main_window PRIVATE global_setting)
