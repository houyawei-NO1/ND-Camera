#ifndef NANDUWIDGET_H
#define NANDUWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>
#include <QStackedWidget>
#include <QDir>
#include <QProcess>
// #include <QSoundEffect>
#include <QSound>
//#include <Windows.h>
#include "menubarwid.h"
#include "ndmassegebox.h"
#include "ctipareawid.h"
#include "cstatewid.h"
#include "cameraeidget.h"

class NanDuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NanDuWidget(QWidget *parent = nullptr);
    ~NanDuWidget();
    void setupUi();
    void Reset();
    void reboot();
    // QSoundEffect effect;

private:
    QWidget *widget=new QWidget(this);
    QGridLayout *gLayout;
    QVBoxLayout *vLayout[12];
    QLabel *pStatus[12];
    QLabel *tName[12];
    MenuBarWid* m_pMenuBar;
    ndmassegebox *m_ndMsgBox;
    QWidget *m_Darkwidge;
    CTipAreaWid *m_pTipAreaWid;
    CStateWid *m_pStateAreawid;
    QStackedWidget *m_StackedWidget;
    cameraeidget *camera;


signals:

public slots:
    void SelectButton(int);
    void click_on_Max();
    void click_on_Min();
    void click_on_closeall();
    void CloseSoft();
    void click_on_msgok(int);
    void click_on_msgcancel();

};

#endif // NANDUWIDGET_H
