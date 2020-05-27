#ifndef _PLAYLISTCONTEXTMENU_H_
#define _PLAYLISTCONTEXTMENU_H_

#include <QObject>
#include <QWidget>
#include <QMenu>

class PlayListContextMenu : public QMenu
{
  Q_OBJECT
public:
  explicit PlayListContextMenu( QWidget* parent = nullptr );
};

#endif // _PLAYLISTCONTEXTMENU_H_
