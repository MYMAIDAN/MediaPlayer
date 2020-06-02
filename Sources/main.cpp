#include "player.h"

#include <QApplication>
#include <QStringListModel>
#include <QListView>
#include <QThread>
#include <QItemSelectionModel>
#include <QMediaPlayer>

int main( int argc, char *argv[] )
{
  QApplication a( argc, argv );
  Player       w;
  QApplication::setWindowIcon( QIcon( ":/images.png" ) );
  w.show();
  return a.exec();
}
