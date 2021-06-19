#include "gameenddialog.h"
#include "ui_gameenddialog.h"

GameEndDialog::GameEndDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameEndDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("遊戲結束");;
    QString dir = QCoreApplication::applicationDirPath() + "/C_Game/";
    QProcess *process = new QProcess();
    process->setWorkingDirectory(dir);
    process->start("game --end");
    process->waitForFinished();
    QString getStr = QString(process->readAllStandardOutput());
    delete process;
    int vp[4] = {0}, winner = 1;
    sscanf(getStr.toStdString().c_str(), "%d %d %d %d %d", &vp[0], &vp[1], &vp[2], &vp[3], &winner);
    ui->winner->setText("Player" + QString::number(winner) + " 勝利");
    ui->scores->setText("分數：\n");
    for(int i=0; i<4; ++i)
        ui->scores->append("\tPlayer" + QString::number(i+1) + ": " + QString::number(vp[i]) + "\n");
}

GameEndDialog::~GameEndDialog()
{
    delete ui;
}
