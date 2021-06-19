#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Setting");
    ui->bgColor_lineEdit->setPlaceholderText("＃80D4E0");
    ui->robotLevel->setId(ui->radioButton, 1);
    ui->robotLevel->setId(ui->radioButton_2, 2);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}


void SettingDialog::on_submit_btn_clicked()
{
    QString bgColor = ui->bgColor_lineEdit->text();
    int robotLevel = ui->robotLevel->checkedId();
    if(bgColor.length()>0 && robotLevel>=1 && robotLevel<=2)
        emit sendSettingData(bgColor, robotLevel);

}
