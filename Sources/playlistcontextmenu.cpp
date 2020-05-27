#include "playlistcontextmenu.h"
#include <QDebug>

PlayListContextMenu::PlayListContextMenu( QWidget* parent ) :
  QMenu( parent )
{

  setAttribute( Qt::WA_DeleteOnClose );

  connect( addAction("Add folder"),&QAction::triggered, this, [](){
      qDebug() << "Add folder triggered";
    });
}
