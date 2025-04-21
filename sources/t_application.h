#ifndef T_APPLICATION_H
#define T_APPLICATION_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "t_fs_image_worker.h"
#include "t_path_aggregator.h"
#include "t_fs.h"

#include "t_network_simulator.h"

#include "memory/t_image_component_storage.hpp"
#include "memory/t_message_component_storage.hpp"
#include "memory/t_peer_component_storage.h"

#include "memory/t_meta_holder.hpp"
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
    QGuiApplication                         _application;
    QQmlApplicationEngine                   _engine;

    t_fs                                    _fs;
    t_peer_id                               _self;

    t_peer_components                       _peer_components;
    memory::t_peer_component_storage        _peer_component_storage;

    t_image_components                      _image_components;
    memory::t_image_component_storage       _image_component_storage;

    t_message_components                    _message_components;
    memory::t_message_component_storage     _message_component_storage;

    memory::t_peer_context_setter           _peer_context_setter;
    memory::t_peer_context_getter           _peer_context_getter;

    t_qt_peer_preview_provider              _peer_preview_provider;

    t_qt_peer_conversation_provider         _peer_conversation_provider;

    t_compound_fs_path_maker                  _root;

    t_avatar_fs_path_maker                  _default_avatar_fs_path_maker;
    t_avatar_fs_path_maker                  _squared_avatar_fs_path_maker;
    t_photo_fs_path_maker                   _photo_fs_path_maker;

    t_image_id_generator                    _image_id_generator;

    t_message_id_generator                  _message_id_generator;

    t_network_simulator                     _network_simulator;

    t_fs_path                               _self_path;
    memory::t_meta_holder                   _meta_holder;
    t_fs_image_worker                       _image_fs_worker;
};

#endif // T_APPLICATION_H
