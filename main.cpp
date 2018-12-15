#include "file/export.h"
#include "graphwidget.h"
#include "mainwindow.h"

#define MAIN
#include "base/globals.h"
#include "base/noxprotos.h"

#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[]) {
    // Run underlying initialization
    set_program_defaults();
    initialize_cms_data();
    initialize_nonl();
    init_symtab();

    Q_INIT_RESOURCE(qtgr);

    QApplication app(argc, argv);
    app.setOrganizationName("QTGR");
    app.setApplicationName("QTGR");
#if QT_VERSION >= 0x040400
    app.setApplicationVersion("0.1.2");
#endif

    QStringList arguments = QCoreApplication::arguments();
    // Now you can parse the arguments *after* the main window has been created.

    // Either run in export mode
    if (arguments.size() == 2 && arguments[1] == "--help") {
        printf("Usage: qtgr [--help] [--pdf] [--png] [--jpg] file.xvgr ...\n");
        return 0;
    } else if (arguments.size() >= 3 &&
               (arguments[1] == "--pdf" || arguments[1] == "--png" ||
                arguments[1] == "--jpg")) {
        for (int i = 2; i < arguments.size(); i++) {
            QString filename = arguments[i];
            QFileInfo info(filename);
            QByteArray v = filename.toUtf8();

            GraphWidget gwidget(NULL);
            // initialize grapics
            inwin = TRUE;
            //    set_default_graph(0);
            set_graph_active(0);
            drawgraph();

            // Clear, then load
            wipeout(0);
            set_graph_active(0);
            int retval = getdata(0, v.data(), SOURCE_DISK, SET_NXY);
            if (!retval) {
                // Don't bother if acquisition fails
                qDebug("Failed to load: %s",
                       info.canonicalFilePath().toUtf8().constData());
                continue;
            }
            drawgraph();

            QString target = info.canonicalFilePath();
            QString origtype = info.suffix();
            FileExport::ImageType type;
            // Need a dedicate mode changer
            if (target.right(origtype.length()) == origtype) {
                target = target.left(target.length() - origtype.length() - 1);
            }

            if (arguments[1] == "--pdf") {
                type = FileExport::PDF;
                target += ".pdf";
            } else if (arguments[1] == "--png") {
                type = FileExport::PNG;
                target += ".png";
            } else if (arguments[1] == "--jpg") {
                type = FileExport::JPG;
                target += ".jpg";
            }
            FileExport::exportImage(type, target, gwidget.scene(), 2400, 1800);
        }
        return 0;
    } else {
        MainWindow mainWin;

        // make sure that event loop is started before parsing command line
        QTimer::singleShot(0, &mainWin, SLOT(initialize()));

        return app.exec();
    }
}
