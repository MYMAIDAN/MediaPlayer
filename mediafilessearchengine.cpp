#include "mediafilessearchengine.h"
#include <QDirIterator>
#include <QDebug>

MediaFilesSearchEngine::MediaFilesSearchEngine()
{
}

MediaFilesSearchEngine::~MediaFilesSearchEngine()
{

}

void MediaFilesSearchEngine::search()
{

  QDirIterator it("/Users/mykhailomaidan/Downloads",QStringList() << "*.flac", QDir::Files, QDirIterator::Subdirectories );
  while( it.hasNext() )
  {
    emit findMediaFile( it.next() );
  }
}
