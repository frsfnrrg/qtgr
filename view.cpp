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

    set_mode = 0 ; // 0 means act on one set; <>0 means all sets (FIXME not implemented);
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
    return tl;
}

class MouseDoubleCall : public MouseCallBack
{
  
public:  
    ViewMenu* view;
    
    void mouse( int x, int y, int w, int h ) {	
        double rx = double(x)/w;
	double ry = 1.0-double(y)/h;
	
    if (rx < g[cg].v.xv1) { // y-axis props
	    view->ticks();
	    view->ticksDialog->editAxis->setCurrentIndex(1);
        view->ticksDialog->updateDialog();
	    return;
	}
	if (rx > g[cg].v.xv2) { // legend
	    view->legends();
	    return;
	}
	if (ry < g[cg].v.yv1) { // x-axis props
	    view->ticks();
	    view->ticksDialog->editAxis->setCurrentIndex(0);
        view->ticksDialog->updateDialog();
	    return;
	}
	if (ry > g[cg].v.yv2) { // title
        view->title();
	    return;
	}
	
	// default: symbols
	view->symbols();
    }
    
} mouseDouble;

void ViewMenu::createActions()
{  
    viewAct = createQAction(tr("Set viewport"),
                            tr("Determine the onscreen boundaries of the graph."),
                            this);
    connect(viewAct, SIGNAL(triggered()), this, SLOT(view()));

    worldAct = createQAction(tr("Set world"),
                             tr("Determine the range of values displayed in the graph."),
                             this);
    connect(worldAct, SIGNAL(triggered()), this, SLOT(world()));

    titleAct = createQAction(tr("Titling"),
                             tr("Set the title and subtitle of the graph."),
                             this);
    connect(titleAct, SIGNAL(triggered()), this, SLOT(title()));

    ticksAct = createQAction(tr("Ticks"),
                             tr("Change spacing and labels for the graph axes."),
                             this);
    connect(ticksAct, SIGNAL(triggered()), this, SLOT(ticks()));

    symbolsAct = createQAction(tr("Symbols"),
                               tr("Change display of sets on the graph."),
                               this);
    connect(symbolsAct, SIGNAL(triggered()), this, SLOT(symbols()));

    legendsAct = createQAction(tr("Legends"),
                               tr("Give legends to sets on the graph."),
                               this);
    connect(legendsAct, SIGNAL(triggered()), this, SLOT(legends()));
    
    graphTypesAct = createQAction(tr("Graph Type"),
                                  tr("Set the graph display metric."),
                                  this);
    connect(graphTypesAct, SIGNAL(triggered()), this, SLOT(graphTypes()));

    // setup double click handler
    mouseDouble.view = this;
    mainWindow->gwidget->mouseDoubleCall =  &mouseDouble;
}

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
