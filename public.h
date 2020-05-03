#ifndef PUBLIC_H
#define PUBLIC_H

#include <QString>

struct SMediaFileInfo
{
  QString filePath;
  QString fileName;
  QString fileType;
  double  fileSize;
  QString fileDir;
};

Q_DECLARE_METATYPE(SMediaFileInfo);



#endif // PUBLIC_H
