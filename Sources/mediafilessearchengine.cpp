#include "mediafilessearchengine.h"
#include <QDirIterator>
#include <QDebug>

MediaFilesSearchEngine::MediaFilesSearchEngine():
  mMediaFileInfo(new SMediaFileInfo)
{
}

MediaFilesSearchEngine::~MediaFilesSearchEngine()
{
  delete  mMediaFileInfo;
}

void MediaFilesSearchEngine::search()
{
  static QFileInfo fileInfo;
  QDirIterator it( "C:\\Users",
                   QStringList() << "*.flac",
                   QDir::Files,
                   QDirIterator::Subdirectories
                  );
  while( it.hasNext() )
  {
      fileInfo.setFile( it.next() );
      mMediaFileInfo->fileType = fileInfo.suffix();
      mMediaFileInfo->fileName = fileInfo.completeBaseName();
      mMediaFileInfo->filePath = fileInfo.filePath();
      mMediaFileInfo->fileDir  = fileInfo.dir().dirName();
      mMediaFileInfo->fileSize = fileInfo.size() / 1024 / 1024;

    emit findMediaFile( *mMediaFileInfo );
  }
}
