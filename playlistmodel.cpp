#include "playlistmodel.h"
#include <QDebug>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QDir>

PlayListModel::PlayListModel( [[maybe_unused]] const QStringList &list, QObject *parent):
  QAbstractTableModel(parent)
{
}

PlayListModel::PlayListModel(QObject *parent):
  QAbstractTableModel(parent),
  m_HeaderSectionTitle({"TrackName","Folder","Type","Size"})
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
        return m_Data[row].fileName;
      case 1:
        return m_Data[row].fileDir;
      case 2:
        return m_Data[row].fileType;
      case 3:
        return QString::number( m_Data[row].fileSize ) + "Mb";
      default:
        return 0;
    }
  }
  return QVariant();
}

int PlayListModel::columnCount( [[maybe_unused]] const QModelIndex &parent) const
{
  return m_HeaderSectionTitle.size();
}

int PlayListModel::rowCount( [[maybe_unused]] const QModelIndex &parent /* =QModelIndex() */) const
{
  return m_Data.size();
}

Qt::ItemFlags PlayListModel::flags( const QModelIndex& index ) const
{
  Qt::ItemFlags flags = QAbstractTableModel::flags(index);
  return index.isValid() ? ( flags | Qt::ItemIsSelectable )
                         : flags;
}

QString PlayListModel::getFilePath(const QModelIndex &index) const
{
  return index.row() <= m_Data.size() ? m_Data[index.row()].filePath : QString();
}

QVariant PlayListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_HeaderSectionTitle[section];
    }
    return QVariant();
}

void PlayListModel::addNewMediaFile(const SMediaFileInfo &mediaFileInfo)
{
  beginInsertRows(QModelIndex(),m_Data.size(),m_Data.size());

    m_Data.insert(m_Data.size(), mediaFileInfo);

  endInsertRows();

}
