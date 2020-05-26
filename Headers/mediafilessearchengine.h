#ifndef _MEDIAFILESSEARCHENGINE_H_
#define _MEDIAFILESSEARCHENGINE_H_

#include <QObject>

#include "public.h"

class MediaFilesSearchEngine : public QObject
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

#endif // _MEDIAFILESSEARCHENGINE_H_
