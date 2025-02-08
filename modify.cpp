#include "modify.h"
#include "ui_modify.h"
#include <taglib/fileref.h>
#include <taglib/tag.h>

Modify::Modify(QWidget *parent, QString currentFileName)
    : QDialog(parent)
    , ui(new Ui::Modify)
    , fileName(currentFileName)
{
    ui->setupUi(this);
    goBackToMain=false;


    ui->cancelButton->setStyleSheet("background-color: #FF0000;");
    ui->saveButton->setStyleSheet("background-color: #00BA0C;");

    getMetadata();
}

void Modify::getMetadata()
{
    TagLib::FileRef f(fileName.toStdString().c_str());

    if (!f.isNull()&&f.tag())
    {
        QString artist=QString::fromStdString(f.tag()->artist().to8Bit(true));
        QString title=QString::fromStdString(f.tag()->title().to8Bit(true));
        QString album=QString::fromStdString(f.tag()->album().to8Bit(true));

        ui->songNameText->setText(title);
        ui->artistNameText->setText(artist);
        ui->albumNameText->setText(album);
    }
}

Modify::~Modify()
{
    delete ui;
}

void Modify::on_cancelButton_clicked()
{
    goBackToMain=true;
    this->close();
}


void Modify::on_saveButton_clicked()
{
    newSongName=ui->songNameText->toPlainText();
    newArtistName=ui->artistNameText->toPlainText();
    newAlbumName=ui->albumNameText->toPlainText();
    setNewData();
    goBackToMain=true;
    this->close();
}


void Modify::setNewData()
{
    newSongName=ui->songNameText->toPlainText();;
    newArtistName=ui->artistNameText->toPlainText();;
    newAlbumName=ui->albumNameText->toPlainText();;

    TagLib::FileRef f(fileName.toStdString().c_str());

    if (!f.isNull()&&f.tag())
    {
        f.tag()->setTitle(newSongName.toStdString());
        f.tag()->setArtist(newArtistName.toStdString());
        f.tag()->setAlbum(newAlbumName.toStdString());
        f.save();
    }
}

void Modify::closeEvent(QCloseEvent *event)
{
    if(goBackToMain==true)
    {
        emit finished(0);
    }
    else
    {
        QApplication::quit();
    }
}
