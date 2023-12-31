#ifndef T_UI_MODEL_PEERS_H
#define T_UI_MODEL_PEERS_H

#include "t_defines.h"

#include <QAbstractListModel>

class t_ui_model_peers : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit t_ui_model_peers(t_json_model_peers&& peers = t_json_model_peers {}, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE t_json_model_peer* get_peer(const int index);

private:
    t_json_model_peers _peers;
};

#endif // T_UI_MODEL_PEERS_H
