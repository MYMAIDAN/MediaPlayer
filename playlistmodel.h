#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QMediaPlaylist>
#include <QMediaPlayer>

class PlayListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit PlayListModel(const QStringList& list, QObject *parent = nullptr);
    explicit PlayListModel(QObject* parent = nullptr);
    ~PlayListModel();
    QVariant      data     ( const QModelIndex& index, int nRole  = Qt::DisplayRole) const override;
    int           columnCount(const QModelIndex &parent = QModelIndex()) const override;
    int           rowCount ( const QModelIndex& parent = QModelIndex() ) const override;
    QVariant      headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags    ( const QModelIndex &index ) const override;

public slots:
    void addNewMediaFile( const QString& path );
    void play(const QModelIndex& index);


private:
    struct SMediaMetaData
    {
      QString     albumTitle;
      QString     albumArtist;
      int         trackNumber;
      QStringList genre;
      int         year;
    };
    QMediaPlayer                  m_player;
    QMap<int,QPair<QString,SMediaMetaData>>  m_Data;
    QStringList                   m_HeaderSectionTitle;

};

#endif // PLAYLISTMODEL_H
