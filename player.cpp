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
  QUrl url = index.data().toUrl();
  mMediaPlayer->setMedia(QUrl::fromLocalFile(index.data().toUrl().path()));
  mMediaPlayer->setVolume(50);
  mMediaPlayer->play();
}

