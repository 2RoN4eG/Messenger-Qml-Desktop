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
inline void do_create_peer_directories(const t_peer_id peer_id, const t_common_fs_path_maker& path, const i_fs_std& fs)
{
    try
    {
        std::vector<t_fs_path> paths
        {
            path.get_avatar_fs_path(peer_id, t_avatar_type_id::t_default_avatar),
            path.get_avatar_fs_path(peer_id, t_avatar_type_id::t_squared_avatar),
            path.get_photo_fs_path(peer_id)
        };

        for (t_fs_path path : paths)
        {
            fs.create_directories(path);
        }
    }
    catch (const std::exception& exception)
    {
        std::cerr << "do_create_peer_directories: exception's what is '" << exception.what() << "'" << std::endl;
    }
}

inline size_t kilobytes(const size_t amount)
{
    return amount * 1024;
}

inline size_t megabytes(const size_t amount)
{
    return kilobytes(amount) * 1024;
}

inline size_t gigabytes(const size_t amount)
{
    return megabytes(amount) * 1024;
}

}


t_application::t_application(int& argument_counter, char** argument_values)
    : _application(argument_counter, argument_values)
    , _self { 1024 }
    , _root { make_root_path(t_messenger_root_path, _self) }
    , _self_path { _root.get_self_fs_path() }
    , _peer_component_storage { _peer_components }
    , _image_component_storage { _image_components }
    , _message_component_storage { _message_components }
    , _peer_context_setter { _peer_component_storage, _image_component_storage, _message_component_storage }
    , _peer_context_getter { _peer_component_storage, _image_component_storage, _message_component_storage }
    , _peer_preview_provider      { &_peer_context_getter }
    , _peer_conversation_provider { &_peer_context_getter }
    , _default_avatar_fs_path_maker { _root, t_avatar_type_id::t_default_avatar }
    , _squared_avatar_fs_path_maker { _root, t_avatar_type_id::t_squared_avatar }
    , _photo_fs_path_maker  { _root }
    , _network_simulator { _peer_context_setter, _message_id_generator, _image_id_generator }
    , _fs {}
    , _meta_holder { megabytes(10), megabytes(20), _fs.get_paths_in_directory(_self_path) }
    , _image_fs_worker { _fs, _meta_holder }
{
    std::cout << "Number of arguments: " << argument_counter << std::endl;
    std::cout << "Arguments passed to the program:" << std::endl;
    for (int argument_index = 0; argument_index < argument_counter; ++argument_index)
    {
        std::cout << argument_index << ": " << argument_values[argument_index] << std::endl;
    }

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

    int result = qmlRegisterType<t_qt_peer_preview_provider>("Bindings", 1, 0, "PeerInfoProvider");
    qDebug() << "register result is" << result;

    result = qmlRegisterType<t_qt_peer_conversation_provider>("Bindings", 1, 0, "PeerConversationProvider");
    qDebug() << "register result is" << result;

    const QUrl url("qrc:///ui/Main.qml");

    auto exiter = [url](QObject* object, const QUrl& object_url) { if (!object && url == object_url) { QCoreApplication::exit(-1); } };

    QObject::connect(&_engine, &QQmlApplicationEngine::objectCreated, &_application, exiter, Qt::QueuedConnection);

    try
    {
        test_common_fs_path_maker();
    }
    catch (const std::exception& exception)
    {
        std::cout << "exception's what is '" << exception.what() << "'" << std::endl;
    }

    _engine.rootContext()->setContextProperty("preview_provider",      &_peer_preview_provider);
    _engine.rootContext()->setContextProperty("conversation_provider", &_peer_conversation_provider);

    _engine.addImageProvider(QLatin1String("default"), new t_qt_default_avatar_provider { _default_avatar_fs_path_maker, _image_component_storage, _image_fs_worker });
    _engine.addImageProvider(QLatin1String("avatars"), new t_qt_image_provider          { _squared_avatar_fs_path_maker, _image_component_storage, _image_fs_worker });
    _engine.addImageProvider(QLatin1String("photos"),  new t_qt_image_provider          { _photo_fs_path_maker,          _image_component_storage, _image_fs_worker });

    _engine.load(url);
    if (_engine.rootObjects().isEmpty())
    {
        throw std::runtime_error { "array root objects is empty" };
    }
}

t_application::~t_application()
{
    // _application.aboutToQuit.connect(_engine.deleteLater());
}

int t_application::exec()
{
    return QGuiApplication::exec();
}
