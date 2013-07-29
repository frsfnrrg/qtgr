//#include <iostream>
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

void ViewMenu::createMenus()
{
    this->setTearOffEnabled(true);
    QMenu* graphs = new QMenu("Graphs");
    graphs->addAction(graphTypesAct);
    this->addMenu(graphs);
    this->addSeparator();
    this->addAction(viewAct);
    this->addAction(worldAct);
    this->addSeparator();
    this->addAction(titleAct);
    this->addAction(ticksAct);
    this->addAction(symbolsAct);
    this->addAction(legendsAct);
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
    viewAct = new QAction(tr("Define viewport..."), this);
    connect(viewAct, SIGNAL(triggered()), this, SLOT(view()));

    worldAct = new QAction(tr("Define world..."), this);
    connect(worldAct, SIGNAL(triggered()), this, SLOT(world()));

    titleAct = new QAction(tr("Title/Subtitle..."), this);
    connect(titleAct, SIGNAL(triggered()), this, SLOT(title()));

    ticksAct = new QAction(tr("Ticks/Tick lables..."), this);
    connect(ticksAct, SIGNAL(triggered()), this, SLOT(ticks()));

    symbolsAct = new QAction(tr("Symbols..."), this);
    connect(symbolsAct, SIGNAL(triggered()), this, SLOT(symbols()));

    legendsAct = new QAction(tr("Legends..."), this);
    connect(legendsAct, SIGNAL(triggered()), this, SLOT(legends()));
    
    graphTypesAct = new QAction(tr("Graph Types"), this);
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
