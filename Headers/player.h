#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "playercontrols.h"
#include "playlisthandler.h"
#include "spectrograph.h"
#include "spectrumengine.h"

#include <QWidget>
#include <QMediaPlayer>]
#include <QUrl>
#include <QTreeView>
#include <memory>

class TreeModel;

class Player : public QWidget
{
  Q_OBJECT

public:
  Player( QWidget* parent = nullptr );
  ~Player();

public slots:
  void seek( uint64_t milisecond );

private slots:
  void playListContextMenuRequested( const QPoint& point );
  void setSong( const QModelIndex& index );

private:
  std::unique_ptr<TreeModel>       mPlayListModel;
  std::unique_ptr<PlayerControls>  mPlayerControls;
  std::unique_ptr<PlayListHandler> m_PlayListHandler;
  std::shared_ptr<QMediaPlayer>    mMediaPlayer;
  std::unique_ptr<SpectrumEngine>  mSpectrumEngine;
  Spectrograph*                    spectograf{ nullptr };
  std::shared_ptr<QTreeView>       mTreeView{ nullptr };
};
#endif // PLAYER_H
