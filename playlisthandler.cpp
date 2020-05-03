#include "playlisthandler.h"
#include <QUrl>

PlayListHandler::PlayListHandler()
{

}

void PlayListHandler::addMediaFile(const SMediaFileInfo &mediaFileInfo)
{
  this->addMedia(QUrl::fromLocalFile(mediaFileInfo.filePath));
  static uint64_t index = this->mediaCount();
  this->mMediaFilesIndexMap.insert(mediaFileInfo.filePath,++index);

}

void PlayListHandler::changeMediaFile(const QString &filePath)
{
  auto it = mMediaFilesIndexMap.find(filePath);
  setCurrentIndex( it != mMediaFilesIndexMap.end() ? it.value() : currentIndex());

}


