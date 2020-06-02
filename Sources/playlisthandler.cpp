#include "playlisthandler.h"

#include <QUrl>
#include <QDirIterator>

PlayListHandler::PlayListHandler() {}

void PlayListHandler::addMediaFolder( const QString& path )
{
  QDirIterator it( path,
                   QStringList() << "*.flac"
                                 << "*.wav",
                   QDir::Files,
                   QDirIterator::Subdirectories );
  QFileInfo    file;
  while( it.hasNext() )
  {
    auto next = it.next();
    file.setFile( next );
    this->addMedia( QUrl::fromLocalFile( next ) );
    uint64_t index = this->mediaCount() - 1;
    this->mMediaFilesIndexMap.insert( file.fileName(), index );
  }
}

void PlayListHandler::changeMediaFile( const QString& filePath )
{
  auto it = mMediaFilesIndexMap.find( filePath );
  setCurrentIndex( it != mMediaFilesIndexMap.end() ? it.value() : currentIndex() );
}

QString PlayListHandler::getCurrentMediaPath()
{
  auto index = this->currentIndex();
  if( index == -1 )
  {
    this->setCurrentIndex( 0 );
    return mMediaFilesIndexMap.key( this->currentIndex() );
  }
  else
  {
    return mMediaFilesIndexMap.key( this->currentIndex() );
  }
}
