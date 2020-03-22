#include "player.h"

#include <QApplication>
#include <QStringListModel>
#include <QListView>
#include <QThread>
#include "playlistmodel.h"
#include "mediafilessearchengine.h"
#include <QItemSelectionModel>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Player w;
    w.show();
    return a.exec();
}
