#include "modify.h"
#include "ui_modify.h"

Modify::Modify(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Modify)
{
    ui->setupUi(this);
    goBackToMain=false;


    ui->cancelButton->setStyleSheet("background-color: #FF0000;");
    ui->saveButton->setStyleSheet("background-color: #00BA0C;");
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
