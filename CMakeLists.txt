cmake_minimum_required(VERSION 3.14)

project(Messenger LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core LinguistTools Quick Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools Quick Network)

add_executable(Messenger
    main.cpp
    # header only section
    t_defines.h
    # header and executable section
    t_path_maker.h t_path_maker.cpp
    t_meta_holder_memory.h t_meta_holder_memory.cpp
    t_fs.h t_fs.cpp
    #
    t_image_storage_memory.h t_image_storage_memory.cpp
    t_image_info_storage_memory.h t_image_info_storage_memory.cpp
    #
    t_image_info.h t_image_info.cpp
    t_image_downloader_async.h t_image_downloader_async.cpp
    t_image_creator_async.h t_image_creator_async.cpp
    #
    t_ui_squared_avatar_provider.h t_ui_squared_avatar_provider.cpp
    t_ui_async_avatar_downloading_response.h t_ui_async_avatar_downloading_response.cpp
    t_ui_async_avatar_creating_response.h t_ui_async_avatar_creating_response.cpp
    t_ui_default_avatar_provider.h t_ui_default_avatar_provider.cpp
    #
    t_json_conversations.h t_json_conversations.cpp
    t_network_simulator.h t_network_simulator.cpp
    #
    Resources.qrc
)

target_link_libraries(Messenger Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(Messenger Qt${QT_VERSION_MAJOR}::Quick)
target_link_libraries(Messenger Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(Messenger Qt${QT_VERSION_MAJOR}::Qml)
target_link_libraries(Messenger Qt${QT_VERSION_MAJOR}::Network)

include(GNUInstallDirs)
install(TARGETS Messenger
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
