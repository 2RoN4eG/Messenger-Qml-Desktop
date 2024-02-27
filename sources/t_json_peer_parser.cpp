#include "t_json_peer_parser.h"

#include "t_fs.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include <iostream>
#include "interface/i_peer_info_storage.h"


namespace {
    using t_qt_json_object = QJsonObject;
    using t_qt_json_array = QJsonArray;
    using t_qt_json_value = QJsonValue;

    t_json_avatar_model process_peer_avatar(const t_qt_json_object& json_object) {
        return {
            json_object["thumb_hash"].toString().toStdString(),
            json_object["url"].toString()
        };
    }

    void process_peer_avatar(i_set_peer_info& peer_info_storage, const t_peer_id peer_id, const t_qt_json_object& json_object) {
        peer_info_storage.set_image_info(
                peer_id,
                json_object["url"].toString(),
                json_object["thumb_hash"].toString().toStdString()
            );
    }

    void process_peer_avatars(i_set_peer_info& peer_info_storage, const t_peer_id peer_id, const t_qt_json_array& json_array) {
        for (const t_qt_json_value& json_value : json_array) {
            process_peer_avatar(peer_info_storage, peer_id, json_value.toObject());
        }
    }

    t_json_model_last_message parse_peer_last_message(const t_qt_json_object& json_object) {
        return {
            json_object.value("text").toString().toStdString(),
            json_object.value("timestamp").toInt()
        };
    }

    void process_peer(i_set_peer_info& peer_info_storage, const t_qt_json_object& json_object) {

        t_peer_id peer_id   = json_object["peer"].toInt();
        t_nickname&& nickname = json_object["nickname"].toString().toStdString();

        peer_info_storage.set_peer_info(peer_id, std::move(nickname));

        process_peer_avatars(peer_info_storage, peer_id, json_object["avatars"].toArray());
        // parse_peer_last_message(peer_info_storage, peer_id, json_object["last_message"].toObject());
    }

    void process_peers(i_set_peer_info& peer_info_storage, const t_qt_json_array& json_array) {
        for (const t_qt_json_value& json_value : json_array) {
            process_peer(peer_info_storage, json_value.toObject());
        }
    }
}

    t_json_peer_info_processor::t_json_peer_info_processor(i_set_peer_info& peer_info_storage)
    : _peer_info_storage { peer_info_storage }
{
}

void t_json_peer_info_processor::operator()(const std::string_view json) const {
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(QByteArray::fromRawData(json.data(), json.size()), &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Error parsing JSON:" << error.errorString();
        qWarning() << "JSON:" << QString { json.data() };
        return;
    }

    const t_qt_json_object& json_object = document.object();

    process_peers(_peer_info_storage, json_object["peers"].toArray());

    return;
}

void t_json_peer_info_processor::operator()(const t_fs_path& path, const i_fs& fs) const {
    (*this)(fs.read_as_single_line(path));
}

void print_json_model_avatar(const t_json_avatar_model& avatar) {
    std::cout << "thumb_hash   : " << avatar.get_thumb_hash() << std::endl;
    std::cout << "url          : " << avatar.get_url().toString().toStdString() << std::endl;
}

void print_json_avatar_models(const t_json_avatar_models& avatars) {
    for (const t_json_avatar_model& avatar : avatars) {
        print_json_model_avatar(avatar);
    }
}

void print_json_model_last_message(const t_json_model_last_message& last_message) {
    std::cout << "text         : " << last_message.get_text() << std::endl;
    std::cout << "timestamp    : " << last_message.get_timestamp() << std::endl;
}

void print_json_model_peer(const t_json_peer_info_model& peer) {
    std::cout << std::endl;
    std::cout << "peer         : " << peer.peer_id().to_string() << std::endl;
    std::cout << "nickname     : " << peer.nickname() << std::endl;

    // std::cout << "avatars" << std::endl;
    // print_json_avatar_models(peer.avatar());

    std::cout << "last_message" << std::endl;
    print_json_model_last_message(peer.last_message());
}

void print_json_model_peers(t_json_peer_models&& peers) {
    for (const t_json_peer_info_model& peer : peers) { print_json_model_peer(peer); }
}
