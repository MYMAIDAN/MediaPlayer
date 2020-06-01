#ifndef _PLAYLISTCONTEXTMENU_H_
#define _PLAYLISTCONTEXTMENU_H_

#include <QObject>
#include <QWidget>
#include <QMenu>

#include "public.h"

class PlayListContextMenu : public QMenu
{
  Q_OBJECT
public:
  explicit PlayListContextMenu( QWidget* parent = nullptr );
  void addFolderHandler();

signals:
  void folderSelected( const QString& path );
};

#endif // _PLAYLISTCONTEXTMENU_H_
