#ifndef T_APPLICATION_H
#define T_APPLICATION_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "t_fs_image_worker.h"
#include "t_path_aggregator.h"
#include "t_fs.h"

#include "t_network_simulator.h"

#include "memory/t_storage_image_info.h"
#include "memory/t_storage_message_info.h"
#include "memory/t_storage_peer_info.h"

#include "memory/t_meta_holder.h"
#include "memory/t_peer_context_setter.h"
#include "memory/t_peer_context_getter.h"

#include "ui/t_qt_peer_preview_provider.h"
#include "ui/t_qt_peer_conversation_provider.h"

class t_application
{
public:
    t_application(int& argc, char** argv);
    ~t_application();

    int exec();

private:
    QGuiApplication _application;

    QQmlApplicationEngine _engine;

    t_fs                            _fs {};
    t_peer_id                       _self { 1024 };

    t_peer_infos                    _peer_infos;
    t_image_infos                   _image_infos;
    t_message_infos                 _message_infos;

    memory::t_peer_info_storage     _peer_info_storage { _peer_infos };
    memory::t_image_info_storage    _image_info_storage { _image_infos };
    memory::t_message_info_storage  _message_info_storage { _message_infos };

    memory::t_peer_context_setter   _peer_context_setter { _peer_info_storage, _image_info_storage, _message_info_storage };
    memory::t_peer_context_getter   _peer_context_getter { _peer_info_storage, _image_info_storage, _message_info_storage };

    t_peer_preview_provider         _peer_preview_provider      { &_peer_context_getter };
    t_peer_conversation_provider    _peer_conversation_provider { &_peer_context_getter };

    t_fs_common_paths               _root = make_common_path("/Users/2RoN4eG/1024/", _self);

    t_avatar_fs_path_maker          _default_avatar_fs_path_maker { _root, t_avatar_type_id::t_default_avatar };
    t_avatar_fs_path_maker          _squared_avatar_fs_path_maker { _root, t_avatar_type_id::t_squared_avatar };
    t_photo_fs_path_maker           _photo_fs_path_maker  { _root };

    t_image_id_generator            _image_id_generator;
    t_message_id_generator          _message_id_generator;

    t_network_simulator             _network_simulator { _peer_context_setter, _message_id_generator, _image_id_generator };

    t_fs_path                       _self_path = _root.get_fs_path_for_self();
    memory::t_meta_holder           _meta_holder { 10 * 1024 * 1024, 20 * 1024 * 1024, _fs.get_paths_in_directory(_self_path) };
    t_fs_image_worker               _image_fs_worker { _fs, _meta_holder };
};

#endif // T_APPLICATION_H
