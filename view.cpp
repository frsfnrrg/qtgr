#include "mainwindow.h"
#include "view.h"

#include "base/globals.h"
#include "graphwidget.h"

#include "view/symbols.h"
#include "view/axis.h"
#include "view/legend.h"
#include "view/title.h"
#include "view/frame.h"
#include "view/dimensions.h"
#include "view/text.h"

ViewMenu::ViewMenu(MainWindow* mainWin) :
    Menu(mainWin, "View", true)
{  
    symbolsDialog = NULL;
    ticksDialog = NULL;
    legendsDialog = NULL;
    titleDialog = NULL;
    frameDialog = NULL;
    dimsDialog = NULL;
    textDialog = NULL;

    createActions();
    populateMenu(this);
}

void ViewMenu::populateMenu(QMenu* q) {
    q->addAction(dimsAct);
    q->addSeparator();
    q->addAction(titleAct);
    q->addAction(legendsAct);
    q->addSeparator();
    q->addAction(axisAct);
    q->addAction(symbolsAct);
    q->addAction(frameAct);
    q->addSeparator();
    q->addAction(textAct);
}

void ViewMenu::populateToolBar(QToolBar* q) {
    q->addAction(dimsAct);
    q->addSeparator();
    q->addAction(titleAct);
    q->addAction(legendsAct);
    q->addSeparator();
    q->addAction(axisAct);
    q->addAction(symbolsAct);
    q->addAction(frameAct);
    q->addSeparator();
    q->addAction(textAct);
}

class MouseDoubleCall : public MouseCallBack
{
  
public:  
    ViewMenu* view;
    
    void mouse( int x, int y, int w, int h ) {	
        double rx = double(x)/w;
        double ry = 1.0-double(y)/h;

        double x1,x2,y1,y2;
        x1 = g[cg].v.xv1;
        x2 = g[cg].v.xv2;
        y1 = g[cg].v.yv1;
        y2 = g[cg].v.yv2;

        if (ry > y2 && (ry > 1.0 - rx * (1.0 - y2) / x1)
                && (ry > 1.0 + (rx - 1.0) * (1.0 - y2) / (1.0 - x2))) {
            view->title();
            return;
        }

        if (ry < y1 && (ry < rx * y1 / x1)
                && (ry <  (rx - 1.0) * y1 / (x2 - 1.0))

                ) {
            view->axis(X_AXIS);
            return;
        }

        if (rx < x1) {
            view->axis(Y_AXIS);
            return;
        }

        if (rx > x2) {
            view->legends();
            return;
        }

        view->symbols();
    }
    
} mouseDouble;

void ViewMenu::createActions()
{
    titleAct = makeAction("Titling",
                          "Set the title and subtitle of the graph.",
                          "Ctrl+Shift+t",
                          SLOT(title()));
    dimsAct = makeAction("Graph Details",
                         "Control the size, zoom, and display type of the graph.",
                         "Ctrl+w",
                         SLOT(dims()));
    axisAct = makeAction("Ticks",
                          "Change spacing and labels for the graph axes.",
                          "Ctrl+t",
                          SLOT(axis()));
    symbolsAct = makeAction("Symbols",
                            "Change display of sets on the graph.",
                            "Ctrl+s",
                            SLOT(symbols()));
    legendsAct = makeAction("Legends",
                            "Give legends to sets on the graph.",
                            "Ctrl+L",
                            SLOT(legends()));
    frameAct = makeAction("Frame",
                          "Alter the look of the graph frame",
                          "Ctrl+f",
                          SLOT(frame()));

    textAct = makeAction("Text",
                          "Add free strings to the graph",
                          "",
                          SLOT(text()));

    // setup double click handler
    mouseDouble.view = this;
    mainWindow->gwidget->mouseDoubleCall =  &mouseDouble;
}


void ViewMenu::updateSymbolsLegend() {
    if (symbolsDialog) symbolsDialog->updateLegend();
}

void ViewMenu::updateIndividualLegend(int cset) {
    if (legendsDialog) legendsDialog->updateLegendsField(cset);
}

void ViewMenu::axis(int axis) {
    if (ticksDialog) {
        ticksDialog->editAxis->setCurrentIndex(axis);
        showDialog(ticksDialog);
        return;
    }
    ticksDialog = new ViewAxis(mainWindow);
    ticksDialog->editAxis->setCurrentIndex(axis);
    loadDialog(ticksDialog);
}

// Lots and lots of boilerplate here

void ViewMenu::symbols() {
    if (showDialog(symbolsDialog)) return;
    symbolsDialog = new ViewSymbols(mainWindow);
    loadDialog(symbolsDialog);
}

void ViewMenu::axis() {
    if (showDialog(ticksDialog)) return;
    ticksDialog = new ViewAxis(mainWindow);
    loadDialog(ticksDialog);
}

void ViewMenu::legends() {
    if (showDialog(legendsDialog)) return;
    legendsDialog = new ViewLegend(mainWindow);
    loadDialog(legendsDialog);
}

void ViewMenu::title() {
    if (showDialog(titleDialog)) return;
    titleDialog = new ViewTitle(mainWindow);
    loadDialog(titleDialog);
}

void ViewMenu::frame() {
    if (showDialog(frameDialog)) return;
    frameDialog = new ViewFrame(mainWindow);
    loadDialog(frameDialog);
}

void ViewMenu::dims() {
    if (showDialog(dimsDialog)) return;
    dimsDialog = new ViewDimensions(mainWindow);
    loadDialog(dimsDialog);
}

void ViewMenu::text() {
    if (showDialog(textDialog)) return;
    textDialog = new ViewText(mainWindow);
    loadDialog(textDialog);
}
