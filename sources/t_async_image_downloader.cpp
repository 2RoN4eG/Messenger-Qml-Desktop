#include "t_async_image_downloader.h"

#include <QNetworkReply>
#include <QImage>
#include <iostream>


t_async_image_downloader::t_async_image_downloader()

{
    connect(&_network, &QNetworkAccessManager::finished, this, &t_async_image_downloader::on_finished, Qt::QueuedConnection);
}

void t_async_image_downloader::run(const t_image_id image_id, const t_url& url) {
    _image_id = image_id;
    std::cout << "t_async_image_downloader::run(const t_image_id image_id { " << _image_id << " }, const t_url& url)" << std::endl;

    if (!url.isValid()) {
        throw std::runtime_error { "url to run async downloading is not valid" };
    }

    _network.get(QNetworkRequest { url });
}

t_image_id t_async_image_downloader::get_image_id() const {
    return _image_id;
}

t_qt_image t_async_image_downloader::get_image() const {
    return _image;
}

void t_async_image_downloader::on_finished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        emit error_happend("some network error has happend");
        return;
    }

    _image = QImage::fromData(reply->readAll());
    reply->deleteLater();

    emit downloaded(_image_id);
}
