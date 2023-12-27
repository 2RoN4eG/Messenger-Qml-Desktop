#ifndef T_IMAGE_DOWNLOADER_ASYNC_H
#define T_IMAGE_DOWNLOADER_ASYNC_H

#include "t_defines.h"

#include <QObject>
#include <QNetworkAccessManager>

class QNetworkReply;

class i_avatar_downloader_async : public QObject {
    Q_OBJECT

public:
    virtual void run(const t_url& url) = 0;

    virtual t_avatar_id get_avatar_id() const = 0;

    virtual t_qt_avatar get_avatar() const = 0;

signals:
    void downloaded(const t_avatar_id avatar_id);

    void error_happend(const t_error& error);
};

class t_avatar_downloader_async : public i_avatar_downloader_async {
    Q_OBJECT

public:
    t_avatar_downloader_async(const t_avatar_id avatar_id);

    void run(const t_url& url) override;

    t_avatar_id get_avatar_id() const override;

    t_qt_avatar get_avatar() const override;

private slots:
    void on_finished(QNetworkReply* reply);

protected:
    t_qt_avatar _avatar;

    const t_avatar_id _avatar_id;

private:
    QNetworkAccessManager _network;
};

using t_avatar_downloader_async_pointer = std::unique_ptr<t_avatar_downloader_async>;

#endif // T_IMAGE_DOWNLOADER_ASYNC_H
