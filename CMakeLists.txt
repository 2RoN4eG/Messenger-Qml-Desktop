cmake_minimum_required(VERSION 3.14)

project(Messenger-Qml-Desktop LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core LinguistTools Quick Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools Quick Network)

add_executable(${CMAKE_PROJECT_NAME}
    sources/t_main.cpp
    # header only section
    sources/t_value.h
    sources/t_defines.h
    sources/t_json_defines.h
    # header and executable section
    sources/t_image_info.h                          sources/t_image_info.cpp
    sources/t_path_aggregator.h                     sources/t_path_aggregator.cpp
    sources/t_fs.h                                  sources/t_fs.cpp
    sources/t_image_fs_worker.h                     sources/t_image_fs_worker.cpp
    #
    sources/interface/i_image_info_storage.h        sources/interface/i_image_info_storage.cpp
    sources/interface/i_messenger_context_setter.h  sources/interface/i_messenger_context_setter.cpp
    sources/interface/i_messenger_context_getter.h  sources/interface/i_messenger_context_getter.cpp
    sources/interface/i_meta_holder.h               sources/interface/i_meta_holder.cpp
    sources/interface/i_rotator.h                   sources/interface/i_rotator.cpp
    # implementation in memory
    sources/memory/t_meta_holder.h                  sources/memory/t_meta_holder.cpp
    sources/memory/t_image_info_storage.h           sources/memory/t_image_info_storage.cpp
    sources/memory/t_messender_context_setter.h     sources/memory/t_messender_context_setter.cpp
    # implementation in file
    #
    sources/t_async_default_avatar_creator.h        sources/t_async_default_avatar_creator.cpp
    sources/t_async_image_downloader.h              sources/t_async_image_downloader.cpp
    # UI providers
    sources/t_ui_peer_preview_provider.h            sources/t_ui_peer_preview_provider.cpp
    sources/t_ui_peer_conversation_provider.h       sources/t_ui_peer_conversation_provider.cpp
    #
    sources/t_ui_async_image_provider.h             sources/t_ui_async_image_provider.cpp
    sources/t_ui_async_default_avatar_provider.h    sources/t_ui_async_default_avatar_provider.cpp
    sources/t_ui_async_image_response.h             sources/t_ui_async_image_response.cpp
    sources/t_ui_async_default_avatar_response.h    sources/t_ui_async_default_avatar_response.cpp
    # network
    sources/t_network_simulator.h                   sources/t_network_simulator.cpp
    #
    sources/t_server_api.h                          sources/t_server_api.cpp
    #
    sources/i_json_processor.h                      sources/i_json_processor.cpp
    sources/t_json_peer_info_parser.h               sources/t_json_peer_info_parser.cpp
    sources/t_json_peer_message_processor.h         sources/t_json_peer_message_processor.cpp
    #
    Resources.qrc
)

target_link_libraries(${CMAKE_PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${CMAKE_PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Quick)
target_link_libraries(${CMAKE_PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(${CMAKE_PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Qml)
target_link_libraries(${CMAKE_PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Network)

include(GNUInstallDirs)
install(TARGETS ${CMAKE_PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
