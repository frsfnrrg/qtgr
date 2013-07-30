#include <QApplication>
#include "mainwindow.h"

#define MAIN
#include "base/globals.h"

int main(int argc, char *argv[])
{
    set_program_defaults();  
    Q_INIT_RESOURCE(qtgr);
    QApplication app(argc, argv);
    app.setOrganizationName("QTGR");
    app.setApplicationName("QTGR");
    app.setApplicationVersion("0.1.0");
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
