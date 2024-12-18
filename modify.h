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
    explicit Modify(QWidget *parent = nullptr);
    ~Modify();

private slots:
    void on_cancelButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::Modify *ui;
    void closeEvent(QCloseEvent *event);
    bool goBackToMain;
};

#endif // MODIFY_H
