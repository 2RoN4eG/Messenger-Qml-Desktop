#ifndef T_UI_MODEL_PEER_H
#define T_UI_MODEL_PEER_H

#include "t_defines.h"

#include <QAbstractListModel>

class t_ui_model_peer : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit t_ui_model_peer(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    t_json_model_peers _peers;
};

#endif // T_UI_MODEL_PEER_H
