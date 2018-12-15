#include "mainwindow.h"
#include "dialog.h"
#include "edit.h"
#include "file.h"
#include "file/export.h"
#include "graphwidget.h"
#include "prop.h"
#include "sets.h"
#include "tools.h"
#include "tools/options.h"
#include "transform.h"
#include "view.h"

#include "base/globals.h"
#include "base/noxprotos.h"
#include "base/xprotos.h"

#include <errno.h>
#include <time.h>
#include <unistd.h>

#include <QApplication>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QTime>
#include <QToolBar>

class FixedAspectContainer : public QWidget {
public:
    FixedAspectContainer(QWidget *w) {
        widget = w;
        widget->setParent(this);
        widget->setGeometry(0, 0, 806, 606);
        this->setMinimumSize(806, 606);
    }

    virtual void resizeEvent(QResizeEvent *) {
        int contentsHeight = height();
        int contentsWidth = height() * (4.0 / 3.0);
        if (contentsWidth > width()) {
            contentsWidth = width();
            contentsHeight = width() * (3.0 / 4.0);
        }

        int xpos = (width() - contentsWidth) / 2;
        int ypos = (height() - contentsHeight) / 2;

        widget->setGeometry(xpos, ypos, contentsWidth, contentsHeight);
    }

private:
    QWidget *widget;
};

MainWindow::MainWindow() : QMainWindow(), settings("QTGR", "QTGR") {
    QWidget::setWindowIcon(QIcon(":images/icon.png"));

    startuptime = QTime::currentTime();
    setLastDirectory(QDir::current());
    clearFile();

    gwidget = new GraphWidget(this);
    gwidget->setMouseTracking(true);
    gwidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gwidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setCentralWidget(new FixedAspectContainer(gwidget));

    bool autoup = settings.value("auto_update", QVariant(true)).toBool();
    Dialog::setAutoUpdate(autoup);

    createMenus();
#if QT_VERSION >= 0x040300
    setUnifiedTitleAndToolBarOnMac(true);
#endif

    // finalize window
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);

    //
    // Name behavior: The document name is set on:
    // - loading a dataset or graph in the unnamed state
    // - saving to a .gr file
    // and reset when
    // - clearing all
    // - program start
    //
    // The name is hinted for saving & exporting
    //

    this->statusBar()->showMessage(tr("Ready"));
}

MainWindow::~MainWindow() { delete gwidget; }

void MainWindow::about() {
    QMessageBox::about(this, tr("About Application"),
                       tr("QTGR is a port to QT of the graphing program XVGR.\n"
                          "Formula transformation format is complicated:\n"
                          "x = (index < 10)*y + (index >= 10)*(- x*x)"));
}

void MainWindow::closeEvent(QCloseEvent *event) {
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    event->accept();
}

void MainWindow::createMenus() {
    fileMenu = new FileMenu(this);
    editMenu = new EditMenu(this);
    transformMenu = new TransformMenu(this);
    viewMenu = new ViewMenu(this);
    toolsMenu = new ToolsMenu(this);
    setMenu = new SetsMenu(this);

    // Something feels off with the order and naming of these menus...
    QMenuBar *mb = this->menuBar();
    mb->addMenu(fileMenu);
    mb->addSeparator();
    mb->addMenu(viewMenu);
    mb->addSeparator();
    mb->addMenu(editMenu);
    mb->addMenu(setMenu);
    mb->addMenu(transformMenu);
    mb->addSeparator();
    mb->addMenu(toolsMenu);
    mb->addSeparator();
    createHelpMenu();

    // for some odd reason, these must be added _after_ the menus
    addToolBarBreak(Qt::TopToolBarArea);
    addToolBarBreak(Qt::LeftToolBarArea);
    addToolBarBreak(Qt::RightToolBarArea);
    addToolBarBreak(Qt::BottomToolBarArea);

    addToolBar(toolsMenu, true);
    addToolBar(viewMenu, true);
    addToolBar(fileMenu, false);
    addToolBar(editMenu, false);
    addToolBar(setMenu, false);
    addToolBar(transformMenu, false);
}

void MainWindow::addToolBar(Menu *m, bool showdef) {
    bool visible =
        settings.value(QString("TB-") + m->title(), showdef).toBool();
    QToolBar *t = m->createToolBar(visible);
    connect(t, SIGNAL(visibilityChanged(bool)), this,
            SLOT(writeToolBarSettings(bool)));
    QMainWindow::addToolBar(Qt::TopToolBarArea, t);
}

void MainWindow::writeToolBarSettings(bool on) {
    QToolBar *changed = (QToolBar *)QObject::sender();
    settings.setValue(QString("TB-") + changed->windowTitle(), on);
}

void MainWindow::createHelpMenu() {
    QAction *aboutAct = new QAction(tr("About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    QAction *aboutQtAct = new QAction(tr("About Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), QApplication::instance(),
            SLOT(aboutQt()));

    helpMenu = this->menuBar()->addMenu(tr("&Help"));
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::dropEvent(QDropEvent *) { printf("We got a drop!\n"); }

void MainWindow::initialize() {
    QTime showtime = QTime::currentTime();

    this->show();

    // Load and render *after* window is up
    // initialize graphics
    inwin = TRUE;
    //    set_default_graph(0);
    set_graph_active(0);
    drawgraph();

    QStringList arguments = QCoreApplication::arguments();
    if (arguments.size() >= 2) {
        // TODO: make SET_NXY autodetect other modes if need be
        int type = SET_NXY;

        for (int i = 1; i < arguments.size(); i++) {
            QFileInfo info(arguments[i]);
            setFile(info.absoluteDir().path(), info.fileName());
            QByteArray v = arguments[i].toUtf8();
            getdata(0, v.data(), SOURCE_DISK, type);
        }

        if (ToolsOptions::isRescaleOnLoad()) {
            this->toolsMenu->autoScale();
        } else {
            drawgraph();
        }
    } else if (!isatty(fileno(stdin))) {
        qDebug("trying to read from stdin pipe: err: %d (%d is ENOTTY)", errno,
               ENOTTY);
        // TODO: figure out how to thread-decouple
        // base (graph, input) processes from UI. (if the program
        // is fed an empty pipe, it hangs.)
        getdata(cg, (char *)"STDIN", SOURCE_STDIN, SET_NXY);
        if (ToolsOptions::isRescaleOnLoad()) {
            this->toolsMenu->autoScale();
        } else {
            drawgraph();
        }
        qDebug("done reading");
    }

    QTime gotime = QTime::currentTime();

    printf("QTGR. Visible at: %d msec ; Ready at: %d msec \n",
           startuptime.msecsTo(showtime), startuptime.msecsTo(gotime));
}

void MainWindow::setFile(QString dir, QString name) {
    fDir = QDir(dir).absolutePath();
    fName = QDir(name).dirName();
    this->setWindowTitle(shortFileName() + " - " + tr("QTGR"));
}

QString MainWindow::fullFileName() {
    if (fName.isEmpty()) {
        return QString();
    }
    return fDir + QDir::separator() + fName;
}

QString MainWindow::fileName() { return fName; }

QString MainWindow::shortFileName() {
    if (fName.isEmpty()) {
        return QString();
    }

    int split = fName.lastIndexOf(".");
    return fName.left(split);
}

QString MainWindow::fileDirectory() { return fDir; }

bool MainWindow::hasFile() { return !fName.isEmpty(); }

void MainWindow::clearFile() {
    fName = QString();
    this->setWindowTitle(tr("QTGR"));
}

void MainWindow::setLastDirectory(QDir dir) { lastDir = dir; }

QDir MainWindow::lastDirectory() { return lastDir; }
