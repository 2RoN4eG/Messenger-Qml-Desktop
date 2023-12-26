#include "t_application.h"

#include <QGuiApplication>


#include <QLocale>
#include <QTranslator>
#include <QNetworkAccessManager>
#include <QQmlApplicationEngine>
#include <QMetaType>
#include <QQmlContext>

#include <iostream>

#include "ui/t_qt_default_avatar_provider.h"
#include "ui/t_qt_image_provider.h"

namespace
{
    void do_create_peer_directories(const t_peer_id peer_id, const t_fs_common_paths& path, const i_fs_std& fs)
    {
        try
        {
            fs.do_create_directories(
                path.get_fs_path_for_avatar(peer_id, t_avatar_type_id::t_default_avatar)
                );

            fs.do_create_directories(
                path.get_fs_path_for_avatar(peer_id, t_avatar_type_id::t_squared_avatar)
                );

            fs.do_create_directories(
                path.get_fs_path_for_photo(peer_id)
                );
        }
        catch (const std::exception& exception)
        {
            std::cerr << "do_create_peer_directories: exception's what is '" << exception.what() << "'" << std::endl;
        }
    }
}


t_application::t_application(int& argc, char** argv)
    : _application(argc, argv)
    , _self { 1024 }
    , _root { make_common_path("/Users/2RoN4eG/1024/", _self) }
    , _self_path { _root.get_fs_path_for_self() }
    , _peer_info_storage { _peer_infos }
    , _image_info_storage { _image_infos }
    , _message_info_storage { _message_infos }
    , _peer_context_setter { _peer_info_storage, _image_info_storage, _message_info_storage }
    , _peer_context_getter { _peer_info_storage, _image_info_storage, _message_info_storage }
    , _peer_preview_provider      { &_peer_context_getter }
    , _peer_conversation_provider { &_peer_context_getter }
    , _default_avatar_fs_path_maker { _root, t_avatar_type_id::t_default_avatar }
    , _squared_avatar_fs_path_maker { _root, t_avatar_type_id::t_squared_avatar }
    , _photo_fs_path_maker  { _root }
    , _network_simulator { _peer_context_setter, _message_id_generator, _image_id_generator }
    , _fs {}
    , _meta_holder { 10 * 1024 * 1024, 20 * 1024 * 1024, _fs.get_paths_in_directory(_self_path) }
    , _image_fs_worker { _fs, _meta_holder }
{
    // try
    // {
    //     _fs.do_directories_remove("/Users/2RoN4eG/1024");
    // }
    // catch (const std::exception& exception)
    // {
    //     std::cout << "exception's what is '" << exception.what() << "'" << std::endl;
    // }

    try
    {
        do_create_peer_directories(t_peer_id { 1024 }, _root, _fs);
        do_create_peer_directories(t_peer_id { 2048 }, _root, _fs);
        do_create_peer_directories(t_peer_id { 2049 }, _root, _fs);
        do_create_peer_directories(t_peer_id { 2050 }, _root, _fs);
        do_create_peer_directories(t_peer_id { 2051 }, _root, _fs);
        do_create_peer_directories(t_peer_id { 2052 }, _root, _fs);
        do_create_peer_directories(t_peer_id { 2053 }, _root, _fs);
        do_create_peer_directories(t_peer_id { 4096 }, _root, _fs);
    }
    catch (const std::exception& exception)
    {
        std::cout << "exception's what " << exception.what() << std::endl;
    }

    int result = qmlRegisterType<t_peer_preview_provider>("Bindings", 1, 0, "PeerInfoProvider");
    qDebug() << "register result is" << result;

    result = qmlRegisterType<t_peer_conversation_provider>("Bindings", 1, 0, "PeerConversationProvider");
    qDebug() << "register result is" << result;

    const QUrl url("qrc:///ui/Main.qml");

    QObject::connect(&_engine,
        &QQmlApplicationEngine::objectCreated,
        &_application,
        [url](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
        );

    try
    {
        test_fs_common_paths();
    }
    catch (const std::exception& exception)
    {
        std::cout << "exception's what is '" << exception.what() << "'" << std::endl;
    }

    // print(self);

    _engine.rootContext()->setContextProperty("preview_provider",      &_peer_preview_provider);
    _engine.rootContext()->setContextProperty("conversation_provider", &_peer_conversation_provider);

    _engine.addImageProvider(QLatin1String("default"), new t_qt_default_avatar_provider { _default_avatar_fs_path_maker, _image_info_storage, _image_fs_worker });
    _engine.addImageProvider(QLatin1String("avatars"), new t_qt_image_provider          { _squared_avatar_fs_path_maker, _image_info_storage, _image_fs_worker });
    _engine.addImageProvider(QLatin1String("photos"),  new t_qt_image_provider          { _photo_fs_path_maker,          _image_info_storage, _image_fs_worker });

    _engine.load(url);
    if (_engine.rootObjects().isEmpty())
    {
        throw std::runtime_error { "array root objects is empty" };
    }

    // i_rotator& rotator = meta_holder;
    // meta_holder.do_rotate(fs);
}

t_application::~t_application()
{
    std::cout << "t_application::~t_application()" << std::endl;

    std::cout << "t_application::~t_application(): _engine.~QQmlApplicationEngine()" << std::endl;

    _engine.~QQmlApplicationEngine();

    std::cout << "t_application::~t_application(): _application.~QGuiApplication()" << std::endl;

    _application.~QGuiApplication();
}

int t_application::exec() {
    return QGuiApplication::exec();
}
