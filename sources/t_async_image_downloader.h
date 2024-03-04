#ifndef T_ASYNC_IMAGE_DOWNLOADER_H
#define T_ASYNC_IMAGE_DOWNLOADER_H

#include "t_defines.h"

#include <QObject>
#include <QNetworkAccessManager>

class QNetworkReply;

class i_async_image_downloader : public QObject
{
    Q_OBJECT

public:
    virtual void run(const t_image_id image_id, const t_url& url) = 0;

    virtual t_image_id get_image_id() const = 0;

    virtual t_qt_image get_image() const = 0;

signals:
    void downloaded(const t_image_id image_id);

    void error_happend(const t_error& error);
};

class t_async_image_downloader : public i_async_image_downloader
{
    Q_OBJECT

public:
    t_async_image_downloader();

    void run(const t_image_id image_id, const t_url& url) override;

    t_image_id get_image_id() const override;

    t_qt_image get_image() const override;

private slots:
    void on_finished(QNetworkReply* reply);

protected:
    t_image_id _image_id;

    t_qt_image _image;

private:
    QNetworkAccessManager _network;
};

using t_async_image_downloader_pointer = std::unique_ptr<t_async_image_downloader>;

#endif // T_ASYNC_IMAGE_DOWNLOADER_H
