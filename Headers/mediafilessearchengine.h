#ifndef MEDIAFILESSEARCHENGINE_H
#define MEDIAFILESSEARCHENGINE_H

#include <QObject>

#include "public.h"

class MediaFilesSearchEngine :  public QObject
{
  Q_OBJECT
public:
  explicit MediaFilesSearchEngine();
  ~MediaFilesSearchEngine();

public slots:
  void search();

signals:
  void findMediaFile( const SMediaFileInfo& mediaFileInfo );

private:
  SMediaFileInfo* mMediaFileInfo;
};

#endif // MEDIAFILESSEARCHENGINE_H
