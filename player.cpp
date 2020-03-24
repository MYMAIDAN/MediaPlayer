#include "player.h"
#include <QHBoxLayout>
#include <QListView>
#include <QThread>
#include <QtWidgets>
#include <QObject>

Player::Player(QWidget *parent)
    : QWidget(parent),
      mPlayListModel(std::make_unique<PlayListModel>()),
      mMediaFilesSearchEngine(std::make_unique<MediaFilesSearchEngine>()),
      mPlayerControls(std::make_unique<PlayerControls>(this)),
      m_PlayListHandler(std::make_unique<PlayListHandler>()),
      mMediaPlayer(std::make_unique<QMediaPlayer>())
{

  QListView* listView = new QListView(this);
  listView->setModel(mPlayListModel.get());

  QThread* searchEngineThread = new QThread();
  mMediaFilesSearchEngine->moveToThread( searchEngineThread );

  QObject::connect( searchEngineThread,            &QThread::started,
                    mMediaFilesSearchEngine.get(), &MediaFilesSearchEngine::search );

  QObject::connect( mMediaFilesSearchEngine.get(), &MediaFilesSearchEngine::findMediaFile,
                    mPlayListModel.get(),          &PlayListModel::addNewMediaFile );

  QObject::connect( mMediaFilesSearchEngine.get(), &MediaFilesSearchEngine::findMediaFile,
                    m_PlayListHandler.get(),       &PlayListHandler::addMediaFile );

  QObject::connect(mPlayerControls.get(), &PlayerControls::play,
                   mMediaPlayer.get(),    &QMediaPlayer::play );

  QObject::connect(mPlayerControls.get(), &PlayerControls::next,
                   m_PlayListHandler.get(), &PlayListHandler::next );

  QObject::connect(mPlayerControls.get(),&PlayerControls::previous,
                   m_PlayListHandler.get(), &PlayListHandler::previous);

  mMediaPlayer->setPlaylist( m_PlayListHandler.get() );


  searchEngineThread->start();

  QObject::connect(listView,&QListView::clicked,
                   this,&Player::playMusic);


  QBoxLayout *listLayout = new QHBoxLayout();
  listLayout->addWidget(listView);
  QBoxLayout *controlLayout = new QHBoxLayout;
  controlLayout->setContentsMargins(0, 0, 0, 0);
  controlLayout->addStretch(1);
  controlLayout->addWidget(mPlayerControls.get());

  QBoxLayout *layout = new QVBoxLayout;
  layout->addLayout(controlLayout);
  layout->addLayout(listLayout);

  setLayout(layout);
}

Player::~Player()
{
}

void Player::playMusic(const QModelIndex &index)
{
  QMediaPlaylist playlist;
  playlist.addMedia(QUrl::fromLocalFile(index.data().toUrl().path()));
 // mMediaPlayer->setMedia(QUrl::fromLocalFile(index.data().toUrl().path()));
  mMediaPlayer->setPlaylist(&playlist);
  mMediaPlayer->setVolume(50);
  mMediaPlayer->play();
}

