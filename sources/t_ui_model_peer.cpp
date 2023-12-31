#include "t_ui_model_peer.h"

t_ui_model_peer::t_ui_model_peer(QObject *parent)
    : QAbstractListModel(parent)
{
}

int t_ui_model_peer::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;

    return (int)_peers.size();
}

QVariant t_ui_model_peer::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    return QVariant();
}
