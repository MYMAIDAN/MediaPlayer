#include "playlistmodel.h"
#include <QDebug>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QMediaMetaData>

PlayListModel::PlayListModel(const QStringList &list, QObject *parent):
  QAbstractTableModel(parent)
{
}

PlayListModel::PlayListModel(QObject *parent):
  QAbstractTableModel(parent),
  m_HeaderSectionTitle({"Titile","AlbumArtist","TrackNumber","Genre","Year"})
{
}

PlayListModel::~PlayListModel()
{

}

QVariant PlayListModel::data(const QModelIndex &index, int nRole) const
{
  auto row      = index.row();
  auto column   = index.column();
  if( !index.isValid() )
  {
    return QVariant();
  }
  if( index.row() < 0 || index.row() >= m_Data.size() )
  {
    return QVariant();
  }

  if(nRole == Qt::DisplayRole)
  {
    switch (column)
    {
      case 0:
        return m_Data[row].second.albumTitle;
      case 1:
        return m_Data[row].second.albumArtist;
      case 2:
        return m_Data[row].second.genre;
      case 3:
        return m_Data[row].second.trackNumber;
      case 4:
        return m_Data[row].second.year;
      default:
        return 0;
    }
  }
  return QVariant();
}

int PlayListModel::columnCount(const QModelIndex &parent) const
{
  return 5;
}

int PlayListModel::rowCount(const QModelIndex &parent /* =QModelIndex() */) const
{
  return m_Data.size();
}

Qt::ItemFlags PlayListModel::flags( const QModelIndex& index ) const
{
  Qt::ItemFlags flags = QAbstractTableModel::flags(index);
  return index.isValid() ? ( flags | Qt::ItemIsEditable )
                         : flags;
}

QVariant PlayListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_HeaderSectionTitle[section];
    }
    return QVariant();
}

void PlayListModel::addNewMediaFile(const QString &path)
{
beginInsertRows(QModelIndex(),m_Data.size()-1,m_Data.size()-1);
  m_player.setMedia(QUrl::fromLocalFile(path));
  m_player.play();
  SMediaMetaData metaData;
  if(m_player.isMetaDataAvailable())
    {
      QVariant data = m_player.metaData(QMediaMetaData::AlbumTitle);
      metaData.albumTitle = data.isNull() ? QString() : data.toString();

      data = m_player.metaData(QMediaMetaData::AlbumArtist);
      metaData.albumArtist = data.isNull() ? QString() : data.toString();

      data = m_player.metaData(QMediaMetaData::Year);
      metaData.year = data.isNull() ? 0 : data.toInt();

      data = m_player.metaData(QMediaMetaData::Genre);
      metaData.genre = data.isNull() ? QStringList() : data.toStringList();

      data = m_player.metaData(QMediaMetaData::TrackNumber);
      metaData.trackNumber = data.isNull() ? 0 : data.toInt();

      m_Data.insert(m_Data.size(),{path,metaData});

      QFileInfo file(path);

    endInsertRows();
      qDebug() <<   file;

    }

}

void PlayListModel::play(const QModelIndex& index)
{
  QVariant value = index.data();
  QMediaPlayer* player = new QMediaPlayer;
  player->setMedia(index.data().toUrl());
  player->setVolume(50);
  player->play();
}
