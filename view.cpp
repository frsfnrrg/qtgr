#include <QtGui>
#include "mainwindow.h"
#include "view.h"
#include "base/globals.h"

ViewMenu::ViewMenu(MainWindow* mainWin) :
    Menu(mainWin, "View", true)
{  
    worldDialog = NULL;
    symbolsDialog = NULL;
    ticksDialog = NULL;
    legendsDialog = NULL;
    graphTypesDialog = NULL;
    viewDialog = NULL;
    titleDialog = NULL;
    frameDialog = NULL;

    createActions();
    populateMenu(this);
}

void ViewMenu::populateMenu(QMenu* q) {
    q->addAction(viewAct);
    q->addAction(worldAct);
    q->addSeparator();
    q->addAction(graphTypesAct);
    q->addSeparator();
    q->addAction(titleAct);
    q->addAction(legendsAct);
    q->addSeparator();
    q->addAction(ticksAct);
    q->addAction(symbolsAct);
    q->addAction(frameAct);
}

QToolBar* ViewMenu::createToolBar() {
    QToolBar* tl = new QToolBar(Menu::title());
    tl->addAction(viewAct);
    tl->addAction(worldAct);
    tl->addSeparator();
    tl->addAction(graphTypesAct);
    tl->addSeparator();
    tl->addAction(titleAct);
    tl->addAction(legendsAct);
    tl->addSeparator();
    tl->addAction(ticksAct);
    tl->addAction(symbolsAct);
    tl->addAction(frameAct);
    return tl;
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
                && (ry > (1.0 - x) * y1 / (1.0 - x2))
                ) {
            view->ticks();
            view->ticksDialog->editAxis->setCurrentIndex(X_AXIS);
            view->ticksDialog->updateDialog();
            return;
        }

        if (rx < x1) {
            view->ticks();
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
    viewAct = makeAction("Set viewport",
                         "Determine the onscreen boundaries of the graph.",
                         "Ctrl+Shift+v", SLOT(view()));
    worldAct = makeAction("Set world",
                          "Determine the range of values displayed in the graph.",
                          "Ctrl+w",
                          SLOT(world()));
    titleAct = makeAction("Titling",
                          "Set the title and subtitle of the graph.",
                          "Ctrl+Shift+t",
                          SLOT(title()));
    ticksAct = makeAction("Ticks",
                          "Change spacing and labels for the graph axes.",
                          "Ctrl+t",
                          SLOT(ticks()));
    symbolsAct = makeAction("Symbols",
                            "Change display of sets on the graph.",
                            "Ctrl+s",
                            SLOT(symbols()));
    legendsAct = makeAction("Legends",
                            "Give legends to sets on the graph.",
                            "Ctrl+L",
                            SLOT(legends()));
    graphTypesAct = makeAction("Graph Type",
                               "Set the graph display metric.",
                               "Ctrl+g",
                               SLOT(graphTypes()));
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

void ViewMenu::world() {
    if (showDialog(worldDialog)) return;
    worldDialog = new ViewWorld(mainWindow);
    loadDialog(worldDialog);
}

void ViewMenu::symbols() {
    if (showDialog(symbolsDialog)) return;
    symbolsDialog = new ViewSymbols(mainWindow);
    loadDialog(symbolsDialog);
}

void ViewMenu::ticks() {
    if (showDialog(ticksDialog)) return;
    ticksDialog = new ViewTicks(mainWindow);
    loadDialog(ticksDialog);
}

void ViewMenu::graphTypes() {
    if (showDialog(graphTypesDialog)) return;
    graphTypesDialog = new ViewGraphType(mainWindow);
    loadDialog(graphTypesDialog);
}

void ViewMenu::legends() {
    if (showDialog(legendsDialog)) return;
    legendsDialog = new ViewLegends(mainWindow);
    loadDialog(legendsDialog);
}

void ViewMenu::view() {
    if (showDialog(viewDialog)) return;
    viewDialog = new ViewView(mainWindow);
    loadDialog(viewDialog);
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

