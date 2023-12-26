#include "t_qt_async_image_downloader.h"

#include <QNetworkReply>
#include <QImage>

i_t_qt_async_image_downloader::~i_t_qt_async_image_downloader()
{
}

namespace async
{
    t_qt_async_image_downloader::t_qt_async_image_downloader()
    {
        connect(&_network, &QNetworkAccessManager::finished, this, &t_qt_async_image_downloader::on_finished, Qt::QueuedConnection);
    }

    void t_qt_async_image_downloader::run(const t_image_id image_id, const t_url& url)
    {
        _image_id = image_id;

        if (!url.isValid())
        {
            throw std::runtime_error { "url to run async downloading is not valid" };
        }

        _network.get(QNetworkRequest { url });
    }

    t_image_id t_qt_async_image_downloader::get_image_id() const
    {
        return _image_id;
    }

    t_ui_image t_qt_async_image_downloader::get_image() const
    {
        return _image;
    }

    void t_qt_async_image_downloader::on_finished(QNetworkReply *reply)
    {
        if (reply->error() != QNetworkReply::NoError)
        {
            emit_error_happend("Network error has happend");
            return;
        }

        _image = QImage::fromData(reply->readAll());
        reply->deleteLater();

        emit_downloaded(_image_id);
    }


    t_qt_async_image_downloader_pointer make_qt_async_image_downloader()
    {
        return std::make_unique<async::t_qt_async_image_downloader>();
    }
} // namespace async
