#include "playlisthandler.h"
#include <QUrl>

PlayListHandler::PlayListHandler()
{

}

void PlayListHandler::addMediaFile(const SMediaFileInfo &mediaFileInfo)
{
  this->addMedia(QUrl::fromLocalFile(mediaFileInfo.filePath));
  uint64_t index = this->mediaCount() - 1;
  this->mMediaFilesIndexMap.insert(mediaFileInfo.filePath,index);
}

void PlayListHandler::changeMediaFile(const QString &filePath)
{
  auto it = mMediaFilesIndexMap.find(filePath);
  setCurrentIndex( it != mMediaFilesIndexMap.end() ? it.value() : currentIndex());
}

QString PlayListHandler::getCurrentMediaPath()
{

    auto index = this->currentIndex() ;
    if( index == -1 )
    {
      this->setCurrentIndex(0);
      return  mMediaFilesIndexMap.key( this->currentIndex() ) ;
    }
    else
    {
      return  mMediaFilesIndexMap.key( this->currentIndex() ) ;
    }

}




