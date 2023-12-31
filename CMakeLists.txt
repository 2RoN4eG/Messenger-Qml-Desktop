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
    sources/t_image_info.h                                  sources/t_image_info.cpp
    sources/t_path_aggregator.h                             sources/t_path_aggregator.cpp
    sources/t_fs.h                                          sources/t_fs.cpp
    # in memory
    sources/t_image_storage_memory.h                        sources/t_image_storage_memory.cpp
    sources/t_meta_holder_memory.h                          sources/t_meta_holder_memory.cpp
    sources/t_image_info_storage_memory.h                   sources/t_image_info_storage_memory.cpp
    #
    sources/t_async_image_downloader.h                      sources/t_async_image_downloader.cpp
    sources/t_async_default_avatar_creator.h                         sources/t_async_default_avatar_creator.cpp
    #
    sources/t_ui_async_provider_image.h            sources/t_ui_async_provider_image.cpp
    sources/t_ui_async_provider_default_avatar.h            sources/t_ui_async_provider_default_avatar.cpp
    #
    sources/t_ui_async_response_image.h          sources/t_ui_async_response_image.cpp
    sources/t_ui_async_response_default_avatar.h    sources/t_ui_async_response_default_avatar.cpp
    # network
    sources/t_network_simulator.h                           sources/t_network_simulator.cpp
    #
    sources/t_server_api.h                                  sources/t_server_api.cpp
    #
    sources/t_json_parse_peer.h                     sources/t_json_parse_peer.cpp
    #
    Resources.qrc
    sources/t_ui_model_peer.h sources/t_ui_model_peer.cpp
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
