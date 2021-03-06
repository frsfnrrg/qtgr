#include "mainwindow.h"
#include "tools.h"
#include "prop.h"
#include "graphwidget.h"
#include "tools/options.h"
#include "tools/status.h"
#include "util.h"

#include "base/globals.h"
#include "base/noxprotos.h"
#include "base/xprotos.h"

#include <QToolBar>

ToolsMenu::ToolsMenu(MainWindow* mainWin) :
    Menu(mainWin, "Tools", true)
{
    optionsDialog = NULL;
    statusDialog = NULL;
    createActions();
    populateMenu(this);
}

void ToolsMenu::populateMenu(QMenu* q) {
    q->addAction(autoScaleAct);
    q->addAction(zoomRectAct);
    q->addSeparator();
    q->addAction(optionsAct);
    q->addAction(statusAct);
}

void ToolsMenu::createActions()
{
    autoScaleAct = makeAction("Autoscale",
                                 "Rescale the displayed area of the graph to show all points.",
                                 "Alt+N",
                                 SLOT(autoScale()));
    zoomRectAct = makeAction("Rect Zoom",
                             "Zoom the graph in.",
                             "ALt+R",
                             SLOT(zoom()));
    optionsAct = makeAction("Options",
                            "Configure the program settings",
                            "Alt+O",
                            SLOT(options()));
    statusAct = makeAction("Status",
                            "See the status and metrics of the sets",
                            "Alt+.",
                            SLOT(status()));
}

void ToolsMenu::populateToolBar(QToolBar* foo) {
    foo->addAction(autoScaleAct);
    foo->addAction(zoomRectAct);
}

void ToolsMenu::autoScale()
{
    autoscale_graph(cg, -3);
    drawgraph();
    WorldDimProp::send(this);
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

    WorldDimProp::send(this);
}

void ToolsMenu::options() {
    if (showDialog(optionsDialog)) return;
    optionsDialog = ToolsOptions::getOptionsDialog(mainWindow);
    loadDialog(optionsDialog);
}

void ToolsMenu::status() {
    if (showDialog(statusDialog)) return;
    statusDialog = new ToolsStatus(mainWindow);
    loadDialog(statusDialog);
}



