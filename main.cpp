#include "nanduwidget.h"
#include <QApplication>
#include "cameraeidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");

     NanDuWidget Widget;
     Widget.show();

    return a.exec();
}

