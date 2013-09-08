#include <QtGui>
#include "mainwindow.h"
#include "view.h"
#include "view/symbols.h"
#include "view/axis.h"
#include "view/legend.h"
#include "view/title.h"
#include "view/frame.h"
#include "base/globals.h"
#include "graphwidget.h"
#include "view/dimensions.h"

//#include "view/world.h"
//#include "view/graphtype.h"
//#include "view/viewport.h"

ViewMenu::ViewMenu(MainWindow* mainWin) :
    Menu(mainWin, "View", true)
{  
//    worldDialog = NULL;
//    graphTypesDialog = NULL;
//    viewDialog = NULL;

    symbolsDialog = NULL;
    ticksDialog = NULL;
    legendsDialog = NULL;
    titleDialog = NULL;
    frameDialog = NULL;
    dimsDialog = NULL;

    createActions();
    populateMenu(this);
}

void ViewMenu::populateMenu(QMenu* q) {
//    q->addAction(viewAct);
//    q->addAction(worldAct);
//    q->addSeparator();
//    q->addAction(graphTypesAct);
    q->addAction(dimsAct);
    q->addSeparator();
    q->addAction(titleAct);
    q->addAction(legendsAct);
    q->addSeparator();
    q->addAction(axisAct);
    q->addAction(symbolsAct);
    q->addAction(frameAct);
}

void ViewMenu::populateToolBar(QToolBar* q) {
//    q->addAction(viewAct);
//    q->addAction(worldAct);
//    q->addSeparator();
//    q->addAction(graphTypesAct);
    q->addAction(dimsAct);
    q->addSeparator();
    q->addAction(titleAct);
    q->addAction(legendsAct);
    q->addSeparator();
    q->addAction(axisAct);
    q->addAction(symbolsAct);
    q->addAction(frameAct);
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

        // todo: fix bottom left corner

        if (ry > y2 && (ry > 1.0 - rx * (1.0 - y2) / x1)
                && (ry > 1.0 + (rx - 1.0) * (1.0 - y2) / (1.0 - x2))) {
            view->title();
            return;
        }

        if (ry < y1 && (ry < rx * y1 / x1)
                && (ry > (1.0 - x) * y1 / (1.0 - x2))
                ) {
            view->axis();
            view->ticksDialog->editAxis->setCurrentIndex(X_AXIS);
            view->ticksDialog->updateDialog();
            return;
        }

        if (rx < x1) {
            view->axis();
            view->ticksDialog->editAxis->setCurrentIndex(Y_AXIS);
            view->ticksDialog->updateDialog();
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
//    viewAct = makeAction("Set viewport",
//                         "Determine the onscreen boundaries of the graph.",
//                         "Ctrl+Shift+v", SLOT(view()));
//    worldAct = makeAction("Set world",
//                          "Determine the range of values displayed in the graph.",
//                          "Ctrl+w",
//                          SLOT(world()));
//    graphTypesAct = makeAction("Graph Type",
//                               "Set the graph display metric.",
//                               "Ctrl+g",
//                               SLOT(graphTypes()));

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



//void ViewMenu::world() {
//    if (showDialog(worldDialog)) return;
//    worldDialog = new ViewWorld(mainWindow);
//    loadDialog(worldDialog);
//}

//void ViewMenu::view() {
//    if (showDialog(viewDialog)) return;
//    viewDialog = new ViewView(mainWindow);
//    loadDialog(viewDialog);
//}

//void ViewMenu::graphTypes() {
//    if (showDialog(graphTypesDialog)) return;
//    graphTypesDialog = new ViewGraphType(mainWindow);
//    loadDialog(graphTypesDialog);
//}
