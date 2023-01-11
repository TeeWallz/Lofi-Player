#ifndef LOFI_H
#define LOFI_H

#include <QMainWindow>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class lofi; }
QT_END_NAMESPACE

struct Station{
    QString name;
    QString url;
};

class lofi : public QMainWindow
{
    Q_OBJECT

public:

    void setStreams(){
    this->liveStation[0] = {"Lauft.fm" , "http://stream.laut.fm/lofi"};
    this->liveStation[1] = {"Planet Lofi","http://198.245.60.88:8080" };
    this->liveStation[2] = {"Chill Cafe","http://192.99.35.215:5078"};
    this->liveStation[3] = {"No Copyright Stream","http://78.129.222.70:33297" };
    this->liveStation[4] = {"Chillsky", "https://lfhh.radioca.st/stream"};
    this->liveStation[5] = {"Lofi Hip Hop Radio", "https://stream.zeno.fm/0r0xa792kwzuv"};
    this->liveStation[6] = {"RauteMusik.FM Study", "http://de-hz-fal-stream07.rautemusik.fm/study"};
    }

    int playStatus(){
        return this->isPlaying;
    }

    void setPlaying(){
        this ->isPlaying = 1;
    }

    void setPause(){
        this ->isPlaying = 0;
    }

    void setAudio(){
      this->player.setMedia(QUrl(this->liveStation[this->nowPlaying].url));
      qInfo()<<this->liveStation[this->nowPlaying].name<<" : "<<this->liveStation[this->nowPlaying].url;
    }

    void nextStation(){
        if ( this->nowPlaying == 9){
            this->nowPlaying = 1;
        }
        else{
            this->nowPlaying++;
        }
        setAudio();
        if(this->isPlaying){
            playAudio();
        }
    }

    void previousStation(){
        if ( this->nowPlaying == 0){
            this->nowPlaying = 9;
        }
        else{
            this->nowPlaying--;
        }
        setAudio();
        if(this->isPlaying){
            playAudio();
        }
    }
    void playAudio() {
      this->player.play();
    }

    QString getStationName(){
        return this->liveStation[this->nowPlaying].name;
    }

    void changeVolume(int val) {
        this->player.setVolume(val);
    }

    void pauseAudio() {
      this->player.pause();
    }

    lofi(QWidget *parent = nullptr);
    ~lofi();

private slots:
    void on_Button_clicked();

    void on_volumeSlider_sliderMoved(int position);


    void on_Button_pressed();

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

private:
    int isPlaying = 0;
    int nowPlaying = 1;
    Ui::lofi *ui;
    Station liveStation[10];
    QMediaPlayer player;
};
#endif // LOFI_H
