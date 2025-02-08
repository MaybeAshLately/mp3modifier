#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDialog>
#include <QVBoxLayout>
#include "modify.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("background-color: #C0C0C0;");
    setAcceptDrops(true);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->close();
}


void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}


void MainWindow::dragMoveEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}


void MainWindow::dropEvent(QDropEvent* event)
{
    auto list=event->mimeData()->urls();
    for(const QUrl& url : list)
    {
        QString fileName = url.toLocalFile();
        if(fileName.endsWith(".mp3")==false) displayInfo();
        else openEditor(fileName);
    }
}


void MainWindow::displayInfo()
{
    QDialog dialog(this);

    dialog.setWindowTitle("Wrong file type");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLabel *label = new QLabel("The app operates only on mp3 files.");
    layout->addWidget(label);

    QPushButton *okButton = new QPushButton("Ok");
    layout->addWidget(okButton);
    okButton->setStyleSheet("background-color: #C0C0C0;");
    connect(okButton, &QPushButton::clicked,this, [&dialog](){dialog.close();} );

    dialog.exec();
}


void MainWindow::openEditor(QString fileName)
{

    Modify* m;
    m= new Modify(this, fileName);
    m->setStyleSheet("background-color: #A0A0A0;");
    m->setWindowTitle("Edit");
    m->setFixedSize(800,600);

    connect(m, &Modify::finished, this, &MainWindow::subclassFinished);
    this->hide();
    m->show();
}

void MainWindow::subclassFinished()
{
    this->show();
}
