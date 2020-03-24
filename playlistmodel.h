#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QMediaPlaylist>

class PlayListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PlayListModel(const QStringList& list, QObject *parent = nullptr);
    explicit PlayListModel(QObject* parent = nullptr);
    ~PlayListModel();
    QVariant      data     ( const QModelIndex& index, int nRole ) const override;
    bool          setData  ( const QModelIndex& index, const QVariant& value, int nRole ) override;
    int           rowCount ( const QModelIndex& parent = QModelIndex() ) const override;
    Qt::ItemFlags flags    ( const QModelIndex &index ) const override;

public slots:
    void addNewMediaFile( const QString& path );
    void play(const QModelIndex& index);


private:
    QStringList m_Data;

};

#endif // PLAYLISTMODEL_H
