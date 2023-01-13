#include <QMediaPlayer>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QFontDatabase>
#include <QLabel>
#include <QPropertyAnimation>
#include <json/value.h>
#include <fstream>
#include <iostream>
#include "lofi.h"
#include "ui_lofi.h"
#include "lib/nlohmann/json.hpp"

using json = nlohmann::json;

lofi::lofi(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::lofi)
{
    ui->setupUi(this);

    int loadedFontID = QFontDatabase::addApplicationFont(":/fonts/BebasNeue.ttf");
    qInfo() << loadedFontID;
    QFont Bebas("BebasNeue", 40, QFont::Bold);
    ui->Toplabel->setFont(Bebas);

    ui->volumeSlider->setValue(100);
}

lofi::~lofi()
{
    delete ui;
}

std::string lofi::getJsonStreamsFileLocation()
{
    if (this->jsonStreamFileLocationCustom.empty())
    {
        return this->jsonStreamFileLocationDefault;
    }
    else
    {
        return this->jsonStreamFileLocationCustom;
    }
}

bool lofi::setStreams()
{
    // Perform stream fle check here, as the default may not exist as well
    if (!std::ifstream(this->getJsonStreamsFileLocation()))
    {
        return false;
    }

    std::ifstream f(this->getJsonStreamsFileLocation());
    json stationData = json::parse(f);

    for (const auto &station : stationData.items())
    {
        Station s = {
            .name = QString::fromStdString(station.value()["name"].get<std::string>()),
            .url = QString::fromStdString(station.value()["url"].get<std::string>())};

        liveStation.push_back(s);
    }

    lofi::setAudio();
    lofi::setUiStationName();
    return true;
}

void lofi::on_volumeSlider_valueChanged(int position)
{
    lofi::changeVolume(position);
}

void lofi::on_pushButtonPlay_pressed()
{
    if (!lofi::playStatus())
    {
        lofi::setPlaying();
        lofi::playAudio();
    }
    else
    {
        lofi::setPause();
        lofi::pauseAudio();
    }
}

void lofi::on_pushButtonNextStation_pressed()
{
    lofi::nextStation();
    lofi::setUiStationName();
}

void lofi::on_pushButtonPreviousStation_pressed()
{
    lofi::previousStation();
    lofi::setUiStationName();
}

void lofi::setUiStationName()
{
    ui->FMlabel->setText(lofi::getStationName());
}
