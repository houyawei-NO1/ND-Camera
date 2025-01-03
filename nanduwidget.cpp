#include "nanduwidget.h"

NanDuWidget::NanDuWidget(QWidget *parent) : QWidget(parent)
{

    setupUi();

    // effect.setSource(QUrl::fromLocalFile(":/sound/0.wav"));//开机
    // effect.setLoopCount(1);
    // effect.setVolume(1);
    // effect.play();

    QSound::play(":/sound/0.wav");


    // //功能状态
    // connect(w, SIGNAL(signal_send(int,bool)), mainwidget, SLOT(led_change(int,bool)),Qt::QueuedConnection);
    // connect(w, SIGNAL(voltage_send(int,int,int,int,int,int,int,int)), mainwidget, SLOT(voltage_change(int,int,int,int,int,int,int,int)),Qt::QueuedConnection);
    // connect(w, SIGNAL(speed_send(int,int,int)), mainwidget, SLOT(speed_change(int,int,int)),Qt::QueuedConnection);
    // connect(w, SIGNAL(electric_send(int,int,int,int,int,int,int,int)), mainwidget,
    //         SLOT(electric_change(int,int,int,int,int,int,int,int)),Qt::QueuedConnection);
    // connect(w,SIGNAL(UpdateUi()),mainwidget,SLOT(ReInit()),Qt::QueuedConnection);
    // //窗口部件计数
    // connect(mainwidget, SIGNAL(send_TotleNum(int)), m_pMenuBar, SLOT(rec_TotleNum(int)),Qt::QueuedConnection);
    // connect(w,SIGNAL(UpdateUi()),m_pMenuBar,SLOT(ReInit()),Qt::QueuedConnection);
    //菜单栏
    connect(m_pMenuBar,SIGNAL(CurSelectPage(int)), this, SLOT(SelectButton(int)),Qt::QueuedConnection);
    connect(m_pMenuBar, SIGNAL(showMax()), this, SLOT(click_on_Max()),Qt::QueuedConnection);
    connect(m_pMenuBar, SIGNAL(showMin()), this, SLOT(click_on_Min()),Qt::QueuedConnection);
    connect(m_pMenuBar, SIGNAL(closeWidget()), this, SLOT(click_on_closeall()),Qt::QueuedConnection);
    //弹窗
    connect(m_ndMsgBox,SIGNAL(Clicked_btn_OK(int)),this,SLOT(click_on_msgok(int)),Qt::QueuedConnection);
    connect(m_ndMsgBox,SIGNAL(Clicked_btn_Cancel()),this,SLOT(click_on_msgcancel()),Qt::QueuedConnection);
    //状态栏
    // connect(w, SIGNAL(status_send(bool,bool,bool)), m_pStateAreawid, SLOT(status_slot(bool,bool,bool)),Qt::QueuedConnection);
    // connect(w, SIGNAL(DataRec_sta()), m_pStateAreawid, SLOT(DataRec_slot()),Qt::QueuedConnection);


    //相机状态
    connect(camera,SIGNAL(send_status(bool)),m_pStateAreawid, SLOT(status_slot(bool)),Qt::QueuedConnection);

    //log打印
    connect(camera,SIGNAL(send_log(QString)),m_pTipAreaWid, SLOT(slotStatusNotify(QString)),Qt::QueuedConnection);

}
void NanDuWidget::setupUi()
{
    setAttribute(Qt::WA_StaticContents);
    setWindowTitle("南都拍照系统--南都汽车电子");
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/image/logo"));

    QDesktopWidget *desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    int currentScreenWid = screenRect.width();
    int currentScreenHei = screenRect.height();
    this->resize(currentScreenWid,currentScreenHei);

    QVBoxLayout *pMainLayOut = new QVBoxLayout(this);

    QVBoxLayout *pVSubLayOut = new QVBoxLayout();
    pVSubLayOut->setSpacing(0); //控件之间的边距
    m_pMenuBar = new MenuBarWid(this);

    m_StackedWidget = new QStackedWidget(this);
    // mainwidget = new MainWidget(this);
    camera = new cameraeidget(this);
    m_StackedWidget->addWidget(camera);
    // m_StackedWidget->addWidget(w);

   pVSubLayOut->addWidget(m_pMenuBar);
   pVSubLayOut->addWidget(m_StackedWidget);
   pVSubLayOut->setSpacing(0);

    QWidget* widbottom = new QWidget(this);
    widbottom->setStyleSheet("background-color:rgb(28,32,48)");

    QHBoxLayout *pLayOut_Bottom = new QHBoxLayout(widbottom);
    m_pTipAreaWid = new CTipAreaWid(this);
    m_pStateAreawid = new CStateWid(this);
    pLayOut_Bottom->addWidget(m_pTipAreaWid,5);
    pLayOut_Bottom->addWidget(m_pStateAreawid,5);
    pLayOut_Bottom->setSpacing(0);
    pLayOut_Bottom->setContentsMargins(0,0,0,0);

    pMainLayOut->addLayout(pVSubLayOut);
    pMainLayOut->addWidget(widbottom,0,Qt::AlignBottom);
    pMainLayOut->setContentsMargins(0,0,0,0);
    pMainLayOut->setSpacing(0); //控件之间的边距
    pMainLayOut->setMargin(0);

    m_ndMsgBox = new ndmassegebox(this);
    m_ndMsgBox->setGeometry((currentScreenWid-460)/2,(currentScreenHei-260)/2,460,260);
    m_ndMsgBox->setVisible(false);
    m_Darkwidge = new QWidget(this);
    m_Darkwidge->resize (currentScreenWid, currentScreenHei);
    m_Darkwidge->move (0,0);
    QPalette pal(m_Darkwidge->palette());
    m_Darkwidge->setStyleSheet("background-color:rgba(0, 0, 0, 70%);border-radius: 20px;");//透明如果主界面是圆角就要圆角
    m_Darkwidge->setAutoFillBackground(true);
    m_Darkwidge->setPalette(pal);
    m_Darkwidge->hide();
}

NanDuWidget::~NanDuWidget()
{
   delete camera;//与关闭按钮重复
}

void NanDuWidget::SelectButton(int iCurSelectNum)
{

    int iturnNum = 0;
    if(iCurSelectNum < 1)
        iturnNum = iCurSelectNum;
    else
        iturnNum = 0;

    m_StackedWidget->setCurrentIndex(iturnNum);
//    if(iCurSelectNum==1)
//    {

////        w->show();
////        m_StackedWidget->setCurrentIndex(1);

//    }

    if(iCurSelectNum == 1)
    {

        //弹框提示重启
        m_Darkwidge->show();
        m_ndMsgBox->setVisible(true);
        m_ndMsgBox->setType(0);
        m_ndMsgBox->setLabelText(tr("重启提醒"),tr("是否确认重启设备？"));
    }

    if(iCurSelectNum == 2)
    {
        //弹框提示关机
        m_Darkwidge->show();
        m_ndMsgBox->setVisible(true);
        m_ndMsgBox->setType(1);
        m_ndMsgBox->setLabelText(tr("关机提醒"),tr("是否确认关机？"));
    }

    if(iCurSelectNum == 3)
    {
        //关于弹框
        m_Darkwidge->show();
        m_ndMsgBox->setVisible(true);
        m_ndMsgBox->setType(2);
        m_ndMsgBox->setLabelText(tr("南都拍照系统"),tr("河南南都汽车电子有限公司\n"
                                                        "南都拍照系统\n"
                                                        "河南省南阳市卧龙区王村乡淯龙光电产业园\n"
                                                        "标准化厂房8号楼4层\n\n"
                                                        "侯亚威 18337356560\n"
                                                        "QT 5.15.2"));
    }


}
void NanDuWidget::click_on_closeall()
{
     delete camera;
     close();
}
void NanDuWidget::click_on_Max()
{
    this->showFullScreen();
}
void NanDuWidget::click_on_Min()
{
    this->showMinimized();
}
void NanDuWidget::CloseSoft()
{
    delete camera;
    close();
}
void NanDuWidget::click_on_msgok(int msgtype)
{
    m_Darkwidge->hide();

    if(msgtype == 0)
    {
        //重启操作
//        this->reboot();
        system("shutdown -r -t 00");
    }
    else if(msgtype == 1)
    {
        //关机
        m_pMenuBar->setFirBtnChecked();
        system("shutdown -s -t 00");
    }

    else
        ;

    //this->showFullScreen();
}
void NanDuWidget::click_on_msgcancel()
{
    m_Darkwidge->hide();
    m_pMenuBar->setFirBtnChecked();

    //this->showFullScreen();
}

void NanDuWidget::reboot()
{
    QString program = QApplication::applicationFilePath();
    QStringList arguments = QApplication::arguments();
    QString workingDirectory = QDir::currentPath();
    QProcess::startDetached(program, arguments, workingDirectory);
    QApplication::exit();
}
