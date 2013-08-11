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

MainWindow::MainWindow() :
    QMainWindow(),
    settings("QTGR","QTGR")
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

    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);

    createMenus();

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
    settings.setValue("pos", pos());
    settings.setValue("size", size());
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

    addToolBar(toolsMenu,true);
    addToolBar(viewMenu,true);
    addToolBar(fileMenu,false);
    addToolBar(editMenu,false);
    addToolBar(setMenu,false);
    addToolBar(transformMenu,false);
}

void MainWindow::addToolBar(Menu* m, bool showdef) {
    bool visible = settings.value(QString("TB-") + m->title(), showdef).toBool();
    QToolBar* t = m->createToolBar(visible);
    connect(t, SIGNAL(visibilityChanged(bool)), this, SLOT(writeToolBarSettings(bool)));
    QMainWindow::addToolBar(t);
}

void MainWindow::writeToolBarSettings(bool on) {
    QToolBar* changed = (QToolBar*)QObject::sender();
    settings.setValue(QString("TB-") + changed->windowTitle(), on);
}


void MainWindow::createHelpMenu()
{
    QAction* aboutAct = new QAction(tr("About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    QAction* aboutQtAct = new QAction(tr("About Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    helpMenu = this->menuBar()->addMenu(tr("&Help"));
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}


void MainWindow::dropEvent(QDropEvent *) {
    printf("We got a drop!\n");
}
