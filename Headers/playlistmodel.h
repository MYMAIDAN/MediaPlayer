#ifndef _PLAYLISTMODEL_H_
#define _PLAYLISTMODEL_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QMediaPlaylist>
#include <QMediaPlayer>

#include "public.h"

class PlayListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
  explicit PlayListModel(const QStringList& list, QObject *parent = nullptr);

  explicit PlayListModel(QObject* parent = nullptr);

  ~PlayListModel();

  QVariant data( const QModelIndex& index, int nRole  = Qt::DisplayRole) const override;

  int columnCount( const QModelIndex& parent = QModelIndex()) const override;

  int rowCount( const QModelIndex& parent = QModelIndex() ) const override;

  QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  Qt::ItemFlags flags( const QModelIndex &index ) const override;

  QString getFilePath( const QModelIndex& index ) const;

public slots:
  void addNewMediaFile( const SMediaFileInfo& mediaFileInfo );

private:
  QMediaPlayer                   m_player;
  QMap<uint64_t,SMediaFileInfo>  m_Data;
  QStringList                    m_HeaderSectionTitle;

};

#endif // _PLAYLISTMODEL_H_
