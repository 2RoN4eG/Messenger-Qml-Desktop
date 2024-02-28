#include <QGuiApplication>

#include "t_image_fs_worker.h"
#include "memory/t_image_info_storage.h"
#include "memory/t_meta_holder.h"
#include "memory/t_peer_context_setter.h"
#include "t_path_aggregator.h"
#include "t_ui_async_default_avatar_provider.h"
#include "t_ui_async_image_provider.h"
#include "t_server_api.h"
#include "t_fs.h"

#include "t_json_peer_info_parser.h"
#include "t_network_simulator.h"

#include "t_ui_peer_preview_provider.h"
#include "t_ui_peer_conversation_provider.h"

#include <QLocale>
#include <QTranslator>
#include <QNetworkAccessManager>
#include <QQmlApplicationEngine>
#include <QMetaType>
#include <QQmlContext>

#include <iostream>

namespace {
    void do_create_peer_directories(const t_peer_id peer_id,
                                    const t_common_paths& path,
                                    const i_fs& fs)
    {
        fs.do_create_directories(
            path.get_fs_path_for_avatar(peer_id, t_avatar_types::t_default_avatar)
            );

        fs.do_create_directories(
            path.get_fs_path_for_avatar(peer_id, t_avatar_types::t_squared_avatar)
            );

        fs.do_create_directories(
            path.get_fs_path_for_photo(peer_id)
            );
    }
}

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    int result = qmlRegisterType<t_ui_peer_preview_provider>("Bindings", 1, 0, "PeerInfoProvider");
    qDebug() << "register result is" << result;
    result = qmlRegisterType<t_ui_peer_conversation_provider>("Bindings", 1, 0, "PeerConversationProvider");
    qDebug() << "register result is" << result;


    const QUrl url("qrc:///ui/Main.qml");
    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &a, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    try {
        test_path();
    }
    catch (const std::exception& exception) {
        std::cout << "exception's what is " << exception.what() << std::endl;
    }

    const t_fs fs {};
    try {
        fs.do_remove("/Users/2RoN4eG/1024");
    } catch (const std::exception& exception) {
        std::cout << "exception's what is " << exception.what() << std::endl;
    }

    const t_peer_id& self = { 1024 };
    print(self);
    
    const t_common_paths path = make_common_path("/Users/2RoN4eG/", self);

    try {
        do_create_peer_directories(t_peer_id { 2048 }, path, fs);
        do_create_peer_directories(t_peer_id { 2049 }, path, fs);
        do_create_peer_directories(t_peer_id { 2050 }, path, fs);
        do_create_peer_directories(t_peer_id { 2051 }, path, fs);
        do_create_peer_directories(t_peer_id { 2052 }, path, fs);
        do_create_peer_directories(t_peer_id { 2053 }, path, fs);
        do_create_peer_directories(t_peer_id { 4096 }, path, fs);
    }
    catch (const std::exception& exception) {
        std::cout << "exception's what " << exception.what() << std::endl;
    }
    

    t_peer_infos peer_infos;
    memory::t_image_info_storage image_info_storage;
    t_messages messages;

    t_image_id_generator avatar_id_generator {};
    // t_image_id_generator photo_id_generator {};

    memory::t_peer_context_setter messenger_context { peer_infos, image_info_storage, messages };

    t_ui_peer_preview_provider peer_preview_provider { &peer_infos, &messenger_context };
    t_ui_peer_conversation_provider peer_conversation_provider { &messages };

    // Expose the instance to the QML engine's root context
    engine.rootContext()->setContextProperty("peer_info_context", &peer_preview_provider);
    engine.rootContext()->setContextProperty("peer_conversation_provider", &peer_conversation_provider);

    t_network_simulator network_simulator { messenger_context };
    network_simulator.process_peer_info();
    network_simulator.process_peer_message();

    const t_fs_path& self_path = path.get_fs_path_for_self();
    memory::t_meta_holder meta_holder { 1024, 2048, fs.get_paths_in_directory(self_path) };
    t_image_fs_worker image_worker { fs, meta_holder };

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("peer_info_storage", &messenger_context);

    engine.addImageProvider(QLatin1String("default"), new t_ui_async_provider_default_avatar { t_make_avatar_path { path, t_avatar_types::t_default_avatar }, image_info_storage, image_worker });
    engine.addImageProvider(QLatin1String("avatars"), new t_ui_async_image_provider          { t_make_avatar_path { path, t_avatar_types::t_squared_avatar }, image_info_storage, image_worker });
    engine.addImageProvider(QLatin1String("photos"),  new t_ui_async_image_provider          { t_make_photo_path  { path },                           image_info_storage, image_worker });

    engine.load(url);
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return a.exec();
}
