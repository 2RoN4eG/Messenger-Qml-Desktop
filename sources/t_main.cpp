#include <QGuiApplication>

#include "t_image_fs_worker.h"
#include "memory/t_image_info_storage.h"
#include "memory/t_meta_holder.h"
#include "memory/t_messenger_context.h"
#include "t_path_aggregator.h"
#include "t_ui_async_default_avatar_provider.h"
#include "t_ui_async_image_provider.h"
#include "t_server_api.h"
#include "t_fs.h"

#include "t_json_peer_parser.h"
#include "t_network_simulator.h"

#include "t_ui_peer_info_wrapper.h"

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
                                    const i_fs& fs) {
        fs.do_create_directories(
            path.get_fs_path_for_avatar(
                peer_id, t_avatar_type::t_default
                )
            );

        fs.do_create_directories(
            path.get_fs_path_for_avatar(
                peer_id, t_avatar_type::t_squared
                )
            );

        fs.do_create_directories(
            path.get_fs_path_for_photo(
                peer_id
                )
            );
    }
}

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    int result = qmlRegisterType<t_ui_peer_info_wrapper>("Bindings", 1, 0, "PeerInfoProvider");
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
    
    t_image_id_generator image_id_generator {};
    memory::t_image_info_storage image_info_storage;

    t_peer_infos peer_infos;
    memory::t_peer_info_context messenger_context { peer_infos, image_info_storage, image_id_generator };

    t_ui_peer_info_wrapper peer_info_wrapper { &peer_infos, &messenger_context };

    // Expose the instance to the QML engine's root context
    engine.rootContext()->setContextProperty("peer_info_context", &peer_info_wrapper);

    QObject *root_object = engine.rootObjects().value(0);

    // Check if the root object is valid
    if (root_object) {
        // Find the instantiated QML object by objectName
        QObject *qml_object = root_object->findChild<QQuickItem*>("peer_info_context");

        // Check if the QML object is valid
        if (qml_object) {
            // Set the property of the QML object
            // qml_object->setProperty("peer_info_storage", &peer_info_storage);
        } else {
            qWarning() << "QML object not found";
        }
    } else {
        qWarning() << "Root object not found";
    }

    // {
    //     peer_info_storage.set_image_info(t_peer_id { 2049 }, t_url { "https://images.pexels.com/photos/18926843/pexels-photo-18926843/free-photo-of-rough-volcanic-rock-formation.jpeg" },                              {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://images.pexels.com/photos/19467240/pexels-photo-19467240/free-photo-of-hand-holding-coffee-cup.jpeg" },                                    {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://images.pexels.com/photos/15561988/pexels-photo-15561988/free-photo-of-man-travelling-on-a-ferry.jpeg" },                                  {});
    //     peer_info_storage.set_image_info(t_peer_id { 2053 }, t_url { "https://images.pexels.com/photos/19467240/pexels-photo-19467240/free-photo-of-hand-holding-coffee-cup.jpeg" },                                    {});
    //     peer_info_storage.set_image_info(t_peer_id { 2049 }, t_url { "https://images.pexels.com/photos/18926843/pexels-photo-18926843/free-photo-of-rough-volcanic-rock-formation.jpeg" },                              {});
    //     peer_info_storage.set_image_info(t_peer_id { 2050 }, t_url { "https://images.pexels.com/photos/15561988/pexels-photo-15561988/free-photo-of-man-travelling-on-a-ferry.jpeg" },                                  {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://dji-minsk.by/upload/resize_cache/iblock/02a/3yg6kgg4eblh2kx5jp0sivu30uugr68a/80_80_1/Kvadrokopter_DJI_Mini_2_kupit_v_minske_6_.jpg" },                                                       {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://media.istockphoto.com/id/1271132926/vector/wireless-router-line-icon-vector-on-isolated-white-background-eps-10.jpg?s=1024x1024&w=is&k=20&c=UGe6fovpvI0vH9yCoGZSP9RsXbX9A5Lf5udPWK9ujSU=" }, {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://media.istockphoto.com/id/1271132926/vector/wireless-router-line-icon-vector-on-isolated-white-background-eps-10.jpg?s=1024x1024&w=is&k=20&c=UGe6fovpvI0vH9yCoGZSP9RsXbX9A5Lf5udPWK9ujSU=" }, {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://media.istockphoto.com/id/1271132926/vector/wireless-router-line-icon-vector-on-isolated-white-background-eps-10.jpg?s=1024x1024&w=is&k=20&c=UGe6fovpvI0vH9yCoGZSP9RsXbX9A5Lf5udPWK9ujSU=" }, {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://media.istockphoto.com/id/1271132926/vector/wireless-router-line-icon-vector-on-isolated-white-background-eps-10.jpg?s=1024x1024&w=is&k=20&c=UGe6fovpvI0vH9yCoGZSP9RsXbX9A5Lf5udPWK9ujSU=" }, {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://media.istockphoto.com/id/1271132926/vector/wireless-router-line-icon-vector-on-isolated-white-background-eps-10.jpg?s=1024x1024&w=is&k=20&c=UGe6fovpvI0vH9yCoGZSP9RsXbX9A5Lf5udPWK9ujSU=" }, {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://media.istockphoto.com/id/1271132926/vector/wireless-router-line-icon-vector-on-isolated-white-background-eps-10.jpg?s=1024x1024&w=is&k=20&c=UGe6fovpvI0vH9yCoGZSP9RsXbX9A5Lf5udPWK9ujSU=" }, {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://media.istockphoto.com/id/1271132926/vector/wireless-router-line-icon-vector-on-isolated-white-background-eps-10.jpg?s=1024x1024&w=is&k=20&c=UGe6fovpvI0vH9yCoGZSP9RsXbX9A5Lf5udPWK9ujSU=" },                   {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://media.istockphoto.com/id/1271132926/vector/wireless-router-line-icon-vector-on-isolated-white-background-eps-10.jpg?s=1024x1024&w=is&k=20&c=UGe6fovpvI0vH9yCoGZSP9RsXbX9A5Lf5udPWK9ujSU=" },                   {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://media.istockphoto.com/id/1271132926/vector/wireless-router-line-icon-vector-on-isolated-white-background-eps-10.jpg?s=1024x1024&w=is&k=20&c=UGe6fovpvI0vH9yCoGZSP9RsXbX9A5Lf5udPWK9ujSU=" },                   {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://media.istockphoto.com/id/1271132926/vector/wireless-router-line-icon-vector-on-isolated-white-background-eps-10.jpg?s=1024x1024&w=is&k=20&c=UGe6fovpvI0vH9yCoGZSP9RsXbX9A5Lf5udPWK9ujSU=" },                   {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://media.istockphoto.com/id/1271132926/vector/wireless-router-line-icon-vector-on-isolated-white-background-eps-10.jpg?s=1024x1024&w=is&k=20&c=UGe6fovpvI0vH9yCoGZSP9RsXbX9A5Lf5udPWK9ujSU=" },                   {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://media.istockphoto.com/id/1271132926/vector/wireless-router-line-icon-vector-on-isolated-white-background-eps-10.jpg?s=1024x1024&w=is&k=20&c=UGe6fovpvI0vH9yCoGZSP9RsXbX9A5Lf5udPWK9ujSU=" },                   {});
    //     peer_info_storage.set_image_info(t_peer_id { 2048 }, t_url { "https://media.istockphoto.com/id/1271132926/vector/wireless-router-line-icon-vector-on-isolated-white-background-eps-10.jpg?s=1024x1024&w=is&k=20&c=UGe6fovpvI0vH9yCoGZSP9RsXbX9A5Lf5udPWK9ujSU=" },                   {});
    // }

    t_network_simulator network_simulator { messenger_context };
    network_simulator.process_peer_infos();

    const t_fs_path& self_path = path.get_fs_path_for_self();
    memory::t_meta_holder meta_holder { 1024, 2048, fs.get_paths_in_directory(self_path) };
    t_image_fs_worker image_worker { fs, meta_holder };

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("peer_info_storage", &messenger_context);

    engine.addImageProvider(QLatin1String("default"), new t_ui_async_provider_default_avatar { t_make_avatar_path { path, t_avatar_type::t_default }, image_info_storage, image_worker });
    engine.addImageProvider(QLatin1String("avatars"), new t_ui_async_image_provider          { t_make_avatar_path { path, t_avatar_type::t_squared }, image_info_storage, image_worker });
    engine.addImageProvider(QLatin1String("photos"),  new t_ui_async_image_provider          { t_make_photo_path  { path },                           image_info_storage, image_worker });

    engine.load(url);
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return a.exec();
}
