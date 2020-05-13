#include "player.h"
#include "mediafilessearchengine.h"
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

  QTableView* listView = new QTableView();
  listView->setModel(mPlayListModel.get());
  listView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

  QThread* searchEngineThread = new QThread();
  mMediaFilesSearchEngine->moveToThread( searchEngineThread );

  qRegisterMetaType<SMediaFileInfo>();

  connect( searchEngineThread,            &QThread::started,
           mMediaFilesSearchEngine.get(), &MediaFilesSearchEngine::search );

  connect( mMediaFilesSearchEngine.get(), &MediaFilesSearchEngine::findMediaFile,
           mPlayListModel.get(),          &PlayListModel::addNewMediaFile );

  connect( mMediaFilesSearchEngine.get(), &MediaFilesSearchEngine::findMediaFile,
           m_PlayListHandler.get(),       &PlayListHandler::addMediaFile );

  connect( mPlayerControls.get(), &PlayerControls::play,
           this,    [this]()
  {
      auto  str = m_PlayListHandler->getCurrentMediaPath();
      QFileInfo file( str );

      mPlayerControls->setTrackInfo( file.fileName() );
      mMediaPlayer->play();
  });

  connect( mPlayerControls.get(),&PlayerControls::pause,
           mMediaPlayer.get(),   &QMediaPlayer::pause );

  connect( mPlayerControls.get(),   &PlayerControls::next,
           m_PlayListHandler.get(), &PlayListHandler::next );

  connect( mPlayerControls.get(),   &PlayerControls::previous,
           m_PlayListHandler.get(), &PlayListHandler::previous );

  connect( mPlayerControls.get(), &PlayerControls::changeVolume,
           mMediaPlayer.get(),    &QMediaPlayer::setVolume );

  connect( mMediaPlayer.get(),    &QMediaPlayer::volumeChanged,
           mPlayerControls.get(), &PlayerControls::setVolume );

  connect( mPlayerControls.get(), &PlayerControls::changeMuting,
           mMediaPlayer.get(),    &QMediaPlayer::setMuted );

  connect( mMediaPlayer.get(),    &QMediaPlayer::mutedChanged,
           mPlayerControls.get(), &PlayerControls::setMuted );

  connect( mMediaPlayer.get(),    &QMediaPlayer::stateChanged,
           mPlayerControls.get(), &PlayerControls::setState );

  connect( mPlayerControls.get(), &PlayerControls::durationChanged,
          this,                   &Player::seek );

  connect( mMediaPlayer.get(),    &QMediaPlayer::positionChanged,
           mPlayerControls.get(), &PlayerControls::positionChanged );

  connect( mMediaPlayer.get(),    &QMediaPlayer::durationChanged,
           mPlayerControls.get(), &PlayerControls::setDuration );

  connect( mPlayerControls.get(), &PlayerControls::changeRate,
           mMediaPlayer.get(),    &QMediaPlayer::setPlaybackRate );

  connect(listView,&QListView::doubleClicked,this,[&](const QModelIndex& index)
  {
    m_PlayListHandler->changeMediaFile(mPlayListModel->getFilePath(index));
    auto str = m_PlayListHandler->getCurrentMediaPath();
    QFileInfo file( std::move( m_PlayListHandler->getCurrentMediaPath() ) );
    mPlayerControls->setTrackInfo( file.fileName() );
    mMediaPlayer->play();
    mPlayerControls->setState(QMediaPlayer::State::PlayingState);
  }
  );

  mMediaPlayer->setPlaylist( m_PlayListHandler.get() );
  mMediaPlayer->setMuted(mPlayerControls->isMuted());
  mPlayerControls->setState(mMediaPlayer->state());
  mPlayerControls->setPlaybackRate(mMediaPlayer->playbackRate());
  mPlayerControls->setVolume(mMediaPlayer->volume());

  searchEngineThread->start();

  QBoxLayout *listLayout = new QHBoxLayout();
    spectograf = new Spectrograph(this);
    listLayout->setContentsMargins(20,20,20,20);
  listLayout->addWidget(listView);
  listLayout->addWidget(spectograf,1);
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

  mMediaPlayer->setPlaylist(&playlist);
  mMediaPlayer->setVolume(50);
  mMediaPlayer->play();
}

void Player::seek(uint64_t milisecond)
{
  mMediaPlayer->setPosition(milisecond*1000);
}

