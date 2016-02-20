#include "mainwindow.h"

#define MAIN
#include "base/globals.h"

#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{

    set_program_defaults();  
    Q_INIT_RESOURCE(qtgr);

    QApplication app(argc, argv);
    app.setOrganizationName("QTGR");
    app.setApplicationName("QTGR");
#if QT_VERSION >= 0x040400
    app.setApplicationVersion("0.1.2");
#endif

    MainWindow mainWin;

    // make sure that event loop is started before parsing command line
    QTimer::singleShot(0, &mainWin, SLOT(initialize()));

    return app.exec();
}
