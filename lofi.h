#ifndef LOFI_H
#define LOFI_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <json/value.h>
#include <fstream>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class lofi;
}
QT_END_NAMESPACE

struct Station
{
    QString name;
    QString url;
};

class lofi : public QMainWindow
{
    Q_OBJECT

public:
    std::string jsonStreamFileLocationCustom;

    bool setStreams();
    
    void setUiStationName();

    std::string getJsonStreamsFileLocation();

    int playStatus()
    {
        return this->isPlaying;
    }

    void setPlaying()
    {
        this->isPlaying = 1;
    }

    void setPause()
    {
        this->isPlaying = 0;
    }

    void setAudio()
    {
        this->player.setMedia(QUrl(this->liveStation[this->nowPlaying].url));
        qInfo() << this->liveStation[this->nowPlaying].name << " : " << this->liveStation[this->nowPlaying].url;
    }

    void nextStation()
    {
        this->nowPlaying = (this->nowPlaying + 1) % liveStation.size();
        setAudio();
        if (this->isPlaying)
        {
            playAudio();
        }
    }

    void previousStation()
    {
        this->nowPlaying = (this->nowPlaying - 1) % liveStation.size();
        setAudio();
        if (this->isPlaying)
        {
            playAudio();
        }
    }
    void playAudio()
    {
        this->player.play();
    }

    QString getStationName()
    {
        return this->liveStation[this->nowPlaying].name;
    }

    void changeVolume(int volumeSliderValue)
    {
        // Volume is perceived as logarithmic, as oposed to linear
        // https://felgo.com/doc/qt/qaudio/#convertVolume
        // volumeSliderValue is in the range [0..100]
        qreal linearVolume = QAudio::convertVolume(volumeSliderValue / qreal(100.0),
                                                QAudio::LogarithmicVolumeScale,
                                                QAudio::LinearVolumeScale);

        this->player.setVolume(qRound(linearVolume * 100));
    }

    void pauseAudio()
    {
        this->player.pause();
    }

    lofi(QWidget *parent = nullptr);
    ~lofi();

private slots:
    void on_volumeSlider_valueChanged(int position);

    void on_pushButtonPlay_pressed();

    void on_pushButtonNextStation_pressed();

    void on_pushButtonPreviousStation_pressed();

private:
    std::vector<Station> liveStation;
    int isPlaying = 0;
    int nowPlaying = 0;
    std::string jsonStreamFileLocationDefault = "/etc/Lofi-Player/streams.json";
    Ui::lofi *ui;
    QMediaPlayer player;
};
#endif // LOFI_H
