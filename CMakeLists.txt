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
    sources/main.cpp
    # header only section
    sources/t_defines.h
    # header and executable section
    sources/t_image_info.h                              sources/t_image_info.cpp
    sources/t_path_maker.h                              sources/t_path_maker.cpp
    sources/t_fs.h                                      sources/t_fs.cpp
    # in memory
    sources/t_image_storage_memory.h                    sources/t_image_storage_memory.cpp
    sources/t_meta_holder_memory.h                      sources/t_meta_holder_memory.cpp
    sources/t_image_info_storage_memory.h               sources/t_image_info_storage_memory.cpp
    #
    sources/t_image_downloader_async.h                  sources/t_image_downloader_async.cpp
    sources/t_image_creator_async.h                     sources/t_image_creator_async.cpp
    #
    sources/t_ui_squared_avatar_provider.h              sources/t_ui_squared_avatar_provider.cpp
    sources/t_ui_default_avatar_provider.h              sources/t_ui_default_avatar_provider.cpp
    #
    sources/t_ui_async_avatar_downloading_response.h    sources/t_ui_async_avatar_downloading_response.cpp
    sources/t_ui_async_avatar_creating_response.h       sources/t_ui_async_avatar_creating_response.cpp
    # network
    sources/t_network_simulator.h                       sources/t_network_simulator.cpp
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
