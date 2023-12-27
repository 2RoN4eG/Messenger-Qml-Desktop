#include <QGuiApplication>
#include <QLocale>
#include <QTranslator>
#include <QNetworkAccessManager>
#include <QQmlApplicationEngine>

#include "t_image_storage_memory.h"
#include "t_image_info_storage_memory.h"
#include "t_meta_holder_memory.h"
#include "t_path_maker.h"
#include "t_ui_default_avatar_provider.h"
#include "t_ui_squared_avatar_provider.h"
#include "t_fs.h"

#include <iostream>

void do_create_peer_directories(const t_peer_id& self, const t_peer_id peer_id, const i_path_maker& path_maker, const i_fs& fs) {
    fs.do_create_directories(
        path_maker.make_path_for_avatar(peer_id, t_avatar_type::t_default)
        );

    fs.do_create_directories(
        path_maker.make_path_for_avatar(peer_id, t_avatar_type::t_squared)
        );

    fs.do_create_directories(
        path_maker.make_path_for_photo(peer_id)
        );
}

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    const QUrl url("qrc:///ui/Main.qml");
    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &a,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    try {
        test_path_maker();
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
    const t_path_maker path_maker = make_path_maker("/Users/2RoN4eG/", self);

    try {
        do_create_peer_directories(self, t_peer_id { 2048 }, path_maker, fs);
        do_create_peer_directories(self, t_peer_id { 2049 }, path_maker, fs);
        do_create_peer_directories(self, t_peer_id { 2050 }, path_maker, fs);
        do_create_peer_directories(self, t_peer_id { 2051 }, path_maker, fs);
        do_create_peer_directories(self, t_peer_id { 2052 }, path_maker, fs);
        do_create_peer_directories(self, t_peer_id { 2053 }, path_maker, fs);
    }
    catch (const std::exception& exception) {
        std::cout << "exception's what " << exception.what() << std::endl;
    }

    t_image_info_storage_memory image_info_storage {};

    do {
        image_info_storage.set_image_info(t_avatar_id { 1 }, t_peer_id { 2048 }, t_url { "https://images.pexels.com/photos/19467240/pexels-photo-19467240/free-photo-of-hand-holding-coffee-cup.jpeg" },       {});
        image_info_storage.set_image_info(t_avatar_id { 2 }, t_peer_id { 2049 }, t_url { "https://images.pexels.com/photos/18926843/pexels-photo-18926843/free-photo-of-rough-volcanic-rock-formation.jpeg" }, {});
        image_info_storage.set_image_info(t_avatar_id { 3 }, t_peer_id { 2048 }, t_url { "https://images.pexels.com/photos/15561988/pexels-photo-15561988/free-photo-of-man-travelling-on-a-ferry.jpeg" },     {});

        image_info_storage.set_image_info(t_avatar_id { 4 }, t_peer_id { 2053 }, t_url { "https://images.pexels.com/photos/19467240/pexels-photo-19467240/free-photo-of-hand-holding-coffee-cup.jpeg" },       {});
        image_info_storage.set_image_info(t_avatar_id { 5 }, t_peer_id { 2049 }, t_url { "https://images.pexels.com/photos/18926843/pexels-photo-18926843/free-photo-of-rough-volcanic-rock-formation.jpeg" }, {});
        image_info_storage.set_image_info(t_avatar_id { 6 }, t_peer_id { 2050 }, t_url { "https://images.pexels.com/photos/15561988/pexels-photo-15561988/free-photo-of-man-travelling-on-a-ferry.jpeg" },     {});
    } while (false);

    const t_path& self_path = path_maker.make_path_for_self();
    t_meta_holder_memory meta_holder { 1024, 2048, fs.get_paths_in_directory(self_path) };
    t_image_storage_memory avatar_storage { fs, meta_holder };

    engine.addImageProvider(QLatin1String("default"), new t_ui_default_avatar_provider { t_avatar_path_holder { path_maker, t_avatar_type::t_default }, image_info_storage, avatar_storage });
    engine.addImageProvider(QLatin1String("avatars"), new t_ui_squared_avatar_provider { t_avatar_path_holder { path_maker, t_avatar_type::t_squared }, image_info_storage, avatar_storage });
    engine.addImageProvider(QLatin1String("photos"),  new t_ui_squared_avatar_provider { t_photo_path_holder  { path_maker },                           image_info_storage, avatar_storage });

    engine.load(url);
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return a.exec();
}
