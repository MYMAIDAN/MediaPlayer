#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QUrl>
#include <memory>

#include "playlistmodel.h"
#include "mediafilessearchengine.h"
#include "playercontrols.h"
#include "playlisthandler.h"
#include "spectrograph.h"

class Player : public QWidget
{
    Q_OBJECT

public:
    Player(QWidget *parent = nullptr);
    ~Player();

public slots:
    void playMusic( const QModelIndex& index );
    void seek(uint64_t milisecond);
private:
    std::unique_ptr<PlayListModel>          mPlayListModel;
    std::unique_ptr<MediaFilesSearchEngine> mMediaFilesSearchEngine;
    std::unique_ptr<PlayerControls>         mPlayerControls;
    std::unique_ptr<PlayListHandler>        m_PlayListHandler;
    std::unique_ptr<QMediaPlayer>           mMediaPlayer;
    Spectrograph    *spectograf       = nullptr;

};
#endif // PLAYER_H
