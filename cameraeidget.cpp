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
    //默认
    str_gongxu=m_gongxu->currentText();
    remotepath="//Houyawei-pc/服务器/拍照系统/";

    //拍照
    connect(m_paizhao_button,&QPushButton::clicked,this,[ = ]{
    str_gongxu=m_gongxu->currentText();
    QString dir = localPath + str_gongxu;
    QDir mDir;
    if(!mDir.exists(dir))
    {
        mDir.mkpath(dir);
    }
    QString remotedir = remotepath + str_gongxu;
    QDir mrDir;
    if(!mrDir.exists(remotedir))
    {
        mrDir.mkpath(remotedir);
    }
    localPathName = dir +"/"+ lineedit1->text();
    remotepathname = remotedir +"/" + lineedit1->text();
    qDebug()<<localPathName<<endl;
    qDebug()<<remotepathname<<endl;
    if (imageCapture->isReadyForCapture()) {
        imageCapture->capture(localPathName);
        emit send_log("拍照成功,保存至路径："+localPathName+"."+imageCodecBox->currentText());
        QTimer::singleShot(0.5 * 1000,this,[=]{
            imageCapture->capture(remotepathname);
             // emit send_log("延时拍照至服务器,保存至路径："+remotepathname);
        });
    } else {
        emit send_log("拍照失败,相机没有准备好");
    }

    lineedit1->clear();
    activateWindow();
    lineedit1->setFocus();
    emit send_status(m_isStarted);
    });

    //识别
    connect(m_shibie_button,&QPushButton::clicked,this,[ = ]{

    if (imageCapture->isReadyForCapture()) {
        imageCapture->capture("D:/cache.jpg");
        emit send_log("拍照成功,保存至路径：D:/cache.jpg");

        QTimer::singleShot(2 * 1000,this,[=]{
        QZXing decoder;
        QImage imageToDecode("D:/cache.jpg");
        decoder.setDecoder(QZXing::DecoderFormat_QR_CODE );
        // decoder.setTryHarderBehaviour(QZXing::TryHarderBehaviour_ThoroughScanning | QZXing::TryHarderBehaviour_Rotate);
        decoder.setSourceFilterType(QZXing::SourceFilter_ImageNormal| QZXing::SourceFilter_ImageInverted);
        QString result=decoder.decodeImage(imageToDecode);
        lineedit1->setText(result);
        if(result.isEmpty()) emit send_log("未识别到二维码");
        else emit send_log("二维码识别结果:"+result);
        });

    } else {
        emit send_log("识别失败,相机没有准备好");
    }

    });

    //清除ID
    connect(m_clean_button,&QPushButton::clicked,this,[ = ]{
        lineedit1->clear();
    });

    //A面
    connect(m_amian_button,&QPushButton::clicked,this,[ = ]{
        lineedit1->insert("A面");
    });

    //B面
    connect(m_bmian_button,&QPushButton::clicked,this,[ = ]{
        lineedit1->insert("B面");
    });

    //分辨率
    connect(imageResolutionBox,&QComboBox::currentTextChanged,this,[ = ]{
        QCameraViewfinderSettings set;
        QSize fbl = imageResolutionBox->itemData(imageResolutionBox->currentIndex()).toSize();
        set.setResolution(fbl);
        m_camera->setViewfinderSettings(set);
    });
    //图片格式
    connect(imageCodecBox,&QComboBox::currentTextChanged,this,[ = ]{

        QImageEncoderSettings settings = imageCapture->encodingSettings();
        settings.setCodec(imageCodecBox->currentText());
        imageCapture->setEncodingSettings(settings);
    });
    //工序选择
    connect(m_gongxu,&QComboBox::currentTextChanged,this,[ = ]{

        str_gongxu=m_gongxu->currentText();

    });

    //重连相机
    connect(m_reconnect_button,&QPushButton::clicked,this,[ = ]{

        selectDevice(QCameraInfo::defaultCamera());
        // start();
        lineedit1->clear();
        lineedit1->setFocus();

    });
    //下载路径选择按钮
    connect(m_filelocation_button, &QPushButton::clicked, this, [ = ] {
        QDir dir= QCoreApplication::applicationDirPath();
        dir.cdUp();
        localPath = dir.path();
        localPath = QFileDialog::getExistingDirectory(this, tr("选择下载路径"),
                                                     localPath,
                                                     QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
        lineedit2->setText(localPath);
    });
    //扫码枪输入自动对焦
    QTimer::singleShot(5 * 1000,this,[=]{
        activateWindow();
        lineedit1->setFocus();
        emit send_status(m_isStarted);
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
void cameraeidget::start()
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
        imageCodecBox->clear();
        for (const QString &codecName : supportedImageCodecs) {
            QString description = imageCapture->imageCodecDescription(codecName);
            imageCodecBox->addItem(codecName , QVariant(codecName));
             // qDebug() << "支持编码格式："<< QVariant(codecName)<<"description"<<description;
        }
        imageCodecBox->setCurrentIndex(5);

        QCameraViewfinderSettings set;
        set.setResolution(1920,1080);
        m_camera->setViewfinderSettings(set);
        qDebug() <<m_camera->status();
        // m_camera->setCaptureMode(QCamera::CaptureStillImage);

        imageResolutionBox->clear();
        const QList<QSize> supportedResolutions = imageCapture->supportedResolutions();
        for (const QSize &resolution : supportedResolutions) {
            imageResolutionBox->addItem(QString("%1x%2").arg(resolution.width()).arg(resolution.height()),
                                            QVariant(resolution));
            // qDebug() << "支持分辨率："<<QString("%1x%2").arg(resolution.width()).arg(resolution.height())<<endl;
        }
        imageResolutionBox->setCurrentIndex(2);

    }


    QTimer::singleShot(2 * 1000,this,[=]{
        emit send_status(m_isStarted);
    });

}

bool cameraeidget::stop()
{
    if (m_isStarted) {
        m_isStarted = false;

        m_camera->stop();
    }
    emit send_status(m_isStarted);
    return true;
}

bool cameraeidget::isStarted()
{
    return m_isStarted;
}

void cameraeidget::init()
{
    localPath="D:/";
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
    auto paizhao_line4_layout = new QHBoxLayout();

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

    QLabel *String1 = new QLabel();
    String1->setText("ID:");
    String1->setStyleSheet("color:rgb(255,245,238);font:25px");
    lineedit1 = new QLineEdit();
    lineedit1->setStyleSheet("color:rgb(43,48,70);font:25px;background-color:rgb(255,245,238)");
    m_clean_button = new QPushButton(this);
    m_clean_button->setFixedSize(30,30);
    m_clean_button->setText("X");
    m_clean_button->setStyleSheet("QPushButton:hover{border-radius:100px;background-color:rgb(67,207,124);color:rgb(255,245,238);font:25px;}\
                       QPushButton:pressed{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}\
                                     QPushButton{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}");
    m_clean_button->setFocusPolicy(Qt::NoFocus);
    paizhao_line1_layout->addWidget(String1);
    paizhao_line1_layout->addWidget(lineedit1);
    paizhao_line1_layout->addWidget(m_clean_button);

    QLabel* String2 = new QLabel();
    String2->setText("本地保存:");
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
    String3->setText("服务器:");
    String3->setStyleSheet("color:rgb(255,245,238);font:25px");
    QCheckBox* fuwuqi = new QCheckBox();
    fuwuqi->setStyleSheet("QCheckBox{ background-color: rgb(255,245,238);color: #1a67c0;border-radius: 0px;}\
                         QCheckBox::indicator {width: 30px; height: 30px; }");
    paizhao_line3_layout->addWidget(String3);
    paizhao_line3_layout->addStretch();
    paizhao_line3_layout->addWidget(fuwuqi);
    paizhao_line3_layout->addStretch();

    m_shibie_button = new QPushButton(this);
    m_shibie_button->setFixedSize(70,40);
    m_shibie_button->setText("识别");
    m_shibie_button->setStyleSheet("QPushButton:hover{border-radius:100px;background-color:rgb(67,207,124);color:rgb(255,245,238);font:25px;}\
                             QPushButton:pressed{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}\
                                           QPushButton{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}");
    m_shibie_button->setFocusPolicy(Qt::NoFocus);
    m_amian_button = new QPushButton(this);
    m_amian_button->setFixedSize(70,40);
    m_amian_button->setText("A面");
    m_amian_button->setStyleSheet("QPushButton:hover{border-radius:100px;background-color:rgb(67,207,124);color:rgb(255,245,238);font:25px;}\
                             QPushButton:pressed{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}\
                                           QPushButton{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}");
    m_amian_button->setFocusPolicy(Qt::NoFocus);
    m_bmian_button = new QPushButton(this);
    m_bmian_button->setFixedSize(70,40);
    m_bmian_button->setText("B面");
    m_bmian_button->setStyleSheet("QPushButton:hover{border-radius:100px;background-color:rgb(67,207,124);color:rgb(255,245,238);font:25px;}\
                             QPushButton:pressed{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}\
                                           QPushButton{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}");
    m_bmian_button->setFocusPolicy(Qt::NoFocus);
    paizhao_line4_layout->addWidget(m_shibie_button);
    paizhao_line4_layout->addWidget(m_amian_button);
    paizhao_line4_layout->addWidget(m_bmian_button);

    caozuolayout->addLayout(paizhao_button_layout);
    caozuolayout->addLayout(paizhao_line1_layout);
    caozuolayout->addLayout(paizhao_line2_layout);
    caozuolayout->addLayout(paizhao_line3_layout);
    caozuolayout->addLayout(paizhao_line4_layout);

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
    lineedit2 = new QLineEdit();
    lineedit2->setStyleSheet("color:rgb(43,48,70);font:25px;background-color:rgb(255,245,238)");
    lineedit2->setText(localPath);
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
    imageCodecBox->setStyleSheet("QComboBox{border-radius:100px;background-color:#1a67c0;color:rgb(255,245,238);font:25px;}");
    peizhi_line4_layout->addWidget(String7);
    peizhi_line4_layout->addWidget(imageCodecBox);

    QLabel* String8 = new QLabel();
    String8->setText("④分辨率:");
    String8->setStyleSheet("color:rgb(255,245,238);font:25px");
    imageResolutionBox = new QComboBox(peizhi);
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


