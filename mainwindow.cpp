#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameenddialog.h"
#include "settingdialog.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("San Juan");
    this->setStyleSheet("background-color: #80D4E0;");

    btn_career[0] = ui->btn_adventurer;
    btn_career[1] = ui->btn_builder;
    btn_career[2] = ui->btn_councillor;
    btn_career[3] = ui->btn_producer;
    btn_career[4] = ui->btn_trader;

    player_info[0] = ui->label_tp1;
    player_info[1] = ui->label_tp2;
    player_info[2] = ui->label_tp3;
    player_info[3] = ui->label_tp4;

    tp[0][0] = ui->tp1_01;
    tp[0][1] = ui->tp1_02;
    tp[0][2] = ui->tp1_03;
    tp[0][3] = ui->tp1_04;
    tp[0][4] = ui->tp1_05;
    tp[0][5] = ui->tp1_06;
    tp[0][6] = ui->tp1_07;
    tp[0][7] = ui->tp1_08;
    tp[0][8] = ui->tp1_09;
    tp[0][9] = ui->tp1_10;
    tp[0][10] = ui->tp1_11;
    tp[0][11] = ui->tp1_12;

    tp[1][0] = ui->tp2_01;
    tp[1][1] = ui->tp2_02;
    tp[1][2] = ui->tp2_03;
    tp[1][3] = ui->tp2_04;
    tp[1][4] = ui->tp2_05;
    tp[1][5] = ui->tp2_06;
    tp[1][6] = ui->tp2_07;
    tp[1][7] = ui->tp2_08;
    tp[1][8] = ui->tp2_09;
    tp[1][9] = ui->tp2_10;
    tp[1][10] = ui->tp2_11;
    tp[1][11] = ui->tp2_12;

    tp[2][0] = ui->tp3_01;
    tp[2][1] = ui->tp3_02;
    tp[2][2] = ui->tp3_03;
    tp[2][3] = ui->tp3_04;
    tp[2][4] = ui->tp3_05;
    tp[2][5] = ui->tp3_06;
    tp[2][6] = ui->tp3_07;
    tp[2][7] = ui->tp3_08;
    tp[2][8] = ui->tp3_09;
    tp[2][9] = ui->tp3_10;
    tp[2][10] = ui->tp3_11;
    tp[2][11] = ui->tp3_12;

    tp[3][0] = ui->tp4_01;
    tp[3][1] = ui->tp4_02;
    tp[3][2] = ui->tp4_03;
    tp[3][3] = ui->tp4_04;
    tp[3][4] = ui->tp4_05;
    tp[3][5] = ui->tp4_06;
    tp[3][6] = ui->tp4_07;
    tp[3][7] = ui->tp4_08;
    tp[3][8] = ui->tp4_09;
    tp[3][9] = ui->tp4_10;
    tp[3][10] = ui->tp4_11;
    tp[3][11] = ui->tp4_12;

    gd[0][0] = ui->gd1_01;
    gd[0][1] = ui->gd1_02;
    gd[0][2] = ui->gd1_03;
    gd[0][3] = ui->gd1_04;
    gd[0][4] = ui->gd1_05;
    gd[0][5] = ui->gd1_06;
    gd[0][6] = ui->gd1_07;
    gd[0][7] = ui->gd1_08;
    gd[0][8] = ui->gd1_09;
    gd[0][9] = ui->gd1_10;
    gd[0][10] = ui->gd1_11;
    gd[0][11] = ui->gd1_12;

    gd[1][0] = ui->gd2_01;
    gd[1][1] = ui->gd2_02;
    gd[1][2] = ui->gd2_03;
    gd[1][3] = ui->gd2_04;
    gd[1][4] = ui->gd2_05;
    gd[1][5] = ui->gd2_06;
    gd[1][6] = ui->gd2_07;
    gd[1][7] = ui->gd2_08;
    gd[1][8] = ui->gd2_09;
    gd[1][9] = ui->gd2_10;
    gd[1][10] = ui->gd2_11;
    gd[1][11] = ui->gd2_12;

    gd[2][0] = ui->gd3_01;
    gd[2][1] = ui->gd3_02;
    gd[2][2] = ui->gd3_03;
    gd[2][3] = ui->gd3_04;
    gd[2][4] = ui->gd3_05;
    gd[2][5] = ui->gd3_06;
    gd[2][6] = ui->gd3_07;
    gd[2][7] = ui->gd3_08;
    gd[2][8] = ui->gd3_09;
    gd[2][9] = ui->gd3_10;
    gd[2][10] = ui->gd3_11;
    gd[2][11] = ui->gd3_12;

    gd[3][0] = ui->gd4_01;
    gd[3][1] = ui->gd4_02;
    gd[3][2] = ui->gd4_03;
    gd[3][3] = ui->gd4_04;
    gd[3][4] = ui->gd4_05;
    gd[3][5] = ui->gd4_06;
    gd[3][6] = ui->gd4_07;
    gd[3][7] = ui->gd4_08;
    gd[3][8] = ui->gd4_09;
    gd[3][9] = ui->gd4_10;
    gd[3][10] = ui->gd4_11;
    gd[3][11] = ui->gd4_12;

    cardInfo = ui->label_cardInfo;
    cardInfo->setWordWrap(true);

    mycard[0] = ui->mycard_01;
    mycard[1] = ui->mycard_02;
    mycard[2] = ui->mycard_03;
    mycard[3] = ui->mycard_04;
    mycard[4] = ui->mycard_05;
    mycard[5] = ui->mycard_06;
    mycard[6] = ui->mycard_07;
    mycard[7] = ui->mycard_08;
    mycard[8] = ui->mycard_09;
    mycard[9] = ui->mycard_10;
    mycard[10] = ui->mycard_11;
    mycard[11] = ui->mycard_12;
    mycard[12] = ui->mycard_13;
    mycard[13] = ui->mycard_14;
    mycard[14] = ui->mycard_15;
    mycard[15] = ui->mycard_16;
    mycard[16] = ui->mycard_17;
    mycard[17] = ui->mycard_18;
    mycard[18] = ui->mycard_19;
    mycard[19] = ui->mycard_20;
    mycard[20] = ui->mycard_21;
    mycard[21] = ui->mycard_22;
    mycard[22] = ui->mycard_23;
    mycard[23] = ui->mycard_24;

    centralWidget()->setMouseTracking(true);
    setMouseTracking(true);
    for(int i=0; i<4; ++i){
        for(int j=0; j<12; ++j){
            tp[i][j]->setMouseTracking(true);
            scaleEnable[i][j] = false;
        }
    }
    for(int i=0; i<24; ++i){
        mycard[i]->setMouseTracking(true);
        scaleMycardEnable[i] = false;
    }
    for(int i=0; i<5; ++i){
        btn_career[i]->setMouseTracking(true);
        scaleCareerEnable[i] = false;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGame(){
    ui->btn_interaction->setText("Start");
    ui->textBrowser_interaction->setText("");
    gameStart = p1SeCa = p1ChMyCa = p1RmCa = false;
    p1BuCa = p1Prod = p1Trad = false;
    newGameCheck = false;
    playerChoiceCareer = 0;
    robotLevel = 1;
    QString dir = QCoreApplication::applicationDirPath() + "/C_Game/";
    QProcess *process = new QProcess();
    process->setWorkingDirectory(dir);
//    process->start("make clean");
//    process->waitForFinished();
//    process->start("make");
//    process->waitForFinished();
    process->start("initGame");
    process->waitForFinished();
    delete process;

    setTableStatus();
}

void MainWindow::readTableJson(){
    QString val;
    QFile file;
    file.setFileName(QCoreApplication::applicationDirPath() + "/C_Game/GameStatus/table.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject root = d.object();

    QJsonObject ps = root.value("Player State").toObject();
    for(int i=0; i<4; ++i)
        playerState[i] = ps.value("Player" + QString::number(i+1)).toBool();

    QJsonObject careerIsChoice = root.value("CareerIsChoice").toObject();
    QStringList careerStr = {"Adventurer", "Builder", "Councillor", "Producer", "Trader"};
    for(int i=0; i<5; ++i)
        career[i] = careerIsChoice.value(careerStr[i]).toBool();

    QJsonObject pc = root.value("Player Career").toObject();
    for(int i=0; i<4; ++i)
        playerCareer[i] = pc.value("Player" + QString::number(i+1)).toInt();

    QJsonObject cardOnTable = root.value("Card On Table").toObject();
    for(int i=0; i<4; ++i){
        QJsonArray cotPlayer = cardOnTable.value("Player" + QString::number(i+1)).toArray();
        playerTable[i].clear();
        for(int j=0; j<cotPlayer.size(); ++j)
            playerTable[i] << cotPlayer.at(j).toString();
    }

    memset(playerGoods, false, sizeof(playerGoods));
    for(int i=0; i<4; ++i){
        QJsonArray gdsPlayer = cardOnTable.value("Goods" + QString::number(i+1)). toArray();
        for(int j=0; j<gdsPlayer.size(); ++j){
            playerGoods[i][j] = gdsPlayer.at(j).toBool();
        }
    }

    QJsonObject HandCard = root.value("Hand Card").toObject();
    for(int i=0; i<4; ++i){
        QJsonArray hcPlayer = HandCard.value("Player" + QString::number(i+1)).toArray();
        playerHand[i].clear();
        for(int j=0; j<hcPlayer.size(); ++j)
            playerHand[i] << hcPlayer.at(j).toString();
    }
}

QString MainWindow::readCardJson(QString select){
    QString val;
    QFile file;
    file.setFileName(QCoreApplication::applicationDirPath() + "/C_Game/GameStatus/card.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject root = d.object();
    return root.value(select).toString();
}

void MainWindow::setTableStatus(){
    readTableJson();
    for(int i=0; i<5; ++i)
        btn_career[i]->setEnabled(career[i]);
    for(int i=0; i<4; ++i){
        for(int j=0; j<12; ++j) {
            tp[i][j]->setStyleSheet("");
            if(playerGoods[i][j]) gd[i][j]->setStyleSheet("background-color: red;");
            else gd[i][j]->setStyleSheet("");
        }
//        player_info[i]->setText("Player" + QString::number(i+1) + ":");
        int cntPS = 0;
        for(auto i: playerState) if(i) ++cntPS;
        for(int i=0; i<4; ++i){
            if(i+1 == cntPS) player_info[i]->setText("** Player" + QString::number(i+1) + ":");
            else player_info[i]->setText("Player" + QString::number(i+1) + ":");
        }

        int ncards = playerTable[i].size();
        for(int j=0; j<ncards; ++j){
            tp[i][j]->setStyleSheet("border-image: url(:/building/images/building/" + playerTable[i][j] + ".jpg);");
        }
    }
    for(int i=0; i<24; ++i) mycard[i]->setStyleSheet("");
    int nhcards = playerHand[0].size();
    for(int i=0; i<nhcards; ++i){
        mycard[i]->setStyleSheet("border-image: url(:/building/images/building/" + playerHand[0][i] + ".jpg);");
    }
}

bool MainWindow::checkGameEnd(){
    for(auto i: playerTable){
        if(i.size() == 12) {
            ui->textBrowser_interaction->setText("Game End!!");
            GameEndDialog *gameEndDig = new GameEndDialog(this);
            gameEndDig->exec();
            return true;
        }
    }
    return false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    int x = event->x(), y = event->y();
    for(int i=0; i<5; ++i){
        int lx = btn_career[i]->x(), ly = btn_career[i]->y();
        int lw = btn_career[i]->width(), lh = btn_career[i]->height();
        if(x>lx && x<lx+lw && y>ly && y<ly+lh && !scaleCareerEnable[i]){
            QString cardinfoStr = readCardJson("Career" + QString::number(i+1));
            cardInfo->setText(cardinfoStr);
            scaleCareerEnable[i] = true;
        }
        else scaleCareerEnable[i] = false;
    }
    for(int i=0; i<4; ++i){
        for(int j=0; j<12; ++j){
            int lx = tp[i][j]->x(), ly = tp[i][j]->y();
            int lw = tp[i][j]->width(), lh = tp[i][j]->height();
            if(x>lx && x<lx+lw && y>ly && y<ly+lh && !scaleEnable[i][j]){
                if(j < playerTable[i].size()) {
                    QString cardinfoStr = playerTable[i][j] + readCardJson(playerTable[i][j]);
                    cardInfo->setText(cardinfoStr);
                }
                scaleEnable[i][j] = true;
            }
            else scaleEnable[i][j] = false;
        }
    }
    for(int i=0; i<24; ++i){
        int lx = mycard[i]->x(), ly = mycard[i]->y();
        int lw = mycard[i]->width(), lh = mycard[i]->height();
        if(x>lx && x<lx+lw && y>ly && y<ly+lh && !scaleMycardEnable[i]){
            if(i< playerHand[0].size()){
                QString cardinfoStr = playerHand[0][i] + readCardJson(playerHand[0][i]);
                cardInfo->setText(cardinfoStr);
            }
            scaleMycardEnable[i] = true;
        }
        else scaleMycardEnable[i] = false;
    }
    bool flag = true;
    for(int i=0; i<4; ++i){
        for(int j=0; j<12; ++j){
            if(scaleEnable[i][j]){
                flag = false;
                break;
            }            
        }
    }
    if(flag){
        for(int i=0; i<24; ++i){
            if(scaleMycardEnable[i]){
                flag = false;
                break;
            }
        }
    }
    if(flag){
        for(int i=0; i<5; ++i){
            if(scaleCareerEnable[i]){
                flag = false;
                break;
            }
        }
    }
    if(flag) cardInfo->setText("");
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    int x = event->x(), y = event->y();
    if(event->button() == Qt::LeftButton){
        bool flag = true;
        for(int i=0; i<24; ++i){
            int lx = mycard[i]->x(), ly = mycard[i]->y();
            int lw = mycard[i]->width(), lh = mycard[i]->height();
            if(x>lx && x<lx+lw && y>ly && y<ly+lh){
                chooseMyCard[i] = !chooseMyCard[i];
                if(i < playerHand[0].size()){
                    if(chooseMyCard[i])
                        mycard[i]->setStyleSheet("border-image: url(:/building/images/building/" + playerHand[0][i] + ".jpg); border: 5px solid red;");
                    else mycard[i]->setStyleSheet("border-image: url(:/building/images/building/" + playerHand[0][i] + ".jpg);");
                }
                flag = false;
                break;
            }
        }
        if(flag){
            for(int i=0; i<12; ++i){
                int lx = tp[0][i]->x(), ly = tp[0][i]->y();
                int lw = tp[0][i]->width(), lh = tp[0][i]->height();
                if(x>lx && x<lx+lw && y>ly && y<ly+lh){
                    chooseTP1Card[i] = !chooseTP1Card[i];
                    if(i < playerTable[0].size()){
                        if(chooseTP1Card[i]) tp[0][i]->setStyleSheet("border-image: url(:/building/images/building/" + playerTable[0][i] + ".jpg); border: 5px solid red;");
                        else tp[0][i]->setStyleSheet("border-image: url(:/building/images/building/" + playerTable[0][i] + ".jpg);");
                    }
                    break;
                }
            }
        }
    }
}

void MainWindow::on_btn_adventurer_clicked() {
    if(p1SeCa){
        playerChoiceCareer = 1;
        ui->textBrowser_interaction->setText("你要選擇的職業是 Adventurer?");
    }
}

void MainWindow::on_btn_builder_clicked() {
    if(p1SeCa){
        playerChoiceCareer = 2;
        ui->textBrowser_interaction->setText("你要選擇的職業是 Builder?");
    }
}

void MainWindow::on_btn_councillor_clicked() {
    if(p1SeCa){
        playerChoiceCareer = 3;
        ui->textBrowser_interaction->setText("你要選擇的職業是 Councillor?");
    }
}

void MainWindow::on_btn_producer_clicked() {
    if(p1SeCa){
        playerChoiceCareer = 4;
        ui->textBrowser_interaction->setText("你要選擇的職業是 Producer?");
    }
}

void MainWindow::on_btn_trader_clicked() {
    if(p1SeCa){
        playerChoiceCareer = 5;
        ui->textBrowser_interaction->setText("你要選擇的職業是 Trader?");
    }
}

void MainWindow::on_btn_interaction_clicked() {
    if(!gameStart){
        QString dir = QCoreApplication::applicationDirPath() + "/C_Game/";
        QProcess *process = new QProcess();
        process->setWorkingDirectory(dir);
        for(int i=0; i<4; ++i){
            for(int j=0; j<4; ++j){
                process->start("game --distribute " + QString::number(j+1) + "/1");
                process->waitForFinished();
            }

        }
        delete process;
        ui->textBrowser_interaction->setText("遊戲開始!");
        ui->btn_interaction->setText("Okay");
        gameStart = true;
        canCallStart = true;
        newGameCheck = true;
    }
    else if(!checkGameEnd()){
        if(p1SeCa && playerChoiceCareer!=0){
            QFile file(QCoreApplication::applicationDirPath() + "/C_Game/GameStatus/table.json");
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            QJsonParseError JsonParseError;
            QJsonDocument JsonDocument = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
            file.close();
            QJsonObject RootObject = JsonDocument.object();
            QJsonValueRef ref = RootObject.find("Player Career").value();
            QJsonObject m_addvalue = ref.toObject();
            m_addvalue.insert("Player1", playerChoiceCareer);
            ref = m_addvalue;
            JsonDocument.setObject(RootObject);
            file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
            file.write(JsonDocument.toJson());
            file.close();
            p1SeCa = false;
            playerChoiceCareer = 0;
        }
        if(p1ChMyCa){
            ui->textBrowser_interaction->setText("從最後 " + QString::number(cMCn) + " 張選出 " + QString::number(cMCm) + " 張");
            ui->textBrowser_interaction->append("\n目前選擇：\n");
            int cntHaveCard = playerHand[0].size();
            int cnt = 0;
            for(int i=cntHaveCard - cMCn; i<cntHaveCard; ++i){
                if(chooseMyCard[i]) {
                    ui->textBrowser_interaction->append(playerHand[0][i] + "\n");
                    ++cnt;
                }
            }
            if(cnt == cMCm){
                if(!checkP1ChMyCa){
                    ui->textBrowser_interaction->append("\n確認選擇請按 Okay！");
                    checkP1ChMyCa = true;
                }
                else {
                    QFile file(QCoreApplication::applicationDirPath() + "/C_Game/GameStatus/table.json");
                    file.open(QIODevice::ReadOnly | QIODevice::Text);
                    QJsonParseError JsonParseError;
                    QJsonDocument JsonDocument = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
                    file.close();
                    QJsonObject RootObject = JsonDocument.object();
                    QJsonObject hcObj = RootObject.find("Hand Card").value().toObject();
                    QJsonObject deckObj = RootObject.find("Deck").value().toObject();
                    QJsonArray p1Arr = hcObj.find("Player1").value().toArray();
                    QJsonArray deadwood = deckObj.find("Deadwood").value().toArray();
                    QStringList temp;
                    for(int i=cntHaveCard - cMCn; i<cntHaveCard; ++i) {
                        if(chooseMyCard[i]) temp.append(playerHand[0][i]);
                        else deadwood.append(playerHand[0][i]);
                    }
                    for(int i=0; i<cMCn; ++i) p1Arr.removeLast();
                    for(int i=0; i<temp.size(); ++i) p1Arr.append(temp[i]);
                    deckObj.insert("Deadwood", deadwood);
                    hcObj.insert("Player1", p1Arr);
                    RootObject.insert("Deck", deckObj);
                    RootObject.insert("Hand Card", hcObj);
                    JsonDocument.setObject(RootObject);
                    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
                    file.write(JsonDocument.toJson());
                    file.close();
                    ui->textBrowser_interaction->setText("");
                    p1ChMyCa = false;
                    canCallStart = true;
                }
            }
            else {
                ui->textBrowser_interaction->append("\n請重新選擇, 並確認！！");
                memset(chooseMyCard, false, sizeof(chooseMyCard));
                checkP1ChMyCa = false;
            }
        }
        if(p1RmCa){
            ui->textBrowser_interaction->setText("選擇 " + QString::number(rmCn) + "張手牌支付");
            ui->textBrowser_interaction->append("\n目前選擇：\n");
            int cntHaveCard = playerHand[0].size();
            int cnt = 0;
            for(int i=0; i<cntHaveCard; ++i){
                if(chooseMyCard[i]) {
                    ui->textBrowser_interaction->append(playerHand[0][i] + "\n");
                    ++cnt;
                }
            }
            if(cnt == rmCn){
                if(!checkP1RmCa){
                    ui->textBrowser_interaction->append("\n確認選擇請按 Okay！");
                    checkP1RmCa = true;
                }
                else{
                    QFile file(QCoreApplication::applicationDirPath() + "/C_Game/GameStatus/table.json");
                    file.open(QIODevice::ReadOnly | QIODevice::Text);
                    QJsonParseError JsonParseError;
                    QJsonDocument JsonDocument = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
                    file.close();
                    QJsonObject RootObject = JsonDocument.object();
                    QJsonObject hcObj = RootObject.find("Hand Card").value().toObject();
                    QJsonObject deckObj = RootObject.find("Deck").value().toObject();
                    QJsonArray p1Arr = hcObj.find("Player1").value().toArray();
                    QJsonArray deadwood = deckObj.find("Deadwood").value().toArray();
                    QStringList temp;
                    for(int i=0; i<cntHaveCard; ++i)
                        if(chooseMyCard[i]) temp.append(playerHand[0][i]);
                    for(int i=0; i<temp.size(); ++i){
                        int pos = -1;
                        for(int j=0; j<p1Arr.size();++j){
                            if(temp[i] == p1Arr.at(j).toString()) {
                                pos = j;
                                break;
                            }
                        }
                        if(pos != -1) {
                            deadwood.append(temp[i]);
                            p1Arr.removeAt(pos);
                        }
                    }
                    deckObj.insert("Deadwood", deadwood);
                    hcObj.insert("Player1", p1Arr);
                    RootObject.insert("Deck", deckObj);
                    RootObject.insert("Hand Card", hcObj);
                    JsonDocument.setObject(RootObject);
                    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
                    file.write(JsonDocument.toJson());
                    file.close();
                    readTableJson();
                    if(PHMark && playerHand[0].size()<=1){
                        QString dir = QCoreApplication::applicationDirPath() + "/C_Game/";
                        QProcess *process = new QProcess();
                        process->setWorkingDirectory(dir);
                        process->start("game --distribute 1/1");
                        process->waitForFinished();
                        delete process;
                    }
                    p1RmCa = false;
                    canCallStart = true;
                }
            }
            else {
                ui->textBrowser_interaction->append("\n請重新選擇, 並確認！！");
                memset(chooseMyCard, false, sizeof(chooseMyCard));
                checkP1RmCa = false;
            }
        }
        if(p1BuCa){
            ui->textBrowser_interaction->setText("請選擇一張卡牌建造！");
            ui->textBrowser_interaction->append("\n目前選擇：\n");
            int cntHaveCard = playerHand[0].size();
            int cnt = 0;
            for(int i=0; i<cntHaveCard; ++i){
                if(chooseMyCard[i]) {
                    ui->textBrowser_interaction->append(playerHand[0][i] + "\n");
                    ++cnt;
                }
            }
            if(cnt <= 1){
                if(!checkP1BuCa){
                    if(cnt == 0) ui->textBrowser_interaction->append("\n不建造建築！");
                    ui->textBrowser_interaction->append("\n確認選擇請按 Okay！");
                    checkP1BuCa = true;
                }
                else{
                    if(cnt == 0) {
                        p1BuCa = false;
                        canCallStart = true;
                    }
                    else {
                        int q;
                        for(int i=0; i<cntHaveCard; ++i){
                            if(chooseMyCard[i]){
                                q = i;
                                break;
                            }
                        }
                        QString dir = QCoreApplication::applicationDirPath() + "/C_Game/";
                        QProcess *process = new QProcess();
                        process->setWorkingDirectory(dir);
                        process->start("game --builder " + QString::number(q));
                        process->waitForFinished();
                        QString getStr = QString(process->readAllStandardOutput());
                        delete process;
                        if(getStr.contains("Can Build.", Qt::CaseSensitive)){
                            int ph, ch;
                            sscanf(getStr.toStdString().c_str(), "Can Build. Cost:%d. %d, %d", &rmCn, &ph, &ch);
                            PHMark = ph;
                            if(ch){
                                QString dir = QCoreApplication::applicationDirPath() + "/C_Game/";
                                QProcess *process = new QProcess();
                                process->setWorkingDirectory(dir);
                                process->start("game --distribute 1/1");
                                process->waitForFinished();
                                delete process;
                            }
                            ui->textBrowser_interaction->setText("選擇 " + QString::number(rmCn) + "張手牌支付");
                            memset(chooseMyCard, false, sizeof(chooseMyCard));
                            p1RmCa = true;
                            checkP1RmCa = false;
                            p1BuCa = false;
                        }
                        else{
                            ui->textBrowser_interaction->setText("此張牌無法建造，請重新選擇！");
                            memset(chooseMyCard, false, sizeof(chooseMyCard));
                            checkP1BuCa = false;
                        }
                    }
                }
            }
            else {
                ui->textBrowser_interaction->append("\n請重新選擇, 並確認！！");
                memset(chooseMyCard, false, sizeof(chooseMyCard));
                checkP1BuCa = false;
            }
        }
        if(p1Prod){
            ui->textBrowser_interaction->setText("可生產 " + QString::number(nCanProd) + " 個物品");
            ui->textBrowser_interaction->append("目前選擇要生產貨物的工廠:");
            int cntHaveCard = playerTable[0].size();
            int cnt = 0;
            QStringList productionStr = {"Tomato plant", "Pond farm", "Mill", "Zeppelin shipyard", "Shipyard"};
            for(int i=0; i<cntHaveCard; ++i){
                bool flag = false;
                for(auto j: productionStr){
                    if(playerTable[0][i] == j){
                        flag = true;
                        break;
                    }
                }
                if(flag && chooseTP1Card[i] && !playerGoods[0][i]) {
                    ui->textBrowser_interaction->append("第 " + QString::number(i+1) + " 間工廠: " + playerTable[0][i] + "\n");
                    ++cnt;
                }
            }
            if(cnt <= nCanProd){
                if(!checkp1Prod){
                    if(cnt < nCanProd) ui->textBrowser_interaction->append("\n還能生產更多！要以當前狀態結束");
                    ui->textBrowser_interaction->append("\n確認選擇請按 Okay！");
                    checkp1Prod = true;
                }
                else {
                    QFile file(QCoreApplication::applicationDirPath() + "/C_Game/GameStatus/table.json");
                    file.open(QIODevice::ReadOnly | QIODevice::Text);
                    QJsonParseError JsonParseError;
                    QJsonDocument JsonDocument = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
                    file.close();
                    QJsonObject RootObject = JsonDocument.object();
                    QJsonObject cotObj = RootObject.find("Card On Table").value().toObject();
                    QJsonObject deckObj = RootObject.find("Deck").value().toObject();
                    QJsonArray gd1Arr = cotObj.find("Goods1").value().toArray();
                    QJsonArray deadwood = deckObj.find("Deadwood").value().toArray();
                    for(int i=0; i<cntHaveCard; ++i){
                        bool flag = false;
                        for(auto j: productionStr){
                            if(playerTable[0][i] == j){
                                flag = true;
                                break;
                            }
                        }
                        if(flag && chooseTP1Card[i] && !playerGoods[0][i]) {
                            deadwood.append(playerTable[0][i]);
                            gd1Arr.replace(i, true);
                        }
                    }
                    cotObj.insert("Goods1", gd1Arr);
                    RootObject.insert("Card On Table", cotObj);
                    int posDeck = deckObj.find("posDeck").value().toInt() + cnt;
                    deckObj.insert("posDeck", posDeck);
                    deckObj.insert("Deadwood", deadwood);
                    RootObject.insert("Deck", deckObj);
                    JsonDocument.setObject(RootObject);
                    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
                    file.write(JsonDocument.toJson());
                    file.close();
                    bool hoFlag = false;
                    for(auto i: playerTable[0]){
                        if(i == "Households") {
                            hoFlag = true;
                            break;
                        }
                    }
                    if(cnt >= 2 && hoFlag) {
                        QString dir = QCoreApplication::applicationDirPath() + "/C_Game/";
                        QProcess *process = new QProcess();
                        process->setWorkingDirectory(dir);
                        process->start("game --distribute 1/1");
                        process->waitForFinished();
                        delete process;
                    }
                    ui->textBrowser_interaction->setText("");
                    p1Prod = false;
                    canCallStart = true;
                }
            }
            else {
                ui->textBrowser_interaction->append("\n請重新選擇, 並確認！！");
                memset(chooseTP1Card, false, sizeof(chooseTP1Card));
                checkp1Prod = false;
            }
        }
        if(p1Trad){
            ui->textBrowser_interaction->setText("可出售 " + QString::number(nCanTrad) + " 個物品");
            ui->textBrowser_interaction->append("請選擇要出售貨物的工廠");
            int cntHaveCard = playerTable[0].size();
            int cnt = 0;
            for(int i=0; i<cntHaveCard; ++i){
                if(chooseTP1Card[i] && playerGoods[0][i]) {
                    ui->textBrowser_interaction->append("第 " + QString::number(i+1) + " 間工廠: " + playerTable[0][i] + "\n");
                    ++cnt;
                }
            }
            if(cnt <= nCanTrad){
                if(!checkp1Trad){
                    if(cnt < nCanTrad) ui->textBrowser_interaction->append("\n還能賣出更多！要以當前狀態結束");
                    ui->textBrowser_interaction->append("\n確認選擇請按 Okay！");
                    checkp1Trad = true;
                }
                else {
                    int prices = 0;
                    QFile file(QCoreApplication::applicationDirPath() + "/C_Game/GameStatus/table.json");
                    file.open(QIODevice::ReadOnly | QIODevice::Text);
                    QJsonParseError JsonParseError;
                    QJsonDocument JsonDocument = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
                    file.close();
                    QJsonObject RootObject = JsonDocument.object();
                    QJsonObject cotObj = RootObject.find("Card On Table").value().toObject();
                    QJsonArray gd1Arr = cotObj.find("Goods1").value().toArray();
                    QJsonArray trCaArr = RootObject.find("Trading Card").value().toArray().at(0).toArray();
                    QStringList productionStr = {"Tomato plant", "Pond farm", "Mill", "Zeppelin shipyard", "Shipyard"};
                    for(int i=0; i<cntHaveCard; ++i){
                        if(chooseTP1Card[i] && playerGoods[0][i]) {
                            gd1Arr.replace(i, false);
                            for(int j=0; j<5; ++j){
                                if(playerTable[0][i] == productionStr[j])
                                    prices += trCaArr.at(j).toInt();
                            }
                        }
                    }
                    cotObj.insert("Goods1", gd1Arr);
                    RootObject.insert("Card On Table", cotObj);
                    JsonDocument.setObject(RootObject);
                    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
                    file.write(JsonDocument.toJson());
                    file.close();

                    QString dir = QCoreApplication::applicationDirPath() + "/C_Game/";
                    QProcess *process = new QProcess();
                    process->setWorkingDirectory(dir);
                    process->start("game --distribute 1/" + QString::number(prices));
                    process->waitForFinished();
                    delete process;

                    bool maPlFlag = false, trRoFlag = false;
                    for(auto i: playerTable[0]){
                        if(i == "Marketplace") maPlFlag = true;
                        if(i == "Trade route") trRoFlag = true;
                        if(maPlFlag && trRoFlag) break;
                    }
                    if(cnt >= 2 && maPlFlag) {
                        QString dir = QCoreApplication::applicationDirPath() + "/C_Game/";
                        QProcess *process = new QProcess();
                        process->setWorkingDirectory(dir);
                        process->start("game --distribute 1/1");
                        process->waitForFinished();
                        delete process;
                    }
                    if(trRoFlag) {
                        QString dir = QCoreApplication::applicationDirPath() + "/C_Game/";
                        QProcess *process = new QProcess();
                        process->setWorkingDirectory(dir);
                        process->start("game --distribute 1/1");
                        process->waitForFinished();
                        delete process;
                    }
                    ui->textBrowser_interaction->setText("");
                    p1Trad = false;
                    canCallStart = true;
                }
            }
            else {
                ui->textBrowser_interaction->append("\n請重新選擇, 並確認！！");
                memset(chooseTP1Card, false, sizeof(chooseTP1Card));
                checkp1Trad = false;
            }
        }
        if(canCallStart){
            QString dir = QCoreApplication::applicationDirPath() + "/C_Game/";
            QProcess *process = new QProcess();
            process->setWorkingDirectory(dir);
            process->start("game --start");
            process->waitForFinished();
            QString getStr = QString(process->readAllStandardOutput());
            delete process;
            qDebug()<<getStr<<endl;
            if(getStr == "P1 select career"){
                ui->textBrowser_interaction->setText("請選擇一個職業!");
                p1SeCa = true;
            }
            else if(getStr.contains("ChooseFromDeck", Qt::CaseSensitive)){
                sscanf(getStr.toStdString().c_str(), "ChooseFromDeck:%d/%d", &cMCn, &cMCm);
                ui->textBrowser_interaction->setText("從最後 " + QString::number(cMCn) + " 張選出 " + QString::number(cMCm) + " 張");
                memset(chooseMyCard, false, sizeof(chooseMyCard));
                p1ChMyCa = true;
                checkP1ChMyCa = false;
                canCallStart = false;
            }
            else if(getStr == "P1 Build"){
                ui->textBrowser_interaction->setText("請選擇一張卡牌建造！");
                memset(chooseMyCard, false, sizeof(chooseMyCard));
                p1BuCa = true;
                checkP1BuCa = false;
                canCallStart = false;
            }
            else if(getStr.contains("Can Produce", Qt::CaseSensitive)){
                sscanf(getStr.toStdString().c_str(), "Can Produce %d items", &nCanProd);
                ui->textBrowser_interaction->setText("可生產 " + QString::number(nCanProd) + " 個物品");
                ui->textBrowser_interaction->append("請選擇要生產貨物的工廠");
                memset(chooseTP1Card, false, sizeof(chooseTP1Card));
                p1Prod = true;
                checkp1Prod = false;
                canCallStart = false;
            }
            else if(getStr.contains("Can Trade", Qt::CaseSensitive)){
                sscanf(getStr.toStdString().c_str(), "Can Trade %d items", &nCanTrad);
                ui->textBrowser_interaction->setText("可出售 " + QString::number(nCanTrad) + " 個物品");
                ui->textBrowser_interaction->append("請選擇要出售貨物的工廠");
                memset(chooseTP1Card, false, sizeof(chooseTP1Card));
                p1Trad = true;
                checkp1Trad = false;
                canCallStart = false;
            }
        }
    }
    setTableStatus();
}

void MainWindow::on_actionNew_Game_triggered() {
    if(newGameCheck){
        QMessageBox box;
        box.setWindowTitle("警告");
        box.setIcon(QMessageBox::Warning);
        box.setText("開啟新局?");
        QPushButton *yesBtn = box.addButton("確定(&Y)", QMessageBox::YesRole);
        box.exec();
        if(box.clickedButton() == yesBtn) initGame();
    }
}

void MainWindow::on_actionOpen_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Game Data", QCoreApplication::applicationDirPath() + "/SaveData/", "Json File(*.json)");
    if(!fileName.isEmpty()){
        initGame();
        QString saveData = QCoreApplication::applicationDirPath() + "/C_Game/GameStatus/table.json";
        QFile::remove(saveData);
        QFile::copy(fileName, saveData);
        gameStart = true;
        canCallStart = true;
        newGameCheck = true;
        setTableStatus();
    }
}

void MainWindow::on_actionSave_As_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Game Data", QCoreApplication::applicationDirPath() + "/SaveData/", "Json File(*.json)");
    if(!fileName.isEmpty()){
        QString saveData = QCoreApplication::applicationDirPath() + "/C_Game/GameStatus/table.json";
        QFile::remove(fileName);
        QFile::copy(saveData, fileName);
    }
}

void MainWindow::receiveSettingData(QString bgColor, int rbL){
    this->setStyleSheet("background-color: " + bgColor + ";");
    robotLevel = rbL;
}

void MainWindow::on_actionSetting_triggered() {
    SettingDialog *settingDig = new SettingDialog(this);
    connect(settingDig, SIGNAL(sendSettingData(QString, int)), this, SLOT(receiveSettingData(QString, int)));
    settingDig->exec();
}

void MainWindow::on_actionHelp_triggered() {
    QMessageBox box;
    box.setWindowTitle("Help");
    box.setText("需要幫忙?請聯絡我們！\n但你應該找不到人(咦~");
    box.addButton(QMessageBox::Ok);
    box.button(QMessageBox::Ok)->hide();
    box.exec();
}

void MainWindow::on_actionAbout_triggered() {
    AboutDialog *aboutDig = new AboutDialog(this);
    aboutDig->exec();
}
