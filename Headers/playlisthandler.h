#ifndef PLAYLISTHANDLER_H
#define PLAYLISTHANDLER_H

#include <QObject>
#include <QMediaPlaylist>
#include <QMap>

#include "public.h"

class PlayListHandler : public QMediaPlaylist
{
  Q_OBJECT
public:
  PlayListHandler();

public slots:
  void addMediaFolder( const QString& path );
  void changeMediaFile(const QString& filePath);
  QString getCurrentMediaPath();

private:
  QMap<QString,uint64_t> mMediaFilesIndexMap;
};

#endif // PLAYLISTHANDLER_H
