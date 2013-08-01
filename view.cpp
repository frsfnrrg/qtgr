#include <QtGui>
#include "mainwindow.h"
#include "view.h"
#include "base/globals.h"

ViewMenu::ViewMenu(MainWindow* mainWin)
{  
    this->mainWindow = mainWin;
    this->setTitle(tr("View"));
    createActions();
    createMenus();
    worldDialog = NULL;
    symbolsDialog = NULL;
    ticksDialog = NULL;
    legendsDialog = NULL;
    graphTypesDialog = NULL;
    viewDialog = NULL;
    titleDialog = NULL;
    frameDialog = NULL;
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

void ViewMenu::createMenus()
{
    this->setTearOffEnabled(true);
    populateMenu(this);
}

QToolBar* ViewMenu::createToolBar() {
    QToolBar* tl = new QToolBar(tr("View"));
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
    viewAct = createQAction(tr("Set viewport"),
                            tr("Determine the onscreen boundaries of the graph."),
                            tr("Ctrl+Shift+v"),
                            this);
    connect(viewAct, SIGNAL(triggered()), this, SLOT(view()));

    worldAct = createQAction(tr("Set world"),
                             tr("Determine the range of values displayed in the graph."),
                             tr("Ctrl+w"),
                             this);
    connect(worldAct, SIGNAL(triggered()), this, SLOT(world()));

    titleAct = createQAction(tr("Titling"),
                             tr("Set the title and subtitle of the graph."),
                             tr("Ctrl+Shift+t"),
                             this);
    connect(titleAct, SIGNAL(triggered()), this, SLOT(title()));

    ticksAct = createQAction(tr("Ticks"),
                             tr("Change spacing and labels for the graph axes."),
                             tr("Ctrl+t"),
                             this);
    connect(ticksAct, SIGNAL(triggered()), this, SLOT(ticks()));

    symbolsAct = createQAction(tr("Symbols"),
                               tr("Change display of sets on the graph."),
                               tr("Ctrl+s"),
                               this);
    connect(symbolsAct, SIGNAL(triggered()), this, SLOT(symbols()));

    legendsAct = createQAction(tr("Legends"),
                               tr("Give legends to sets on the graph."),
                               tr("Ctrl+L"),
                               this);
    connect(legendsAct, SIGNAL(triggered()), this, SLOT(legends()));
    
    graphTypesAct = createQAction(tr("Graph Type"),
                                  tr("Set the graph display metric."),
                                  tr("Ctrl+g"),
                                  this);
    connect(graphTypesAct, SIGNAL(triggered()), this, SLOT(graphTypes()));

    frameAct = createQAction(tr("Frame"),
                             tr("Alter the look of the graph frame"),
                             tr("Ctrl+f"),
                             this);
    connect(frameAct, SIGNAL(triggered()), this, SLOT(frame()));

    // setup double click handler
    mouseDouble.view = this;
    mainWindow->gwidget->mouseDoubleCall =  &mouseDouble;
}


void ViewMenu::updateSymbolsLegend() {
    if (symbolsDialog) {
        symbolsDialog->updateLegend();
    }
}

void ViewMenu::updateIndividualLegend(int cset) {
    if (legendsDialog) {
        legendsDialog->updateLegendsField(cset);
    }
}

// Lots and lots of boilerplate here

void ViewMenu::world()
{
    if (worldDialog) {
        worldDialog->setVisible(true);
    } else {
        worldDialog = new ViewWorld(this->mainWindow);
        worldDialog->show();
    }
    worldDialog->updateDialog();
}

void ViewMenu::updateWorld() 
{
    if (worldDialog) {
        worldDialog->updateDialog();
    }
}

void ViewMenu::symbols()
{
    if (symbolsDialog) {
        symbolsDialog->setVisible(true);
    } else {
        symbolsDialog = new ViewSymbols(this->mainWindow);
        symbolsDialog->show();
    }
    symbolsDialog->updateDialog();
}

void ViewMenu::updateSymbols()
{
    if (symbolsDialog) {
        symbolsDialog->updateDialog();
    }
}


void ViewMenu::ticks()
{   
    if (ticksDialog) {
        ticksDialog->setVisible(true);
    } else {
        ticksDialog = new ViewTicks(this->mainWindow);
        ticksDialog->show();
    }
    ticksDialog->updateDialog();
}

void ViewMenu::updateTicks() 
{
    if (ticksDialog) {
        ticksDialog->updateDialog();
    }
}

void ViewMenu::graphTypes() {
    if (graphTypesDialog) {
        graphTypesDialog->setVisible(true);
    } else {
        graphTypesDialog = new ViewGraphType(this->mainWindow);
        graphTypesDialog->show();
    }
    graphTypesDialog->updateDialog();
}

void ViewMenu::updateGraphTypes() {
    if (graphTypesDialog) {
        graphTypesDialog->updateDialog();
    }
}

void ViewMenu::legends()
{   
    if (legendsDialog) {
        legendsDialog->setVisible(true);
    } else {
        legendsDialog = new ViewLegends(this->mainWindow);
        legendsDialog->show();
    }
    legendsDialog->updateDialog();
}

void ViewMenu::updateLegends()
{
    if (legendsDialog) {
        legendsDialog->updateDialog();
    }
}

void ViewMenu::view()
{
    if (viewDialog) {
        viewDialog->setVisible(true);
    } else {
        viewDialog = new ViewView(this->mainWindow);
        viewDialog->show();
    }
    viewDialog->updateDialog();
}

void ViewMenu::updateView()
{
    if (viewDialog) {
        viewDialog->updateDialog();
    }
}

void ViewMenu::title()
{
    if (titleDialog) {
        titleDialog->setVisible(true);
    } else {
        titleDialog = new ViewTitle(this->mainWindow);
        titleDialog->show();
    }
    titleDialog->updateDialog();
}

void ViewMenu::updateTitle()
{
    if (titleDialog) {
        titleDialog->updateDialog();
    }
}

void ViewMenu::frame()
{
    if (frameDialog) {
        frameDialog->setVisible(true);
    } else {
        frameDialog = new ViewFrame(this->mainWindow);
        frameDialog->show();
    }
    frameDialog->updateDialog();
}

void ViewMenu::updateFrame()
{
    if (frameDialog) {
        frameDialog->updateDialog();
    }
}

