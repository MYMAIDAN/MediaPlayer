#include "playlistmodel.h"
#include <QDebug>
#include <QFileInfo>
#include <QMediaPlayer>

PlayListModel::PlayListModel(const QStringList &list, QObject *parent):
  QAbstractListModel(parent),
  m_Data(list)
{
}

PlayListModel::PlayListModel(QObject *parent):
  QAbstractListModel(parent)
{

}

PlayListModel::~PlayListModel()
{

}

QVariant PlayListModel::data(const QModelIndex &index, int nRole) const
{
  if( !index.isValid() )
  {
    return QVariant();
  }
  if( index.row() < 0 || index.row() >= m_Data.size() )
  {
    return QVariant();
  }

  return (nRole == Qt::DisplayRole || nRole == Qt::EditRole )
      ? m_Data.at( index.row() )
      : QVariant();
}

bool PlayListModel::setData(const QModelIndex &index, const QVariant &value, int nRole)
{
  if( index.isValid() && nRole == Qt::EditRole )
  {
    m_Data.replace( index.row(), value.value<QString>() );
    emit dataChanged( index, index );
    return true;
  }
  return false;
}

int PlayListModel::rowCount(const QModelIndex &parent /* =QModelIndex() */) const
{
  if( parent.isValid() )
  {
    return 0;
  }
  return m_Data.size();
}

Qt::ItemFlags PlayListModel::flags( const QModelIndex& index ) const
{
  Qt::ItemFlags flags = QAbstractListModel::flags(index);
  return index.isValid() ? ( flags | Qt::ItemIsEditable )
                         : flags;
}

void PlayListModel::addNewMediaFile(const QString &path)
{
beginInsertRows(QModelIndex(),m_Data.size()-1,m_Data.size()-1);
  m_Data.push_back(path);
  QFileInfo file(path);

endInsertRows();
  qDebug() <<   file;
}

void PlayListModel::play(const QModelIndex& index)
{
  QVariant value = index.data();
  QMediaPlayer* player = new QMediaPlayer;
  player->setMedia(index.data().toUrl());
  player->setVolume(50);
  player->play();
}
