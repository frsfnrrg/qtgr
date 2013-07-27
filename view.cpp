/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <iostream>
#include <QtGui>
#include "mainwindow.h"
#include "view.h"
#include "globals.h"

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
//    legendsEditDialog = NULL;
    graphTypesDialog = NULL;
    set_mode = 0 ; // 0 means act on one set; <>0 means all sets (FIXME not implemented);
}

void ViewMenu::createMenus()
{
    this->setTearOffEnabled(true);
    this->addAction(worldAct);
    this->addSeparator();
    this->addAction(titleAct);
    this->addAction(ticksAct);
    this->addAction(symbolsAct);
    this->addAction(legendsAct);
    this->addSeparator();

    QMenu* graphs = new QMenu("Graphs");
    graphs->addAction(graphTypesAct);
    this->addMenu(graphs);
}

class MouseDoubleCall : public MouseCallBack
{
  
public:  
    ViewMenu* view;
    
    void mouse( int x, int y, int w, int h ) {	
        double rx = double(x)/w;
	double ry = 1.0-double(y)/h;
	
	if (rx <  g[cg].v.xv1) { // y-axis props 
	    view->ticks();
	    view->ticksDialog->editAxis->setCurrentIndex(1);
	    view->ticksDialog->updateTicks();
	    return;
	}
	if (rx > g[cg].v.xv2) { // legend
	    view->legends();
	    return;
	}
	if (ry < g[cg].v.yv1) { // x-axis props
	    view->ticks();
	    view->ticksDialog->editAxis->setCurrentIndex(0);
	    view->ticksDialog->updateTicks();
	    return;
	}
	if (ry > g[cg].v.yv2) { // title
	    return;
	}
	
	// default: symbols
	view->symbols();
    }
    
} mouseDouble;

void ViewMenu::createActions()
{  
    worldAct = new QAction(tr("Define world..."), this);
    connect(worldAct, SIGNAL(triggered()), this, SLOT(world()));

    titleAct = new QAction(tr("Title/Subtitle..."), this);
    //     connect(autoScaleAct, SIGNAL(triggered()), this, SLOT(autoScale()));

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
    worldDialog->updateWorld();
}

void ViewMenu::updateWorld() 
{
  if (worldDialog) {
	worldDialog->updateWorld();
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
    symbolsDialog->updateSymbols();
}

void ViewMenu::updateSymbols()
{
    if (symbolsDialog) {
	symbolsDialog->updateSymbols();
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
    ticksDialog->updateTicks();
}

void ViewMenu::updateTicks() 
{
  if (ticksDialog) {
	ticksDialog->updateTicks();
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

// TODO: classify it out!
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





