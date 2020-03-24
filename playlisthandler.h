#ifndef PLAYLISTHANDLER_H
#define PLAYLISTHANDLER_H

#include <QObject>
#include <QMediaPlaylist>

class PlayListHandler : public QMediaPlaylist
{
  Q_OBJECT
public:
  PlayListHandler();

public slots:
  void addMediaFile(const QString& filePath);
};

#endif // PLAYLISTHANDLER_H
