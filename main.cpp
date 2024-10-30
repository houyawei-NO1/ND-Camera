#include "nanduwidget.h"
#include <QApplication>
#include "cameraeidget.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);
    a.setStyle("fusion");

     NanDuWidget Widget;
     Widget.show();

    return a.exec();
}

