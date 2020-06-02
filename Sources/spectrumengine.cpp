#include "spectrumengine.h"
#include <QDebug>
#include <QByteArray>

SpectrumEngine::SpectrumEngine( std::shared_ptr<QMediaPlayer> playerPtr )
    : mMediaPlayerPtr( playerPtr ), mAudioProbe( std::make_unique<QAudioProbe>() ),
      mSpectrumAnalyser( std::make_unique<SpectrumAnalyser>( this ) )
{
  mSpectrumAnalyser->setWindowFunction( WindowFunction::HannWindow );
  mAudioProbe->setSource( mMediaPlayerPtr.get() );
  connect(
      mAudioProbe.get(), &QAudioProbe::audioBufferProbed, this, [this]( [[maybe_unused]] const QAudioBuffer &buffer ) {
        mSpectrumAnalyser->calculate( QByteArray( buffer.data<char>(), buffer.byteCount() ), buffer.format() );
      } );

  connect( mSpectrumAnalyser.get(), &SpectrumAnalyser::spectrumChanged, this, &SpectrumEngine::spectrumChanged );
}
