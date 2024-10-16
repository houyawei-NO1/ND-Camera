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

class cameraeidget : public QWidget
{
    Q_OBJECT
public:
     // cameraeidget(QVideoWidget *widget);
     explicit cameraeidget(QWidget *parent = nullptr);
     ~cameraeidget();

     bool start();
     bool stop();
     bool isStarted();
     void selectDevice(const QCameraInfo &cameraInfo);

     void init();

     int currentScreenWid;//整个主部件区域大小
     int currentScreenHei;//整个主部件区域大小

signals:
     void send_status(bool);
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
};

#endif // CAMERAEIDGET_H
