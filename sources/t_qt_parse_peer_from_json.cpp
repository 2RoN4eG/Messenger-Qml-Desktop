#include "t_qt_parse_peer_from_json.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>


//const auto json = R"(
//        {
//          "self": 1024,
//          "peers": [
//            {
//              "peer": 2048,
//              "nickname": "Albert Einstein",
//              "avatars": [
//                {
//                  "thumb_hash": "",
//                  "url": "https://hips.hearstapps.com/hmg-prod/images/albert-einstein-sticks-out-his-tongue-when-asked-by-news-photo-1681316749.jpg"
//                },
//                {
//                  "thumb_hash": "",
//                  "url": "https://www.nobelprize.org/images/einstein-12923-portrait-medium.jpg"
//                },
//                {
//                  "thumb_hash": "",
//                  "url": "https://assets.editorial.aetnd.com/uploads/2009/10/albert-einstein-gettyimages-544750041.jpg"
//                }
//              ],
//              "last_message": {
//                "message_text": "Hello, I'm Albert Einstein and I'm genious",
//                "message_timestamp": 100
//              }
//            },
//            {
//              "peer": 2049,
//              "nickname": "Albus Dumbledore",
//              "last_message": {
//                "message_text": "Hello, I am Albus Dumbledore. I wanna show you a bit magic ...",
//                "message_timestamp": 100
//              },
//              "avatars": [
//                {
//                  "thumb_hash": "",
//                  "url": "https://images.ctfassets.net/usf1vwtuqyxm/1dmmUJzpRcWaUmMOCu8QwO/7e013145694566076d47fd004fd604c2/AlbusDumbledore_WB_F6_DumbledoreSittingInChair_Promo_080615_Port.jpg?w=914&q=70&fm=jpg"
//                },
//                {
//                  "thumb_hash": "",
//                  "url": "https://creations.mattel.com/cdn/shop/products/e4g44r0kigsn14peqbtj_1024x.jpg?v=1699999014"
//                },
//                {
//                  "thumb_hash": "",
//                  "url": "https://static.wikia.nocookie.net/wikihp/images/8/88/Dumbledore.jpg/revision/latest?cb=20090911073332&path-prefix=es"
//                }
//              ]
//            }
//          ]
//        }
//    )";

t_avatar_model parse_peer_avatar(const QJsonObject& json_object) {
    return {
        json_object["thumb_hash"].toString().toStdString(),
        json_object["url"].toString()
    };
}

t_avatar_models parse_peer_avatars(const QJsonArray& json_array) {
    t_avatar_models avatar_models {};

    for (const QJsonValue& json_value : json_array) {
        avatar_models.emplace_back(
            parse_peer_avatar(
                json_value.toObject()
            )
        );
    }

    return avatar_models;
}

t_last_message_model parse_peer_last_message(const QJsonObject& json_object) {
    return {
        json_object["message_text"].toString().toStdString(),
        json_object["message_timestamp"].toInteger()
    };
}

t_peer_model parse_peer(const QJsonObject& json_object) {
    return {
        json_object["peer"].toInteger(),
        json_object["nickname"].toString().toStdString(),
        parse_peer_avatars(json_object["avatars"].toArray()),
        parse_peer_last_message(json_object["last_message"].toObject())
    };
}

t_peer_models parse_peers(const QJsonArray& json_array) {
    t_peer_models peer_models {};

    for (const QJsonValue& json_value : json_array) {
        peer_models.emplace_back(
            parse_peer(
                json_value.toObject()
                )
            );
    }

    return peer_models;
}


t_peer_models t_qt_parse_peer_from_json::operator()(const std::string_view json) const {
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(QByteArray::fromRawData(json.data(), json.size()), &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Error parsing JSON:" << error.errorString();
        return {};
    }

    const QJsonObject& json_object = document.object();

    return parse_peers(
            json_object["peers"].toArray()
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
