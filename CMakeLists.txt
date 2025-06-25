cmake_minimum_required(VERSION 3.30)
project(websocket_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Applications/Qt6.2.4/6.2.4/macos")

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

include_directories(./head ./ui)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        WebSockets
        REQUIRED)

add_executable(websocket_test
        main.cpp
        ui/main_window.cpp
        ui/main_window.h
        ui/main_window.ui
        src/ws_client_connection.cpp
        head/ws_client_connection.h
        ui/data_window.cpp
        ui/data_window.h
        ui/data_window.ui
        ui/time_task_window.cpp
        ui/time_task_window.h
        ui/time_task_window.ui
        ui/add_timer_send_data_window.cpp
        ui/add_timer_send_data_window.h
        ui/add_timer_send_data_window.ui

)

target_link_libraries(websocket_test
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        Qt::WebSockets
        ${UI_HEAD_TRANSFER}     #仅仅用于传递头文件
        ${CODE_RESOURCE_HEAD_TRANSFER}
)

