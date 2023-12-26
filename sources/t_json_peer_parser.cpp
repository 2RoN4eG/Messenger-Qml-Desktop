#include "t_json_peer_parser.h"

#include "t_fs.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include <iostream>

namespace {
    using t_qt_json_object = QJsonObject;
    using t_qt_json_array = QJsonArray;
    using t_qt_json_value = QJsonValue;

    t_json_model_avatar parse_peer_avatar(const t_qt_json_object& json_object) {
        return {
            json_object["thumb_hash"].toString().toStdString(),
            json_object["url"].toString()
        };
    }

    t_json_model_avatars parse_peer_avatars(const t_qt_json_array& json_array) {
        t_json_model_avatars avatar_models {};

        for (const t_qt_json_value& json_value : json_array) {
            avatar_models.emplace_back(
                parse_peer_avatar(
                        json_value.toObject()
                    )
                );
        }

        return avatar_models;
    }

    t_json_model_last_message parse_peer_last_message(const t_qt_json_object& json_object) {
        return {
            json_object.value("text").toString().toStdString(),
            json_object.value("timestamp").toInteger()
        };
    }

    t_json_model_peer parse_peer(const t_qt_json_object& json_object) {
        return {
            json_object["peer"].toInteger(),
            json_object["nickname"].toString().toStdString(),
            parse_peer_avatars(json_object["avatars"].toArray()),
            parse_peer_last_message(json_object["last_message"].toObject())
        };
    }

    t_json_model_peers parse_peers(const t_qt_json_array& json_array) {
        t_json_model_peers peer_models {};

        for (const t_qt_json_value& json_value : json_array) {
            peer_models.emplace_back(
                parse_peer(
                        json_value.toObject()
                    )
                );
        }

        return peer_models;
    }
}

t_json_model_peers t_json_peer_parser::operator()(const std::string_view json) const {
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(QByteArray::fromRawData(json.data(), json.size()), &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Error parsing JSON:" << error.errorString();
        return {};
    }

    const t_qt_json_object& json_object = document.object();

    return parse_peers(
            json_object["peers"].toArray()
        );
}
    
t_json_model_peers t_json_peer_parser::from_file(const i_fs& fs, const t_fs_path& path) const {
    return (*this)(
            fs.read_as_single_line(path)
        );
}

void print_json_model_avatar(const t_json_model_avatar& avatar) {
    std::cout << "thumb_hash   : " << avatar.get_thumb_hash() << std::endl;
    std::cout << "url          : " << avatar.get_url().toString().toStdString() << std::endl;
}

void print_json_model_avatars(const t_json_model_avatars& avatars) {
    for (const t_json_model_avatar& avatar : avatars) { print_json_model_avatar(avatar); }
}

void print_json_model_last_message(const t_json_model_last_message& last_message) {
    std::cout << "text         : " << last_message.get_text() << std::endl;
    std::cout << "timestamp    : " << last_message.get_timestamp() << std::endl;
}

void print_json_model_peer(const t_json_model_peer& peer) {
    std::cout << std::endl;
    std::cout << "peer         : " << peer.get_peer_id().to_string() << std::endl;
    std::cout << "nickname     : " << peer.get_nickname() << std::endl;

    std::cout << "avatars" << std::endl;
    print_json_model_avatars(peer.get_avatars());

    std::cout << "last_message" << std::endl;
    print_json_model_last_message(peer.get_last_message());
}

void print_json_model_peers(t_json_model_peers&& peers) {
    for (const t_json_model_peer& peer : peers) { print_json_model_peer(peer); }
}
