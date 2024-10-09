#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color:black;");//rgb(28,32,48)
    this->setWindowFlags(Qt::FramelessWindowHint);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
//    currentScreenWid = (screenRect.width()*3/4);
//    currentScreenHei = (screenRect.height()*4/5 - 100);
    currentScreenWid = (screenRect.width());
    currentScreenHei = (screenRect.height() - 100);
    this->setFixedSize(currentScreenWid,currentScreenHei);

    mainlayout = new QHBoxLayout(this);
    mainlayout->setSpacing(10);
    gridlayout_left = new QGridLayout();
    gridlayout_right = new QGridLayout();
    mainlayout->addLayout(gridlayout_left,1);
    mainlayout->addLayout(gridlayout_right,1);//比例无效
    Init();
    gridlayout_left->setMargin(0);
    gridlayout_right->setMargin(0);
    gridlayout_left->setSpacing(0);
    gridlayout_right->setSpacing(0);
    gridlayout_left->setContentsMargins(0,25,0,20);
    gridlayout_right->setContentsMargins(0,25,0,20);
    m_buhege = "";
//    setLayout(gridlayout);

    connect(this, SIGNAL(send_BuhegeXiangmu(QString)), resultDialog, SLOT(rec_BuhegeXiangmu(QString)),Qt::QueuedConnection);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Cal_TotleNum()));
    timer->start(1000);




}
void MainWidget::Init()
{

//    QWidget* top = new QWidget(this);
//    gridlayout->addWidget(top,0,0,1,14);

    QWidget* top = new QWidget(this);
    top->setStyleSheet("border-radius: 20px;background-color:rgb(43,48,70)");
//    top->setContentsMargins(5, 5, 5, 50);
    gridlayout_left->addWidget(top,0,0,8,8);

    ledwidget[0] = new LedWidget(top);
    ledwidget[0]->show();
    ledwidget[0]->Init("PS1-DI01");
    gridlayout_left->addWidget(ledwidget[0],0,0,2,2);
    ledwidget[1] = new LedWidget(top);
    ledwidget[1]->show();
    ledwidget[1]->Init("PS1-DI02");
    gridlayout_left->addWidget(ledwidget[1],0,2,2,2);
    ledwidget[2] = new LedWidget(top);
    ledwidget[2]->show();
    ledwidget[2]->Init("PS1-DI03");
    gridlayout_left->addWidget(ledwidget[2],0,4,2,2);
    ledwidget[3] = new LedWidget(top);
    ledwidget[3]->show();
    ledwidget[3]->Init("PS1-DI04");
    gridlayout_left->addWidget(ledwidget[3],0,6,2,2);

    ledwidget[4] = new LedWidget(top);
    ledwidget[4]->show();
    ledwidget[4]->Init("PS1-DI05");
    gridlayout_left->addWidget(ledwidget[4],2,0,2,2);
    ledwidget[5] = new LedWidget(top);
    ledwidget[5]->show();
    ledwidget[5]->Init("PS2-DI06");
    gridlayout_left->addWidget(ledwidget[5],2,2,2,2);
    ledwidget[6] = new LedWidget(top);
    ledwidget[6]->show();
    ledwidget[6]->Init("PS2-DI07");
    gridlayout_left->addWidget(ledwidget[6],2,4,2,2);
    ledwidget[7] = new LedWidget(top);
    ledwidget[7]->show();
    ledwidget[7]->Init("PS2-DI08");
    gridlayout_left->addWidget(ledwidget[7],2,6,2,2);

    ledwidget[8] = new LedWidget(top);
    ledwidget[8]->show();
    ledwidget[8]->Init("PS1-DI09");
    gridlayout_left->addWidget(ledwidget[8],4,0,2,2);
    ledwidget[9] = new LedWidget(top);
    ledwidget[9]->show();
    ledwidget[9]->Init("地-DI10");
    gridlayout_left->addWidget(ledwidget[9],4,2,2,2);
    ledwidget[10] = new LedWidget(top);
    ledwidget[10]->show();
    ledwidget[10]->Init("PS3-DI11");
    gridlayout_left->addWidget(ledwidget[10],4,4,2,2);
    ledwidget[11] = new LedWidget(top);
    ledwidget[11]->show();
    ledwidget[11]->Init("PS3-DI12");
    gridlayout_left->addWidget(ledwidget[11],4,6,2,2);

    ledwidget[12] = new LedWidget(top);
    ledwidget[12]->show();
    ledwidget[12]->Init("PS3-DI13");
    gridlayout_left->addWidget(ledwidget[12],6,0,2,2);
    ledwidget[13] = new LedWidget(top);
    ledwidget[13]->show();
    ledwidget[13]->Init("PS3-DI14");
    gridlayout_left->addWidget(ledwidget[13],6,2,2,2);
    ledwidget[14] = new LedWidget(top);
    ledwidget[14]->show();
    ledwidget[14]->Init("PS3-DI15");
    gridlayout_left->addWidget(ledwidget[14],6,4,2,2);
    ledwidget[15] = new LedWidget(top);
    ledwidget[15]->show();
    ledwidget[15]->Init("PS3-DI16");
    gridlayout_left->addWidget(ledwidget[15],6,6,2,2);

    // ledwidget[16] = new LedWidget(top);
    // ledwidget[16]->show();
    // ledwidget[16]->Init("PS3-17");
    // gridlayout_left->addWidget(ledwidget[16],8,0,2,2);
    // ledwidget[17] = new LedWidget(top);
    // ledwidget[17]->show();
    // ledwidget[17]->Init("PS3-18");
    // gridlayout_left->addWidget(ledwidget[17],8,2,2,2);

    QWidget* mid = new QWidget(this);
    mid->setStyleSheet("border-radius: 20px;background-color:black");
    gridlayout_left->addWidget(mid,8,0,1,8);

    QWidget* buttom = new QWidget(this);
    buttom->setStyleSheet("border-radius: 20px;background-color:rgb(43,48,70)");
//    buttom->setContentsMargins(50, 50, 50, 50);
    gridlayout_left->addWidget(buttom,9,0,2,8);

    textwidget[0] = new TextWidget(this);
    textwidget[0]->show();
    textwidget[0]->Init("AI-01","mV");
    gridlayout_left->addWidget(textwidget[0],9,0,1,2);
    textwidget[1] = new TextWidget(this);
    textwidget[1]->show();
    textwidget[1]->Init("AI-02","mV");
    gridlayout_left->addWidget(textwidget[1],9,2,1,2);
    textwidget[2] = new TextWidget(this);
    textwidget[2]->show();
    textwidget[2]->Init("AI-03","mV");
    gridlayout_left->addWidget(textwidget[2],9,4,1,2);
    textwidget[3] = new TextWidget(this);
    textwidget[3]->show();
    textwidget[3]->Init("AI-04","mV");
    gridlayout_left->addWidget(textwidget[3],9,6,1,2);

    textwidget[4] = new TextWidget(this);
    textwidget[4]->show();
    textwidget[4]->Init("AI-05","mV");
    gridlayout_left->addWidget(textwidget[4],10,0,1,2);
    textwidget[5] = new TextWidget(this);
    textwidget[5]->show();
    textwidget[5]->Init("AI-06","mV");
    gridlayout_left->addWidget(textwidget[5],10,2,1,2);
    textwidget[6] = new TextWidget(this);
    textwidget[6]->show();
    textwidget[6]->Init("AI-07","mV");
    gridlayout_left->addWidget(textwidget[6],10,4,1,2);
    textwidget[7] = new TextWidget(this);
    textwidget[7]->show();
    textwidget[7]->Init("AI-08","mV");
    gridlayout_left->addWidget(textwidget[7],10,6,1,2);


    chartviewwid = new ChartViewWid(this);
    chartviewwid->Init("电磁阀电流");
//    chartviewwid[1] = new ChartViewWid(this);
//    chartviewwid[1]->Init("四驱电磁阀");
//    chartviewwid[2] = new ChartViewWid(this);
//    chartviewwid[2]->Init("蜂鸣器电磁阀");
//    chartviewwid[3] = new ChartViewWid(this);
//    chartviewwid[3]->Init("PTO电磁阀");
    electric_change(0,0,0,0,0,0,0,0/*,0,0,0,0*/);
    m_totlenum = 0;


    QWidget* right1 = new QWidget(this);
    right1->setStyleSheet("border-radius: 20px;background-color:rgb(43,48,70)");
    resultDialog = new ResultDialog();
    gridlayout_right->addWidget(resultDialog,0,0,4,8);
    gridlayout_right->addWidget(right1,0,0,4,8);
    QWidget* right1_mid = new QWidget(this);
    right1_mid->setStyleSheet("border-radius: 20px;background-color:black");
    gridlayout_right->addWidget(right1_mid,4,0,1,8);

    QWidget* right2 = new QWidget(this);
    right2->setStyleSheet("border-radius: 20px;background-color:rgb(43,48,70)");
    gridlayout_right->addWidget(right2,5,0,2,8);
    textwidget[8] = new TextWidget(right2);
    textwidget[8]->show();
    textwidget[8]->Init("FI-01","hZ");
    gridlayout_right->addWidget(textwidget[8],5,0,1,1);
    textwidget[9] = new TextWidget(right2);
    textwidget[9]->show();
    textwidget[9]->Init("FI-02","hZ");
    gridlayout_right->addWidget(textwidget[9],5,1,1,1);
    textwidget[10] = new TextWidget(right2);
    textwidget[10]->show();
    textwidget[10]->Init("FI-03","hZ");
    gridlayout_right->addWidget(textwidget[10],5,2,1,1);
    // textwidget[9] = new TextWidget(right2);
    // textwidget[9]->show();
    // textwidget[9]->Init("FI-04","hZ");
    // gridlayout_right->addWidget(textwidget[9],5,3,1,1);

    // textwidget[10] = new TextWidget(right2);
    // textwidget[10]->show();
    // textwidget[10]->Init("FI-05","hZ");
    // gridlayout_right->addWidget(textwidget[10],6,0,1,1);
    // textwidget[11] = new TextWidget(right2);
    // textwidget[11]->show();
    // textwidget[11]->Init("FI-06","hZ");
    // gridlayout_right->addWidget(textwidget[11],6,1,1,1);
    // textwidget[12] = new TextWidget(right2);
    // textwidget[12]->show();
    // textwidget[12]->Init("FI-07","hZ");
    // gridlayout_right->addWidget(textwidget[12],6,2,1,1);
    QWidget* right2_mid = new QWidget(this);
    right2_mid->setStyleSheet("border-radius: 20px;background-color:black");
    gridlayout_right->addWidget(right2_mid,7,0,1,8);

     gridlayout_right->addWidget(chartviewwid,8,0,25,8);
//    gridlayout_right->addWidget(chartviewwid[1],4,4,25,8);
//    gridlayout_right->addWidget(chartviewwid[2],4,0,25,8);
//    gridlayout_right->addWidget(chartviewwid[3],4,4,25,8);


}
void MainWidget::led_change(int id, bool iflag)
{
//    qDebug()<<"id:"<<id<<"  iflag:"<<iflag<<endl;
    ledwidget[id]->LedChange(iflag);
}

void MainWidget::voltage_change(int numa,int numb,int numc,int numd,int nume,int numf,int numg,int numh)
{
    // qDebug()<<"接收到的电压："<<numa<<endl
    //     <<numb<<endl
    //     <<numc<<endl
    //     <<numd<<endl
    //      <<nume<<endl
    //      <<numf<<endl;
    if(numa!=5) textwidget[0]->SetValue(numa);
    if(numb!=5) textwidget[1]->SetValue(numb);
    if(numc!=5) textwidget[2]->SetValue(numc);
    if(numd!=5) textwidget[3]->SetValue(numd);
    if(nume!=5) textwidget[4]->SetValue(nume);
    if(numf!=5) textwidget[5]->SetValue(numf);
    if(numg!=5) textwidget[6]->SetValue(numg);
    if(numh!=5) textwidget[7]->SetValue(numh);
}

void MainWidget::speed_change(int numa,int numb,int numc/*,int numd,int nume,int numf,int numg*/)
{
    // qDebug()<<"接收到的电压："<<numa<<endl
    //     <<numb<<endl
    //     <<numc<<endl
    //     <<numd<<endl
    //      <<nume<<endl
    //      <<numf<<endl;
    if(numa!=5) textwidget[8]->SetValue(numa);
    if(numb!=5) textwidget[9]->SetValue(numb);
    if(numc!=5) textwidget[10]->SetValue(numc);
    // if(numd!=5) textwidget[9]->SetValue(numd);
    // if(nume!=5) textwidget[10]->SetValue(nume);
    // if(numf!=5) textwidget[11]->SetValue(numf);
    // if(numf!=5) textwidget[12]->SetValue(numg);
}

void MainWidget::electric_change(int numa,int numb,int numc,int numd,int nume,int numf,int numg,int numh/*,int numi,int numj,int numk,int numl*/)
{

    chartviewwid->ElectricChange( numa, numb, numc, numd, nume, numf, numg, numh/*, numi,numj,numk,numl*/);
//    chartviewwid[1]->ElectricChange(numb);
//    chartviewwid[2]->ElectricChange(numc);
//    chartviewwid[3]->ElectricChange(numd);
}
void MainWidget::ReInit()
{
    //新控制器上电前重新初始化准备
    //led灯状态重置
    for(int i= 0;i<16;++i)
    {
         ledwidget[i]->ReInit();
    }
    for(int j =0;j<11;j++)
    {
        textwidget[j]->ReInit();
    }
    chartviewwid->ReInit();

    m_totlenum = 0;
}
void MainWidget::Cal_TotleNum()
{
    m_buhege="当前未通过项目：";
    m_totlenum = 0;
    for(int i= 0;i<16;++i)
    {
         m_totlenum = ledwidget[i]->m_result + m_totlenum;
         if(ledwidget[i]->m_result == 0) m_buhege = m_buhege +" "+ ledwidget[i]->m_name;
    }
   for(int j =0;j<11;j++)
   {
        m_totlenum = textwidget[j]->m_hege + m_totlenum;
        if(textwidget[j]->m_hege == 0) m_buhege = m_buhege +" " + textwidget[j]->m_str_name;
   }
   for(int k =0;k<8;k++)
   {
       m_totlenum = chartviewwid->m_hegenum[k] + m_totlenum;
       if(chartviewwid->m_hegenum[k] == 0) m_buhege = m_buhege +" "+ "电磁阀" + QString::number(k+1);
   }

    send_TotleNum(m_totlenum);
    send_BuhegeXiangmu(m_buhege);
//    qDebug()<<"m_buhege:"<<m_buhege<<endl;
}



