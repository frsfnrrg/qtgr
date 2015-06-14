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
    app.setApplicationVersion("0.1.1");

    MainWindow mainWin;

    // make sure that event loop is started before parsing command line
    QTimer::singleShot(0, &mainWin, SLOT(initialize()));

    mainWin.show();
    return app.exec();
}
