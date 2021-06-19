#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool career[5], playerGoods[4][12], playerState[4];
    int playerCareer[4];
    QStringList playerTable[4], playerHand[4];

    void initGame();
    void readTableJson();
    QString readCardJson(QString);
    void setTableStatus();
    bool checkGameEnd();

protected:
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);

private slots:
    void receiveSettingData(QString, int);

    void on_btn_adventurer_clicked();
    void on_btn_builder_clicked();
    void on_btn_councillor_clicked();
    void on_btn_producer_clicked();
    void on_btn_trader_clicked();
    void on_btn_interaction_clicked();

    void on_actionNew_Game_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_As_triggered();
    void on_actionSetting_triggered();
    void on_actionHelp_triggered();
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QPushButton *btn_career[5];
    QLabel *player_info[4], *tp[4][12], *gd[4][12], *cardInfo, *mycard[24];

    bool scaleEnable[4][12], scaleMycardEnable[24], scaleCareerEnable[5];
    bool gameStart, canCallStart, p1SeCa, chooseMyCard[24], chooseTP1Card[12];
    bool p1ChMyCa, checkP1ChMyCa;
    bool p1BuCa, checkP1BuCa;
    bool p1RmCa, checkP1RmCa, PHMark;
    bool p1Prod, checkp1Prod;
    bool p1Trad, checkp1Trad;
    int playerChoiceCareer, cMCn, cMCm, rmCn, nCanProd, nCanTrad;
    bool newGameCheck;
    int robotLevel;
};
#endif // MAINWINDOW_H
