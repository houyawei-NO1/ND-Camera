#include "resultdialog.h"
#include <QDebug>

ResultDialog::ResultDialog(QWidget *parent) : QWidget(parent)
{
    setContentsMargins(0,0,0,0);
//    this->setStyleSheet("background-color:green");
    this->setStyleSheet("background-color:rgb(43,48,70)");

    MainLayout = new QVBoxLayout();
    MainLayout->setSpacing(0);
    hboxlayout = new QHBoxLayout();
    hboxlayout->setSpacing(0);

    ResultLabel =  new QLabel;
    ResultLabel->setText("");
    ResultLabel->setStyleSheet("color:white;font:20px");
    ResultLabel->setWordWrap(true);
    ResultLabel->setAlignment(Qt::AlignVCenter);
    ResultLabel->setGeometry(50, 50, 200, 100);

    // MainLayout->addStretch(1);
    MainLayout->addWidget(ResultLabel);
    // MainLayout->addStretch(1);
    setLayout(MainLayout);

}
void ResultDialog::rec_BuhegeXiangmu(QString str_bhg)
{
    qDebug()<<str_bhg.size();
    if(str_bhg.size()>255) str_bhg="设备未上电";
    else if(str_bhg.size()<=17) str_bhg="当前产品检验通过";
    ResultLabel->setText(str_bhg);
}
