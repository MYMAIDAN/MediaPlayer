#ifndef MEDIAFILESSEARCHENGINE_H
#define MEDIAFILESSEARCHENGINE_H

#include <QObject>

class MediaFilesSearchEngine :  public QObject
{
  Q_OBJECT
public:
  explicit MediaFilesSearchEngine();
  ~MediaFilesSearchEngine();

public slots:
  void search();

signals:
  void findMediaFile( const QString& path );
};

#endif // MEDIAFILESSEARCHENGINE_H
