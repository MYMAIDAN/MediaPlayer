#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QUrl>
#include <memory>

#include "playlistmodel.h"
#include "mediafilessearchengine.h"
#include "playerconctrols.h"

class Player : public QWidget
{
    Q_OBJECT

public:
    Player(QWidget *parent = nullptr);
    ~Player();

public slots:
    void playMusic( const QModelIndex& index );
private:
    std::unique_ptr<PlayListModel>          mPlayListModel;
    std::unique_ptr<MediaFilesSearchEngine> mMediaFilesSearchEngine;
    std::unique_ptr<PlayerControls>         mPlayerControls;
    std::unique_ptr<QMediaPlayer>           mMediaPlayer;


};
#endif // PLAYER_H
