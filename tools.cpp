#include <QtGui>
#include "mainwindow.h"
#include "tools.h"
#include "base/globals.h"
#include "prop.h"

ToolsMenu::ToolsMenu(MainWindow* mainWin)
{  
    this->mainWindow = mainWin;
    this->setTitle(tr("Tools"));
    createActions();
    createMenus();
}


void ToolsMenu::createMenus()
{
    this->setTearOffEnabled(true);
    this->addAction(autoScaleAct);
    this->addAction(zoomRectAct);
}

void ToolsMenu::createActions()
{
    autoScaleAct = createQAction(tr("Autoscale"),
                                 tr("Rescale the displayed area of the graph to show all points."),
                                 this);
    autoScaleAct->setShortcut(QKeySequence(tr("Ctrl+a")));
    connect(autoScaleAct, SIGNAL(triggered()), this, SLOT(autoScale()));

    zoomRectAct = createQAction(tr("Rect Zoom"),
                                tr("Zoom the graph in."),
                                this);
    zoomRectAct->setShortcut(QKeySequence(tr("Ctrl+r")));
    connect(zoomRectAct, SIGNAL(triggered()), this, SLOT(zoom()));
}

QToolBar* ToolsMenu::createToolBar() {
    QToolBar* foo = new QToolBar(tr("Tools"));
    foo->addAction(autoScaleAct);
    foo->addAction(zoomRectAct);
    return foo;
}

void ToolsMenu::autoScale()
{
   autoscale_proc();
   WorldDimProp::send();
}

void ToolsMenu::zoom() {
    GraphWidget::startRect(this);
}

void ToolsMenu::finishRect(double x1, double x2, double y1, double y2) {
    double wx1, wy1, wx2, wy2;

    if (x1 == x2 || y1 == y2) {
        printf("Zoomed rectangle is zero along X or Y, zoom cancelled");
    } else {
        view2world(x1, y1, &wx1, &wy1);
        view2world(x2, y2, &wx2, &wy2);
        if (wx1 > wx2) {
            fswap(&wx1, &wx2);
        }
        if (wy1 > wy2) {
            fswap(&wy1, &wy2);
        }
        g[cg].w.xg1 = wx1;
        g[cg].w.xg2 = wx2;
        g[cg].w.yg1 = wy1;
        g[cg].w.yg2 = wy2;
        default_axis(cg, g[cg].auto_type, X_AXIS);
        default_axis(cg, g[cg].auto_type, ZX_AXIS);
        default_axis(cg, g[cg].auto_type, Y_AXIS);
        default_axis(cg, g[cg].auto_type, ZY_AXIS);
        drawgraph();
    }
}



