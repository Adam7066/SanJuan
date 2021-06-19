#ifndef GAMEENDDIALOG_H
#define GAMEENDDIALOG_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class GameEndDialog;
}

class GameEndDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameEndDialog(QWidget *parent = nullptr);
    ~GameEndDialog();

private:
    Ui::GameEndDialog *ui;
};

#endif // GAMEENDDIALOG_H
