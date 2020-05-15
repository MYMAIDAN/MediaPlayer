#ifndef SPECTRUMENGINE_H
#define SPECTRUMENGINE_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioProbe>
#include <QAudioBuffer>
#include <memory>

#include "spectrumanalyser.h"

class SpectrumEngine : public QObject
{
  Q_OBJECT
public:
  SpectrumEngine( std::shared_ptr<QMediaPlayer> playerPtr );

signals:
  void spectrumChanged( const FrequencySpectrum &spectrum );

private:
  std::shared_ptr<QMediaPlayer>     mMediaPlayerPtr;
  std::unique_ptr<QAudioProbe>      mAudioProbe;
  std::unique_ptr<SpectrumAnalyser> mSpectrumAnalyser;
};

#endif // SPECTRUMENGINE_H
