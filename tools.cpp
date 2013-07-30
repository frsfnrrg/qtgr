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
    this->addAction(zoomOutAct);
//    this->addAction(worldAct);
//     this->addAction(viewAct);
  
}

void ToolsMenu::createActions()
{
   
//    worldAct = new QAction(tr("Define world..."), this);
//     connect(autoScaleAct, SIGNAL(triggered()), this, SLOT(autoScale()));
//   
//     viewAct = new QAction(tr("Define view..."), this);
//     connect(autoScaleAct, SIGNAL(triggered()), this, SLOT(autoScale()));

    autoScaleAct = new QAction(tr("Autoscale"), this);
    connect(autoScaleAct, SIGNAL(triggered()), this, SLOT(autoScale()));

    zoomRectAct = new QAction(tr("Zoom rect"), this);
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



