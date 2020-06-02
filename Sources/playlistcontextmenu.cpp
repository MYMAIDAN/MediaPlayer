#include "playlistcontextmenu.h"

#include <QDebug>
#include <QFileDialog>
#include <QDirIterator>

PlayListContextMenu::PlayListContextMenu( QWidget* parent )
    : QMenu( parent )
{
  setAttribute( Qt::WA_DeleteOnClose );
  connect( addAction( "Add folder" ), &QAction::triggered, this, &PlayListContextMenu::addFolderHandler );
}

void PlayListContextMenu::addFolderHandler()
{
  QFileDialog dialog;
  dialog.setFileMode( QFileDialog::Directory );
  dialog.setOption( QFileDialog::DontUseNativeDialog, false );
  dialog.setOption( QFileDialog::ShowDirsOnly, false );
  dialog.exec();
  qDebug() << dialog.directory();
  auto folderName = dialog.directory().path();
  emit folderSelected( folderName );
}
