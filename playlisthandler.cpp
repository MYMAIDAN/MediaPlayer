#include "playlisthandler.h"
#include <QUrl>

PlayListHandler::PlayListHandler()
{

}

void PlayListHandler::addMediaFile(const QString &filePath)
{
  this->addMedia(QUrl::fromLocalFile(filePath));
  static uint64_t index = this->mediaCount();
  this->mMediaFilesIndexMap.insert(filePath,++index);

}

void PlayListHandler::changeMediaFile(const QString &filePath)
{
  auto it = mMediaFilesIndexMap.find(filePath);
  setCurrentIndex( it != mMediaFilesIndexMap.end() ? it.value() : currentIndex());
}


