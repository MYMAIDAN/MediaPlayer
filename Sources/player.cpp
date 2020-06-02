#include "player.h"
#include "spectrum.h"
#include "playlistcontextmenu.h"
#include "treemodel.h"

#include <QHBoxLayout>
#include <QTreeView>
#include <QThread>
#include <QtWidgets>
#include <QObject>
#include <QTreeView>

#include <utility>

Player::Player( QWidget *parent )
    : QWidget( parent )
    , mPlayListModel( std::make_unique<TreeModel>( QStringList() << "Folder" ) )
    , mPlayerControls( std::make_unique<PlayerControls>( this ) )
    , m_PlayListHandler( std::make_unique<PlayListHandler>() )
    , mMediaPlayer( std::make_shared<QMediaPlayer>() )
    , mSpectrumEngine( std::make_unique<SpectrumEngine>( mMediaPlayer ) )
{
  mTreeView = std::make_shared<QTreeView>();
  mTreeView->setModel( mPlayListModel.get() );

  qRegisterMetaType<SMediaFileInfo>(); // register new type for qmoc

  connect( mPlayerControls.get(), &PlayerControls::play, this, [this]() {
    auto      str = m_PlayListHandler->getCurrentMediaPath();
    QFileInfo file( str );

    mPlayerControls->setTrackInfo( file.fileName() );
    mMediaPlayer->play();
  } );

  connect( mPlayerControls.get(), &PlayerControls::pause, mMediaPlayer.get(), &QMediaPlayer::pause );

  connect( mPlayerControls.get(), &PlayerControls::next, m_PlayListHandler.get(), &PlayListHandler::next );

  connect( mPlayerControls.get(), &PlayerControls::previous, m_PlayListHandler.get(), &PlayListHandler::previous );

  connect( mPlayerControls.get(), &PlayerControls::changeVolume, mMediaPlayer.get(), &QMediaPlayer::setVolume );

  connect( mMediaPlayer.get(), &QMediaPlayer::volumeChanged, mPlayerControls.get(), &PlayerControls::setVolume );

  connect( mPlayerControls.get(), &PlayerControls::changeMuting, mMediaPlayer.get(), &QMediaPlayer::setMuted );

  connect( mMediaPlayer.get(), &QMediaPlayer::mutedChanged, mPlayerControls.get(), &PlayerControls::setMuted );

  connect( mMediaPlayer.get(), &QMediaPlayer::stateChanged, mPlayerControls.get(), &PlayerControls::setState );

  connect( mPlayerControls.get(), &PlayerControls::durationChanged, this, &Player::seek );

  connect( mMediaPlayer.get(),
           &QMediaPlayer::positionChanged,
           mPlayerControls.get(),
           &PlayerControls::positionChanged );

  connect( mMediaPlayer.get(), &QMediaPlayer::durationChanged, mPlayerControls.get(), &PlayerControls::setDuration );

  connect( mPlayerControls.get(), &PlayerControls::changeRate, mMediaPlayer.get(), &QMediaPlayer::setPlaybackRate );

  connect( mTreeView.get(), &QTreeView::doubleClicked, this, &Player::setSong );

  mMediaPlayer->setPlaylist( m_PlayListHandler.get() );
  mMediaPlayer->setMuted( mPlayerControls->isMuted() );
  mPlayerControls->setState( mMediaPlayer->state() );
  mPlayerControls->setPlaybackRate( mMediaPlayer->playbackRate() );
  mPlayerControls->setVolume( mMediaPlayer->volume() );

  QBoxLayout *listLayout = new QHBoxLayout();
  spectograf             = new Spectrograph( this );
  spectograf->setParams( SpectrumNumBands, SpectrumLowFreq, SpectrumHighFreq );
  connect( mSpectrumEngine.get(), &SpectrumEngine::spectrumChanged, spectograf, &Spectrograph::spectrumChanged );

  mTreeView->setContextMenuPolicy( Qt::CustomContextMenu );

  connect( mTreeView.get(), &QTreeView::customContextMenuRequested, this, &Player::playListContextMenuRequested );

  listLayout->setContentsMargins( 20, 20, 20, 20 );
  listLayout->addWidget( mTreeView.get(), 2, 0 );
  listLayout->addWidget( spectograf, 1 );

  QBoxLayout *controlLayout = new QHBoxLayout;
  controlLayout->setContentsMargins( 0, 0, 0, 0 );
  controlLayout->addWidget( mPlayerControls.get() );

  QBoxLayout *layout = new QVBoxLayout;
  layout->addWidget( mPlayerControls.get() );

  layout->addLayout( listLayout );

  setLayout( layout );
}

Player::~Player() {}

void Player::seek( uint64_t milisecond )
{
  mMediaPlayer->setPosition( milisecond * 1000 );
}

void Player::playListContextMenuRequested( const QPoint &point )
{
  auto menu = PlayListContextMenu( mTreeView->parentWidget() );
  connect( &menu, &PlayListContextMenu::folderSelected, m_PlayListHandler.get(), &PlayListHandler::addMediaFolder );
  connect( &menu, &PlayListContextMenu::folderSelected, this->mPlayListModel.get(), &TreeModel::addFolder );

  menu.exec( mTreeView->mapToGlobal( point ) );
}

void Player::setSong( const QModelIndex &index )
{
  m_PlayListHandler->changeMediaFile( index.data().toString() );
  QFileInfo file( std::move( m_PlayListHandler->getCurrentMediaPath() ) );
  mPlayerControls->setTrackInfo( file.fileName() );
  mMediaPlayer->play();
  mPlayerControls->setState( QMediaPlayer::State::PlayingState );
}
