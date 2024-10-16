#include "cameraeidget.h"

cameraeidget::cameraeidget(QWidget *parent) :
    QWidget(parent),
    m_isStarted(false),
    m_camera(NULL)
{

    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color:black;");//rgb(28,32,48)
    this->setWindowFlags(Qt::FramelessWindowHint);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    currentScreenWid = (screenRect.width());
    currentScreenHei = (screenRect.height() - 100);
    this->setFixedSize(currentScreenWid,currentScreenHei);

    init();
    selectDevice(QCameraInfo::defaultCamera());
    start();

    //拍照
    connect(m_paizhao_button,&QPushButton::clicked,this,[ = ]{
     qDebug() <<m_camera->status();
    imageCapture->capture();
    });
    //分辨率
    connect(imageResolutionBox,&QComboBox::currentTextChanged,this,[ = ]{
        QCameraViewfinderSettings set;
        QSize fbl = imageResolutionBox->itemData(imageResolutionBox->currentIndex()).toSize();
        set.setResolution(fbl);
        qDebug()<<fbl;
        m_camera->setViewfinderSettings(set);
    });
    //图片格式
    connect(imageCodecBox,&QComboBox::currentTextChanged,this,[ = ]{

        QImageEncoderSettings settings = imageCapture->encodingSettings();
        qDebug()<<"setting"<<settings.codec();
        settings.setCodec(imageCodecBox->itemData(imageCodecBox->currentIndex()).toString());
        qDebug()<<"setting"<<settings.codec();
        imageCapture->setEncodingSettings(settings);
        imageCapture->capture();
    });


}
cameraeidget::~cameraeidget()
{
    delete m_camera;
}

void cameraeidget::selectDevice(const QCameraInfo &cameraInfo)
{
    bool restart = isStarted();
    if (isStarted()) {
        stop();
    }

    if (m_camera) {
        delete m_camera;
    }

    m_curCameraInfo = cameraInfo;
    m_camera = new QCamera(m_curCameraInfo);
    m_camera->setViewfinder(m_viewfinder);


    if (restart)//首次启动没有重连
        start();
}
bool cameraeidget::start()
{
    if (! m_isStarted) {
        m_isStarted = true;

        m_camera->start();

        // QList<QCameraInfo> curCameraInfoList = QCameraInfo::availableCameras();
        // for (int i = 0; i < curCameraInfoList.count(); i++) {
        //     qDebug() << "连接相机数量："<< curCameraInfoList.count();
        //     qDebug() << "相机名称："<< curCameraInfoList.at(i).deviceName();
        // }

        imageCapture = new QCameraImageCapture(m_camera);
        const QStringList supportedImageCodecs = imageCapture->supportedImageCodecs();
        for (const QString &codecName : supportedImageCodecs) {
            QString description = imageCapture->imageCodecDescription(codecName);
            imageCodecBox->addItem(codecName , QVariant(codecName));
             qDebug() << "支持编码格式："<< QVariant(codecName)<<"description"<<description;
        }


        QCameraViewfinderSettings set;
        set.setResolution(1920,1080);
        m_camera->setViewfinderSettings(set);
        qDebug() <<m_camera->status();
        // m_camera->setCaptureMode(QCamera::CaptureStillImage);

        const QList<QSize> supportedResolutions = imageCapture->supportedResolutions();
        for (const QSize &resolution : supportedResolutions) {
            imageResolutionBox->addItem(QString("%1x%2").arg(resolution.width()).arg(resolution.height()),
                                            QVariant(resolution));
            // qDebug() << "支持分辨率："<<QString("%1x%2").arg(resolution.width()).arg(resolution.height())<<endl;
        }

        if (imageCapture->isReadyForCapture()) {
            imageCapture->capture();
        } else {
            qWarning() << "Camera not ready for capture";
        }

    }

    emit send_status(m_isStarted);
    return true;
}

bool cameraeidget::stop()
{
    if (m_isStarted) {
        m_isStarted = false;

        m_camera->stop();
    }

    return true;
}

bool cameraeidget::isStarted()
{
    return m_isStarted;
}

void cameraeidget::init()
{
    auto mainLayout = new QHBoxLayout(this);
    m_viewfinder = new QCameraViewfinder(this);
    m_viewfinder->setStyleSheet("border-radius: 20px;background-color:rgb(43,48,70)");
    mainLayout->addWidget(m_viewfinder,8);

    auto operatelLayout = new QVBoxLayout(this);
    QWidget* black1 = new QWidget(this);
    black1->setStyleSheet("border-radius: 20px;background-color:rgb(black)");
    QWidget* caozuo = new QWidget(this);
    caozuo->setStyleSheet("border-radius: 20px;background-color:rgb(43,48,70)");
    auto caozuolayout = new QVBoxLayout(caozuo);
    auto paizhao_button_layout = new QHBoxLayout();
    auto paizhao_line1_layout = new QHBoxLayout();
    auto paizhao_line2_layout = new QHBoxLayout();
    auto paizhao_line3_layout = new QHBoxLayout();

    m_paizhao_button = new QPushButton(caozuo);
    m_paizhao_button->setFixedSize(200,200);
    m_paizhao_button->setText("拍照");
    m_paizhao_button->setStyleSheet("QPushButton:hover{border-radius:100px;background-color:rgb(67,207,124);color:rgb(255,245,238);font:80px;}\
                        QPushButton:pressed{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:80px;}\
                        QPushButton{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:80px;}");
    m_paizhao_button->setFocusPolicy(Qt::NoFocus);
    paizhao_button_layout->addStretch();
    paizhao_button_layout->addWidget(m_paizhao_button);
    paizhao_button_layout->addStretch();

    QLabel* String1 = new QLabel();
    String1->setText("①二维码ID:");
    String1->setStyleSheet("color:rgb(255,245,238);font:25px");
    QLineEdit* lineedit1 = new QLineEdit();
    lineedit1->setStyleSheet("color:rgb(43,48,70);font:25px;background-color:rgb(255,245,238)");
    paizhao_line1_layout->addWidget(String1);
    paizhao_line1_layout->addWidget(lineedit1);

    QLabel* String2 = new QLabel();
    String2->setText("②本地保存:");
    String2->setStyleSheet("color:rgb(255,245,238);font:25px");
    QCheckBox* bendi = new QCheckBox();
    bendi->setStyleSheet("QCheckBox{ background-color: rgb(255,245,238);color: #1a67c0;border-radius: 0px;}\
                         QCheckBox::indicator {width: 30px; height: 30px; }");
    bendi->setChecked(true);
    paizhao_line2_layout->addWidget(String2);
    paizhao_line2_layout->addStretch();
    paizhao_line2_layout->addWidget(bendi);
    paizhao_line2_layout->addStretch();

    QLabel* String3 = new QLabel();
    String3->setText("③服务器:");
    String3->setStyleSheet("color:rgb(255,245,238);font:25px");
    QCheckBox* fuwuqi = new QCheckBox();
    fuwuqi->setStyleSheet("QCheckBox{ background-color: rgb(255,245,238);color: #1a67c0;border-radius: 0px;}\
                         QCheckBox::indicator {width: 30px; height: 30px; }");
    paizhao_line3_layout->addWidget(String3);
    paizhao_line3_layout->addStretch();
    paizhao_line3_layout->addWidget(fuwuqi);
    paizhao_line3_layout->addStretch();


    caozuolayout->addLayout(paizhao_button_layout);
    caozuolayout->addLayout(paizhao_line1_layout);
    caozuolayout->addLayout(paizhao_line2_layout);
    caozuolayout->addLayout(paizhao_line3_layout);

    QWidget* black2 = new QWidget(this);
    black2->setStyleSheet("border-radius: 20px;background-color:rgb(black)");
    QWidget* peizhi = new QWidget(this);
    peizhi->setStyleSheet("border-radius: 20px;background-color:rgb(43,48,70)");
    QWidget* black3 = new QWidget(this);
    black3->setStyleSheet("border-radius: 20px;background-color:rgb(black)");

    auto peizhilayout = new QVBoxLayout(peizhi);
    auto peizhi_line1_layout = new QHBoxLayout();//配置区，重连按键
    auto peizhi_line2_layout = new QHBoxLayout();//目录
    auto peizhi_line3_layout = new QHBoxLayout();//工序
    auto peizhi_line4_layout = new QHBoxLayout();//格式
    auto peizhi_line5_layout = new QHBoxLayout();//分辨率

    QLabel* String4 = new QLabel();
    String4->setText("配置区");
    String4->setStyleSheet("color:rgb(255,245,238);font:25px");
    m_reconnect_button = new QPushButton(peizhi);
    m_reconnect_button->setFixedSize(150,30);
    m_reconnect_button->setText("重连相机");
    m_reconnect_button->setStyleSheet("QPushButton:hover{border-radius:100px;background-color:rgb(67,207,124);color:rgb(255,245,238);font:25px;}\
                                    QPushButton:pressed{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}\
                                    QPushButton{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}");
    m_reconnect_button->setFocusPolicy(Qt::NoFocus);
    peizhi_line1_layout->addWidget(String4);
    peizhi_line1_layout->addWidget(m_reconnect_button);

    QLabel* String5 = new QLabel();
    String5->setText("①目录:");
    String5->setStyleSheet("color:rgb(255,245,238);font:25px");
    QLineEdit* lineedit2 = new QLineEdit();
    lineedit2->setStyleSheet("color:rgb(43,48,70);font:25px;background-color:rgb(255,245,238)");
    m_filelocation_button = new QPushButton(peizhi);
    m_filelocation_button->setFixedSize(50,30);
    m_filelocation_button->setText("选择");
    m_filelocation_button->setStyleSheet("QPushButton:hover{border-radius:100px;background-color:rgb(67,207,124);color:rgb(255,245,238);font:25px;}\
                                    QPushButton:pressed{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}\
                                    QPushButton{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}");
    m_filelocation_button->setFocusPolicy(Qt::NoFocus);
    peizhi_line2_layout->addWidget(String5);
    peizhi_line2_layout->addWidget(lineedit2);
    peizhi_line2_layout->addWidget(m_filelocation_button);

    QLabel* String6 = new QLabel();
    String6->setText("②工序:");
    String6->setStyleSheet("color:rgb(255,245,238);font:25px");
    m_gongxu = new QComboBox(peizhi);
    m_gongxu->addItem("贴片");
    m_gongxu->addItem("三防");
    m_gongxu->addItem("PCBA打胶");
    m_gongxu->addItem("壳体打胶");
    m_gongxu->setStyleSheet("QComboBox{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}");
    peizhi_line3_layout->addWidget(String6);
    peizhi_line3_layout->addWidget(m_gongxu);

    QLabel* String7 = new QLabel();
    String7->setText("③格式:");
    String7->setStyleSheet("color:rgb(255,245,238);font:25px");
    imageCodecBox = new QComboBox(peizhi);
    imageCodecBox->addItem(tr("默认"), QVariant(QString()));
    imageCodecBox->setStyleSheet("QComboBox{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}");
    peizhi_line4_layout->addWidget(String7);
    peizhi_line4_layout->addWidget(imageCodecBox);

    QLabel* String8 = new QLabel();
    String8->setText("④分辨率:");
    String8->setStyleSheet("color:rgb(255,245,238);font:25px");
    imageResolutionBox = new QComboBox(peizhi);
    imageResolutionBox->addItem(tr("1920x1080"));
    imageResolutionBox->setStyleSheet("QComboBox{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}");
    peizhi_line5_layout->addWidget(String8);
    peizhi_line5_layout->addWidget(imageResolutionBox);

    peizhilayout->addLayout(peizhi_line1_layout);
    peizhilayout->addLayout(peizhi_line2_layout);
    peizhilayout->addLayout(peizhi_line3_layout);
    peizhilayout->addLayout(peizhi_line4_layout);
    peizhilayout->addLayout(peizhi_line5_layout);

    operatelLayout->addWidget(black1,2);
    operatelLayout->addWidget(caozuo,20);
    operatelLayout->addWidget(black2,1);
    operatelLayout->addWidget(peizhi,20);
    operatelLayout->addWidget(black3,2);

    mainLayout->addLayout(operatelLayout,2);

}


