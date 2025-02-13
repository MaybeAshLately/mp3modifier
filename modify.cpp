#include "modify.h"
#include "ui_modify.h"
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>
#include <QDragEnterEvent>
#include <QDialog>
#include <QMimeData>
#include <QVBoxLayout>
#include <QFile>
#include <QByteArray>


Modify::Modify(QWidget *parent, QString currentFileName)
    : QDialog(parent)
    , ui(new Ui::Modify)
    , fileName(currentFileName)
{
    ui->setupUi(this);
    goBackToMain=false;

    setAcceptDrops(true);

    ui->cancelButton->setStyleSheet("background-color: #FF0000;");
    ui->saveButton->setStyleSheet("background-color: #00BA0C;");
    ui->otherDataButton->setChecked(true);

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

        TagLib::ID3v2::Tag *tag=dynamic_cast<TagLib::MPEG::File*>(f.file())->ID3v2Tag();
        if (!tag) return;

        TagLib::ID3v2::FrameList frames = tag->frameListMap()["APIC"];
        if (frames.isEmpty())
        {
            ui->cover->setText("No cover found");
            return;
        }

        TagLib::ID3v2::AttachedPictureFrame *coverFrame=dynamic_cast<TagLib::ID3v2::AttachedPictureFrame *>(frames.front());
        if (!coverFrame)
        {
            ui->cover->setText("No cover found");
            return;
        }

        QByteArray coverData(coverFrame->picture().data(), coverFrame->picture().size());
        QPixmap pixmap;
        if (!pixmap.loadFromData(coverData)) return;

        ui->cover->setPixmap(pixmap.scaled(ui->cover->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
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
        if(ui->otherDataButton->isChecked())
        {
            f.tag()->setComment("");
            f.tag()->setGenre("");
            f.tag()->setTrack(0);
            f.tag()->setYear(0);
        }


        if(newCoverPath.isEmpty()==false)
        {
            QFile coverFile(newCoverPath);
            if (coverFile.open(QIODevice::ReadOnly))
            {
                QByteArray coverData = coverFile.readAll();
                coverFile.close();

                TagLib::ID3v2::Tag *tag=dynamic_cast<TagLib::MPEG::File*>(f.file())->ID3v2Tag();
                if (!tag) return;

                if (tag)
                {
                    TagLib::ID3v2::FrameList frames = tag->frameListMap()["APIC"];
                    for(auto frame: frames)
                    {
                        tag->removeFrame(frame);
                    }

                    TagLib::ID3v2::AttachedPictureFrame *coverFrame = new TagLib::ID3v2::AttachedPictureFrame();
                    if((newCoverPath.endsWith(".jpeg"))||(newCoverPath.endsWith(".jpg"))) coverFrame->setMimeType("image/jpeg");
                    else if(newCoverPath.endsWith(".png")) coverFrame->setMimeType("image/png");
                    coverFrame->setPicture(TagLib::ByteVector(coverData.data(), coverData.size()));

                    tag->addFrame(coverFrame);
                }

            }
        }

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



void Modify::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}


void Modify::dragMoveEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}


void Modify::dropEvent(QDropEvent* event)
{
    auto list=event->mimeData()->urls();
    for(const QUrl& url : list)
    {
        QString imagePath = url.toLocalFile();
        newCoverPath=imagePath;
        if((imagePath.endsWith(".jpeg")==true)||(imagePath.endsWith(".png")==true)||(imagePath.endsWith(".jpg")==true))
        {
            QPixmap pixmap;
            if(!pixmap.load(imagePath)) return;
            ui->cover->setPixmap(pixmap.scaled(ui->cover->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        else
        {
            displayInfo();
        }
    }
}


void Modify::displayInfo()
{
    QDialog dialog(this);

    dialog.setWindowTitle("Wrong file type");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLabel *label = new QLabel("As cover you can only use jpg, jpeg and png files.");
    layout->addWidget(label);

    QPushButton *okButton = new QPushButton("Ok");
    layout->addWidget(okButton);
    okButton->setStyleSheet("background-color: #C0C0C0;");
    connect(okButton, &QPushButton::clicked,this, [&dialog](){dialog.close();} );

    dialog.exec();
}
