#include "t_json_parse_peer.h"

#include "t_fs.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

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
            json_object["message_text"].toString().toStdString(),
            json_object["message_timestamp"].toInteger()
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

    t_json_model_peers t_json_parse_peer::operator()(const std::string_view json) const {
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

    t_json_model_peers t_json_parse_peer::from_file(const i_fs& fs, const t_fs_path& path) const {
        return (*this)(
                fs.read_as_single_line(path)
            );
    }

//void print(const t_avatar_model& avatar) {
//    std::cout << "thumb_hash   : " << avatar.get_thumb_hash() << std::endl;
//    std::cout << "url          : " << avatar.get_url().toString().toStdString() << std::endl;
//}

//void print(const t_avatar_models& avatars) {
//    for (const t_avatar_model& avatar : avatars) {
//        print(avatar);
//    }
//}

//void print(const t_last_message_model& last_message) {
//    std::cout << "text         : " << last_message.get_text() << std::endl;
//    std::cout << "timestamp    : " << (long long)last_message.get_timestamp() << std::endl;
//}

//void print(const t_peer_model& peer) {
//    std::cout << std::endl;
//    std::cout << "peer         : " << peer.get_peer_id().to_string() << std::endl;
//    std::cout << "nickname     : " << peer.get_nickname() << std::endl;

//    std::cout << "avatars" << std::endl;
//    print(peer.get_avatars());

//    std::cout << "last_message" << std::endl;
//    print(peer.get_last_message());
//}

//void print(const t_peer_models& peers) {
//    for (const t_peer_model peer : peers) {
//        print(peer);
//    }
//}

//void test_t_qt_json_parser_peer_from_json() {
//    const t_peer_models& peers = t_qt_json_parser_peer_from_json {}.parse(json);
//    print(peers);
//}
