#ifndef MODIFY_H
#define MODIFY_H

#include <QDialog>

namespace Ui {
class Modify;
}

class Modify : public QDialog
{
    Q_OBJECT

public:
    explicit Modify(QWidget *parent = nullptr, QString currentFileName="");
    ~Modify();

private slots:
    void on_cancelButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::Modify *ui;
    void closeEvent(QCloseEvent *event);
    bool goBackToMain;
    void getMetadata();
    void setNewData();
    void displayInfo();

    const QString fileName;

    QString newSongName;
    QString newArtistName;
    QString newAlbumName;

    QString newCoverPath;


protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent* event);
    void dragMoveEvent(QDragEnterEvent *event);
};

#endif // MODIFY_H
