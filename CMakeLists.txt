cmake_minimum_required(VERSION 3.14)

project(Messenger LANGUAGES CXX)

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

    # header and executable section
    sources/t_image_component.hpp                       sources/t_image_component.cpp
    sources/t_path_aggregator.h                         sources/t_path_aggregator.cpp
    sources/t_fs.h                                      sources/t_fs.cpp
    sources/t_fs_image_worker.h                         sources/t_fs_image_worker.cpp

    #
    sources/interfaces/i_image_component_storage.hpp    sources/interfaces/i_image_component_storage.cpp
    sources/interfaces/i_peer_component_storage.hpp     sources/interfaces/i_peer_component_storage.cpp
    sources/interfaces/i_message_component_storage.hpp  sources/interfaces/i_message_component_storage.cpp

    sources/interfaces/i_peer_context_setter.h          sources/interfaces/i_peer_context_setter.cpp
    sources/interfaces/i_peer_context_getter.h          sources/interfaces/i_peer_context_getter.cpp

    sources/interfaces/i_file_meta_holder.hpp           sources/interfaces/i_file_meta_holder.cpp
    sources/interfaces/i_rotator.h                      sources/interfaces/i_rotator.cpp
    sources/interfaces/i_avatar_fs_path.hpp             sources/interfaces/i_avatar_fs_path.cpp
    sources/interfaces/i_path_self_and_peer.h           sources/interfaces/i_path_self_and_peer.cpp
    sources/interfaces/i_photo_path.hpp                 sources/interfaces/i_photo_path.cpp
    sources/interfaces/i_stiker_fs_path.hpp             sources/interfaces/i_path_stiker.cpp
    sources/interfaces/i_json_processor.hpp             sources/interfaces/i_json_processor.cpp
    sources/interfaces/i_ui_image_path_maker.h          sources/interfaces/i_ui_image_path_maker.cpp
    sources/interfaces/i_image_fs_worker.h              sources/interfaces/i_image_fs_worker.cpp

    # in memory implementation
    sources/memory/t_meta_holder.hpp                    sources/memory/t_meta_holder.cpp
    sources/memory/t_image_component_storage.hpp        sources/memory/t_image_component_storage.cpp
    sources/memory/t_peer_component_storage.h           sources/memory/t_peer_component_storage.cpp
    sources/memory/t_message_component_storage.hpp      sources/memory/t_message_component_storage.cpp
    sources/memory/t_peer_context_setter.h              sources/memory/t_peer_context_setter.cpp
    sources/memory/t_peer_context_getter.h              sources/memory/t_peer_context_getter.cpp

    # in file implementation

    # image downloader and creator
    sources/async/t_qt_async_default_avatar_creator.h   sources/async/t_qt_async_default_avatar_creator.cpp
    sources/async/t_qt_async_image_downloader.h         sources/async/t_qt_async_image_downloader.cpp
    # UI providers
    sources/ui/t_qt_image_provider.h                    sources/ui/t_qt_image_provider.cpp
    sources/ui/t_qt_image_response.h                    sources/ui/t_qt_image_response.cpp
    sources/ui/t_qt_default_avatar_provider.h           sources/ui/t_qt_default_avatar_provider.cpp
    sources/ui/t_qt_default_avatar_response.h           sources/ui/t_qt_default_avatar_response.cpp
    sources/ui/t_qt_peer_preview_provider.h             sources/ui/t_qt_peer_preview_provider.cpp
    sources/ui/t_qt_peer_conversation_provider.h        sources/ui/t_qt_peer_conversation_provider.cpp
    # network
    sources/t_network_simulator.h                       sources/t_network_simulator.cpp
    #
    sources/json/t_json_defines.h
    sources/json/t_json_peer_preview_parser.h           sources/json/t_json_peer_preview_parser.cpp
    sources/json/t_json_peer_message_processor.h        sources/json/t_json_peer_message_processor.cpp
    #
    sources/t_ui_image_path_maker.h                     sources/t_ui_image_path_maker.cpp
    sources/t_application.h                             sources/t_application.cpp
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
