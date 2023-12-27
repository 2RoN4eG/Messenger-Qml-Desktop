#include "t_image_downloader_async.h"

#include <QNetworkReply>
#include <QImage>

#include <iostream>

t_avatar_downloader_async::t_avatar_downloader_async(const t_avatar_id avatar_id)
    : _avatar_id { avatar_id }
{
    connect(&_network, &QNetworkAccessManager::finished, this, &t_avatar_downloader_async::on_finished, Qt::QueuedConnection);
}

void t_avatar_downloader_async::run(const t_url& url) {
    if (!url.isValid()) {
        throw std::runtime_error { "url to run async downloading is not valid" };
    }

    _network.get(QNetworkRequest { url });
}

t_avatar_id t_avatar_downloader_async::get_avatar_id() const {
    return _avatar_id;
}

t_qt_avatar t_avatar_downloader_async::get_avatar() const {
    return _avatar;
}

void t_avatar_downloader_async::on_finished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        emit error_happend("some network error has happend");
        return;
    }

    _avatar = QImage::fromData(reply->readAll());
    reply->deleteLater();

    emit downloaded(_avatar_id);
}
