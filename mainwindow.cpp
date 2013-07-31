#include <QtGui>

#include "mainwindow.h"
#include "file.h"
#include "edit.h"
#include "view.h"
#include "tools.h"
#include "sets.h"
#include "transform.h"
#include "graphwidget.h"
#include "base/globals.h"
#include "prop.h"

QAction* createQAction(const QString &name, const QString &explained, const QString &shortcut, QObject* parent)
{
   QAction* f = new QAction(name, parent);
   f->setToolTip(explained);
   f->setStatusTip(explained);
   f->setWhatsThis(explained);
   f->setShortcut(QKeySequence(shortcut));
   f->setShortcutContext(Qt::ApplicationShortcut);
   return f;
}

MainWindow::MainWindow()
{
    this->setWindowTitle(tr("QTGR"));

    QGraphicsScene *scene = new GraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);
    scene->setBackgroundBrush(Qt::white);

    gwidget = new GraphWidget(scene,this);
    gwidget->setMouseTracking(true);
    gwidget->setMinimumWidth(806);
    gwidget->setMaximumWidth(806);
    gwidget->setMaximumHeight(606);
    gwidget->setMinimumHeight(606);

    setCentralWidget(gwidget);

    createMenus();

    readSettings();

    setUnifiedTitleAndToolBarOnMac(true);

    // initialize grapics
    inwin = TRUE;
    //    set_default_graph(0);
    set_graph_active(0);
    drawgraph();

    this->statusBar()->showMessage(tr("Ready"));
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("QTGR is a port to QT of the graphing program XVGR.\n"
               "Formula transformation format is complicated:\n"
               "x = (index < 10)*y + (index >= 10)*(- x*x)"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}


void MainWindow::createMenus()
{
    fileMenu = new FileMenu(this);
    editMenu = new EditMenu(this);
    transformMenu = new TransformMenu(this);
    viewMenu = new ViewMenu(this);
    toolsMenu = new ToolsMenu(this);
    setMenu = new SetsMenu(this);

    // Something feels off with the order and naming of these menus...
    QMenuBar* mb = this->menuBar();
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
    this->addToolBar(toolsMenu->createToolBar());
    this->addToolBar(viewMenu->createToolBar());
}


void MainWindow::createHelpMenu()
{
    QAction* aboutAct = new QAction(tr("About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    QAction* aboutQtAct = new QAction(tr("About Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    QAction* optionsAct = new QAction(tr("Options"), this);

    helpMenu = this->menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(optionsAct);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::readSettings()
{
    QSettings settings("QTGR", "QTGR");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings()
{
    QSettings settings("QTGR", "QTGR");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

void MainWindow::dropEvent(QDropEvent *) {
    printf("We got a drop!\n");
}
