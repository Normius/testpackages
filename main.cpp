#include "packagemanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PackageManager pm;
    pm.resize(800, 600);
    pm.show();
    return a.exec();
}
