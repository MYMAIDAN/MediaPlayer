/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "playercontrols.h"

#include <QBoxLayout>
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QComboBox>
#include <QAudio>
#include <QTime>

PlayerControls::PlayerControls( QWidget *parent )
    : QWidget( parent )
{
  m_playButton = new QToolButton( this );
  m_playButton->setIcon( QIcon( ":/play_icon.svg" ) );

  connect( m_playButton, &QAbstractButton::clicked, this, &PlayerControls::playClicked );

  m_stopButton = new QToolButton( this );
  m_stopButton->setIcon( QIcon( ":/stop_icon.svg" ) );
  m_stopButton->setEnabled( false );

  connect( m_stopButton, &QAbstractButton::clicked, this, &PlayerControls::stop );

  m_nextButton = new QToolButton( this );
  m_nextButton->setIcon( QIcon( ":/next_icon.svg" ) );

  connect( m_nextButton, &QAbstractButton::clicked, this, &PlayerControls::next );

  m_previousButton = new QToolButton( this );
  m_previousButton->setIcon( QIcon( ":/previos_icon.svg" ) );

  connect( m_previousButton, &QAbstractButton::clicked, this, &PlayerControls::previous );

  m_muteButton = new QToolButton( this );
  m_muteButton->setIcon( QIcon( ":/sound_icon.svg" ) );

  connect( m_muteButton, &QAbstractButton::clicked, this, &PlayerControls::muteClicked );

  m_volumeSlider = new QSlider( Qt::Horizontal, this );
  m_volumeSlider->setRange( 0, 100 );

  connect( m_volumeSlider, &QSlider::valueChanged, this, &PlayerControls::onVolumeSliderValueChanged );

  m_durationSlider = new QSlider( Qt::Horizontal, this );
  m_durationSlider->setEnabled( true );
  m_durationSlider->setSliderDown( true );

  connect( m_durationSlider, &QAbstractSlider::sliderMoved, this, &PlayerControls::durationChanged );

  m_rateBox = new QComboBox( this );
  m_rateBox->addItem( "0.5x", QVariant( 0.5 ) );
  m_rateBox->addItem( "1.0x", QVariant( 1.0 ) );
  m_rateBox->addItem( "2.0x", QVariant( 2.0 ) );
  m_rateBox->setCurrentIndex( 1 );

  connect( m_rateBox, QOverload<int>::of( &QComboBox::activated ), this, &PlayerControls::updateRate );
  mDurationLabel = new QLabel( this );
  mPositionLabel = new QLabel( this );
  mDurationLabel->setText( "/00.00" );
  mPositionLabel->setText( "00.00" );

  QBoxLayout *box = new QVBoxLayout;
  mTrackNameLabel = new QLabel;
  mTrackNameLabel->setText( "Hello" );
  box->setContentsMargins( 0, 0, 0, 0 );
  box->addWidget( mTrackNameLabel, 0, Qt::AlignCenter );
  box->addWidget( m_durationSlider );

  QBoxLayout *layout  = new QHBoxLayout;
  QBoxLayout *layout2 = new QHBoxLayout;

  layout->setContentsMargins( 0, 20, 0, 0 );
  layout->addWidget( m_stopButton );
  layout->addWidget( m_previousButton );
  layout->addWidget( m_playButton );
  layout->addWidget( m_nextButton );
  layout->addWidget( m_muteButton );
  layout->addWidget( m_volumeSlider );
  layout->addWidget( m_rateBox );
  layout->addWidget( mPositionLabel );
  layout->addWidget( mDurationLabel );
  layout2->addLayout( layout );
  layout2->addLayout( box, 1 );
  setLayout( layout2 );
}

QMediaPlayer::State PlayerControls::state() const
{
  return m_playerState;
}

void PlayerControls::setState( QMediaPlayer::State state )
{
  if( state != m_playerState )
  {
    m_playerState = state;

    switch( state )
    {
    case QMediaPlayer::StoppedState:
      m_stopButton->setEnabled( false );
      m_playButton->setIcon( QIcon( ":/play_icon.svg" ) );
      break;
    case QMediaPlayer::PlayingState:
      m_stopButton->setEnabled( true );
      m_playButton->setIcon( QIcon( ":/pause_icon.svg" ) );
      break;
    case QMediaPlayer::PausedState:
      m_stopButton->setEnabled( true );
      m_playButton->setIcon( QIcon( ":/play_icon.svg" ) );
      break;
    }
  }
}

int PlayerControls::volume() const
{
  qreal linearVolume = QAudio::convertVolume( m_volumeSlider->value() / qreal( 100 ),
                                              QAudio::LogarithmicVolumeScale,
                                              QAudio::LinearVolumeScale );

  return qRound( linearVolume * 100 );
}

void PlayerControls::setVolume( int volume )
{
  qreal logarithmicVolume =
      QAudio::convertVolume( volume / qreal( 100 ), QAudio::LinearVolumeScale, QAudio::LogarithmicVolumeScale );

  m_volumeSlider->setValue( qRound( logarithmicVolume * 100 ) );
}

bool PlayerControls::isMuted() const
{
  return m_playerMuted;
}

void PlayerControls::setMuted( bool muted )
{
  if( muted != m_playerMuted )
  {
    m_playerMuted = muted;

    m_muteButton->setIcon( muted ? QIcon( ":/mute_icon.svg" ) : QIcon( ":/sound_icon.svg" ) );
  }
}

void PlayerControls::playClicked()
{
  switch( m_playerState )
  {
  case QMediaPlayer::StoppedState:
  case QMediaPlayer::PausedState:
    emit play();
    break;
  case QMediaPlayer::PlayingState:
    emit pause();
    break;
  }
}

void PlayerControls::muteClicked()
{
  emit changeMuting( !m_playerMuted );
}

qreal PlayerControls::playbackRate() const
{
  return m_rateBox->itemData( m_rateBox->currentIndex() ).toDouble();
}

void PlayerControls::setPlaybackRate( float rate )
{
  for( int i = 0; i < m_rateBox->count(); ++i )
  {
    if( qFuzzyCompare( rate, float( m_rateBox->itemData( i ).toDouble() ) ) )
    {
      m_rateBox->setCurrentIndex( i );
      return;
    }
  }

  m_rateBox->addItem( QString( "%1x" ).arg( rate ), QVariant( rate ) );
  m_rateBox->setCurrentIndex( m_rateBox->count() - 1 );
}

void PlayerControls::updateRate()
{
  emit changeRate( playbackRate() );
}

void PlayerControls::onVolumeSliderValueChanged()
{
  emit changeVolume( volume() );
}

void PlayerControls::setDuration( uint64_t milisecond )
{
  m_durationSlider->setRange( 0, milisecond / 1000 );
  m_durationSlider->setSliderDown( false );

  uint64_t second = milisecond / 1000;

  QTime totalTime( ( second / 3600 ) % 60, ( second / 60 ) % 60, ( second % 60 ), ( second * 1000 ) % 1000 );

  QString format = "/mm:ss";
  if( second > 3600 )
  {
    format = "/hh:mm:ss";
  }

  auto str = totalTime.toString( format );
  mDurationLabel->setText( str );
}

void PlayerControls::positionChanged( uint64_t milisecond )
{
  uint64_t second = milisecond / 1000;
  m_durationSlider->setValue( second );

  QTime currentTime( ( second / 3600 ) % 60, ( second / 60 ) % 60, second % 60, ( second * 1000 ) % 1000 );

  QString format = "mm:ss";
  if( second > 3600 )
  {
    format = "hh:mm:ss";
  }

  auto str = currentTime.toString( format );
  mPositionLabel->setText( str );
}

void PlayerControls::setTrackInfo( const QString &trackInfo )
{
  mTrackNameLabel->setText( trackInfo );
}
