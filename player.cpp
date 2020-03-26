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

  QObject::connect( mPlayerControls.get(),   &PlayerControls::previous,
                    m_PlayListHandler.get(), &PlayListHandler::previous );

  QObject::connect(mPlayerControls.get(), &PlayerControls::changeVolume,
                   mMediaPlayer.get(), &QMediaPlayer::setVolume );

  QObject::connect( mMediaPlayer.get(), &QMediaPlayer::volumeChanged,
                    mPlayerControls.get(), &PlayerControls::setVolume );

  QObject::connect(mPlayerControls.get(), &PlayerControls::durationChanged,this, &Player::seek);
  QObject::connect(mMediaPlayer.get(),&QMediaPlayer::positionChanged,mPlayerControls.get(),&PlayerControls::positionChanged);
  QObject::connect(mMediaPlayer.get(),&QMediaPlayer::durationChanged,mPlayerControls.get(),&PlayerControls::setDuration);


  mMediaPlayer->setPlaylist( m_PlayListHandler.get() );

  mPlayerControls->setVolume(mMediaPlayer->volume());


  searchEngineThread->start();

  QObject::connect(listView,&QListView::clicked,
                   this,&Player::playMusic);


  QBoxLayout *listLayout = new QHBoxLayout();
  listLayout->addWidget(listView);
  QBoxLayout *controlLayout = new QHBoxLayout;
  controlLayout->setContentsMargins(0, 0, 0, 0);
  //controlLayout->addStretch(1);
  controlLayout->addWidget(mPlayerControls.get());

  QBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(mPlayerControls.get());
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

void Player::seek(uint64_t milisecond)
{
  mMediaPlayer->setPosition(milisecond*1000);
}

