#include "playlisthandler.h"
#include <QUrl>

PlayListHandler::PlayListHandler()
{

}

void PlayListHandler::addMediaFile(const QString &filePath)
{
  this->addMedia(QUrl::fromLocalFile(filePath));
}


