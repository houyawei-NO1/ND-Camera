#ifndef CAMERAEIDGET_H
#define CAMERAEIDGET_H

#include <QCamera>
#include <QCameraInfo>
#include <QVideoWidget>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QCameraViewfinderSettings>
#include <QDir>
#include <QFileDialog>
#include <QTimer>
class cameraeidget : public QWidget
{
    Q_OBJECT
public:
     // cameraeidget(QVideoWidget *widget);
     explicit cameraeidget(QWidget *parent = nullptr);
     ~cameraeidget();

     void start();
     bool stop();
     bool isStarted();
     void selectDevice(const QCameraInfo &cameraInfo);

     void init();

     int currentScreenWid;//整个主部件区域大小
     int currentScreenHei;//整个主部件区域大小

signals:
    void send_status(bool);
    void send_log(QString);

private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *operatelLayout;
    bool               m_isStarted;
    QCameraViewfinder *m_viewfinder;
    QCamera           *m_camera;
    QCameraInfo        m_curCameraInfo;
    QCameraImageCapture *imageCapture;
    QPushButton* m_paizhao_button;
    QPushButton* m_reconnect_button;
    QPushButton* m_filelocation_button;
    QComboBox *m_gongxu;
    QComboBox *imageCodecBox;
    QComboBox *imageResolutionBox;
    QLineEdit* lineedit1;
    QString localPath;
    QString localPathName;
    QLineEdit* lineedit2;
    QString str_gongxu;
    QString remotepath;
    QString remotepathname;
};

#endif // CAMERAEIDGET_H
