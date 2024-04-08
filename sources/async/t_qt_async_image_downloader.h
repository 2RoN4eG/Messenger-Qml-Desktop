#ifndef T_t_qt_async_image_downloader_H
#define T_t_qt_async_image_downloader_H

#include "../t_defines.h"

#include <QObject>
#include <QNetworkAccessManager>

#include <iostream>

class QNetworkReply;

class i_t_qt_async_image_downloader
    : public QObject
{
    Q_OBJECT

public:
    virtual ~i_t_qt_async_image_downloader() = 0;

    virtual void run(const t_image_id image_id, const t_url& url) = 0;

    virtual t_image_id get_image_id() const = 0;

    virtual t_ui_image get_image() const = 0;

protected:
    void emit_error_happend(const t_error& error)
    {
        std::cerr << "error: " << error << std::endl;

        emit error_happend(error);
    }

    void emit_downloaded(const t_image_id image_id)
    {
        std::cerr << "downloaded: " << image_id << std::endl;

        emit downloaded(image_id);
    }

signals:
    void downloaded(const t_image_id image_id);

    void error_happend(const t_error& error);
};

namespace async
{
    class t_qt_async_image_downloader
        : public i_t_qt_async_image_downloader
    {
        Q_OBJECT

    public:
        t_qt_async_image_downloader();
        ~t_qt_async_image_downloader() override = default;

        void run(const t_image_id image_id, const t_url& url) override;

        t_image_id get_image_id() const override;

        t_ui_image get_image() const override;

    private slots:
        void on_finished(QNetworkReply* reply);

    protected:
        t_image_id _image_id;

        t_ui_image _image;

    private:
        QNetworkAccessManager _network;
    };

    
    using t_qt_async_image_downloader_pointer = std::unique_ptr<t_qt_async_image_downloader>;

    t_qt_async_image_downloader_pointer make_qt_async_image_downloader();
} // namespace async

#endif // T_t_qt_async_image_downloader_H
