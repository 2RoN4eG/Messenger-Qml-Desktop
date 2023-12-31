#include "t_ui_model_peers.h"

t_ui_model_peers::t_ui_model_peers(t_json_model_peers&& peers, QObject* parent)
    : QAbstractListModel(parent)
    , _peers { std::move(peers) }
{
    _peers.resize(25);
}

int t_ui_model_peers::rowCount(const QModelIndex &parent) const {
//    if (parent.isValid())
//        return 0;

    return (int)_peers.size();
}

QVariant t_ui_model_peers::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    return QVariant();
}

t_json_model_peer* t_ui_model_peers::get_peer(const int index)
{
    return &_peers[index];
}
