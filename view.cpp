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
    legendsEditDialog = NULL;
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
    graphTypesDialog->updateType();
}

void ViewMenu::updateGraphTypes() {
    if (graphTypesDialog) {
        graphTypesDialog->updateType();
    }
}

// TODO: classify it out!
void ViewMenu::legends()
{   
    if (legendsDialog) {
      legendsDialog->setVisible(true);
    } else {
	legendsDialog = new QDialog(this->mainWindow);
    legendsDialog->setWindowTitle(tr("QTGR: Legends"));
      
	// make input fields
	locType = new QComboBox;
    locType->addItem(tr("Viewport coordinates"));
    locType->addItem(tr("World coordinates"));
//	connect(editAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTicks()));	
	
// 	// make line edits
	legendX = new QLineEdit();
	legendY = new QLineEdit();
	legendX->setMaximumWidth(100); 
	legendY->setMaximumWidth(100); 
	
	showLegend = new QCheckBox("Show Legend");	
	//connect(apply, SIGNAL(clicked()), this, SLOT(applyTicks()));
	
	QPushButton* editLegend = new QPushButton("Edit...");
	connect(editLegend, SIGNAL(clicked()), this, SLOT(legendsEdit()));	
	
	QPushButton* apply = new QPushButton("Apply");
 	connect(apply, SIGNAL(clicked()), this, SLOT(applyLegends()));
	
	QPushButton* done  = new QPushButton("Done");
	connect(done, SIGNAL(clicked()), this, SLOT(doneLegends()));
	
	QPushButton* place  = new QPushButton("Place");
	connect(place, SIGNAL(clicked()), this, SLOT(placeLegends()));
// 	
// 
 	QGridLayout* layout = new QGridLayout();
// 	    
 	layout->addWidget(showLegend,0,0,1,2,Qt::AlignLeft);
	layout->addWidget(editLegend,0,4,1,1);
// 	
	layout->addWidget(new QLabel(""),1,0);
	
	layout->addWidget(new QLabel("Legend location: "),2,0);
	layout->addWidget(locType,2,1,1,3);
// 	
 	layout->addWidget(new QLabel(""),3,0);
// 	
 	layout->addWidget(new QLabel("Color:"),4,0);
 	layout->addWidget(new QLabel("Char size:"),5,0);
// 	layout->addWidget(majTic,4,1);
// 	layout->addWidget(minTic,5,1);
// 	
	layout->addWidget(new QLabel(""),6,0);
	
	layout->addWidget(new QLabel("Legend x:"),7,0);
 	layout->addWidget(new QLabel("Legend y:"),8,0);
	layout->addWidget(legendX,7,1);
	layout->addWidget(legendY,8,1);
	
	layout->addWidget(place,7,3,Qt::AlignHCenter);

	
	layout->addWidget(new QLabel(""),10,0);

	layout->addWidget(apply,11,1,Qt::AlignHCenter);
	layout->addWidget(done,11,3,Qt::AlignHCenter);
	
	layout->setColumnMinimumWidth(0,80);
	layout->setColumnMinimumWidth(1,80);
	layout->setColumnMinimumWidth(2,80);
	layout->setColumnMinimumWidth(3,80);
	layout->setColumnMinimumWidth(4,80);

	legendsDialog->setLayout(layout);
      
	legendsDialog->show();
    }
    updateLegends();
}

void ViewMenu::updateLegends()
{
    int gno; 
     legend leg;
    
    gno = cg; // current graph only 

    get_graph_legend(gno,&leg);
      
//     printf("UpdateLegends %i %f %f %i\n",leg.active == ON, leg.legx, leg.legy, leg.loctype);

    if (legendsDialog) {
	showLegend->setChecked(g[gno].l.active == ON);
	if (g[gno].l.loctype == VIEW) {
	    locType->setCurrentIndex(0);
	} else {
	    locType->setCurrentIndex(1);
	}
	legendX->setText(QString::number(g[gno].l.legx,'g',9));
	legendY->setText(QString::number(g[gno].l.legy,'g',9));

	legendsDialog->update();
    }
}

void ViewMenu::applyLegends()
{
  int gno,axis; 
  legend leg;
    
    gno = cg; // current graph only 

    get_graph_legend(gno,&leg);
      
//     printf("ApplyLegends %i %f %f\n",leg.active == ON, leg.legx, leg.legy);
   
    if (showLegend->isChecked()) {
	g[gno].l.active = ON;
    } else {
	g[gno].l.active = OFF;
    } 
    
    if (locType->currentIndex() == 0) {
	g[gno].l.loctype = VIEW;
    } else {
	g[gno].l.loctype = WORLD;
    }
    
    g[gno].l.legx = legendX->text().toDouble();
    g[gno].l.legy = legendY->text().toDouble();
    
    drawgraph();  
}

void ViewMenu::doneLegends()
{
  this->applyLegends();
  this->legendsDialog->setVisible(false);
}

class MouseClickCall : public MouseCallBack
{
  
public:  
    ViewMenu* view;
    
    void mouse( int x, int y, int w, int h )
    {	
    printf("mouse_callback %f %f \n" ,double(x)/w,1.0-double(y)/h);
    view->mainWindow->gwidget->mouseClickCall = NULL;
    view->mainWindow->gwidget->unsetCursor();
    view->mainWindow->statusBar()->clearMessage();
    
    view->legendX->setText(QString::number(double(x)/w,'g',3));
    view->legendY->setText(QString::number(1.0-double(y)/h,'g',3));
    view->applyLegends();
    
    }
} mouseClick;

void ViewMenu::placeLegends()
{
    mouseClick.view = this;
    mainWindow->gwidget->mouseClickCall =  &mouseClick;
    mainWindow->gwidget->setCursor(Qt::CrossCursor);
    mainWindow->statusBar()->showMessage(tr("Click to place legend"));
}


void ViewMenu::legendsEdit()
{
  if (legendsEditDialog) {
      legendsEditDialog->setVisible(true);
    } else {
	legendsEditDialog = new QDialog(this->mainWindow);
	legendsEditDialog->setWindowTitle("QTGR: Edit legend labels");
	legendsEditDialog->setMaximumHeight(300);
	legendsEditDialog->setMinimumWidth(400);

	// buttons
	QPushButton* apply = new QPushButton("Apply");
	connect(apply, SIGNAL(clicked()), this, SLOT(applyLegendsEdit()));
	
	QPushButton* done  = new QPushButton("Done");
	connect(done, SIGNAL(clicked()), this, SLOT(doneLegendsEdit()));

	// central widget for legend labels
	QScrollArea* scrollArea = new QScrollArea;
	QWidget* widget = new QWidget(); 
	QGridLayout* layout = new QGridLayout(); 
	
	for (int i=0; i<ViewMenu::maxsets; i++) {
	  setLabels[i] = new QLineEdit();
	  setLabels[i]->setMinimumWidth(240);
	  layout->addWidget(new QLabel(QString("Set ")+QString::number(i)),i,0);
	  layout->addWidget(setLabels[i],i,1);
	}

	widget->setLayout(layout);  
	scrollArea->setWidget(widget);
	
	
	// put everything together
	QGridLayout* lay = new QGridLayout();
	lay->addWidget(scrollArea,0,0,1,5);
	
	layout->addWidget(new QLabel(""),1,0);
	
	lay->addWidget(apply,2,1);
	lay->addWidget(done,2,3);
	
	layout->setColumnMinimumWidth(0,80);
	layout->setColumnMinimumWidth(1,80);
	layout->setColumnMinimumWidth(2,80);
	layout->setColumnMinimumWidth(3,80);
	layout->setColumnMinimumWidth(4,80);
	
	legendsEditDialog->setLayout(lay);
	  
	legendsEditDialog->show();  
	
    } //legendsEditDialog != NULL
    
    updateLegendsEdit();

}

void ViewMenu::updateLegendsEdit()
{
    int gno; 
    
    gno = cg; // current graph only 
    
//     printf("updateLegendEdit  max %i s %s\n",g[gno].maxplot,g[gno].l.str[0].s); 
    
    for (int i=0; i<ViewMenu::maxsets; i++) {
//        printf("updateLegendEdit   %i s %s\n",i,g[gno].l.str[i].s); 
       setLabels[i]->setText(QString::fromLocal8Bit(g[gno].l.str[i].s));
    }
    legendsEditDialog->update();

}

void ViewMenu::applyLegendsEdit()
{
    int gno; 
    
    gno = cg; // current graph only 
    
    for (int i=0; i<ViewMenu::maxsets; i++) {
	strcpy((char*)g[gno].l.str[i].s,setLabels[i]->text().toAscii().data());
    } 
}

void ViewMenu::doneLegendsEdit()
{
  this->applyLegendsEdit();
  this->legendsEditDialog->setVisible(false);
}



