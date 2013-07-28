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
#include "file.h"
#include "core/globals.h"

FileMenu::FileMenu(MainWindow* mainWin)

{  
    this->mainWindow = mainWin;
    this->setTitle(tr("&File"));
    createActions();
    createMenus();
}


void FileMenu::createMenus()
{
    this->setTearOffEnabled(true);
    this->addAction(readSetAct);
    this->addAction(readParaAct);
    this->addAction(readBlockAct);
    this->addSeparator();
    this->addAction(writeSetAct);
    this->addAction(writeParaAct);
    this->addAction(saveAllAct);
    this->addSeparator();
    this->addAction(clearAct);
    this->addSeparator();
    this->addAction(printAct);
    this->addAction(exportAct);
    this->addSeparator();
    this->addAction(exitAct);
}

void FileMenu::createActions()
{
   
    readSetAct = new QAction(tr("Read sets..."), this);
    connect(readSetAct, SIGNAL(triggered()), this, SLOT(open()));
    
    readParaAct = new QAction(tr("Read parameters..."), this);
//     connect(readParaAct, SIGNAL(triggered()), this, SLOT(newFile()));
    
    readBlockAct = new QAction(tr("Read block data..."), this);
//     connect(readBlockAct, SIGNAL(triggered()), this, SLOT(newFile()));
    
    writeSetAct = new QAction(tr("Write sets..."), this);
//     connect(writeSetAct, SIGNAL(triggered()), this, SLOT(newFile()));
    
    writeParaAct = new QAction(tr("Write parameters..."), this);
//     connect(writeParaAct, SIGNAL(triggered()), this, SLOT(newFile()));
    
    saveAllAct = new QAction(tr("Save all..."), this);
//     connect(saveAllAct, SIGNAL(triggered()), this, SLOT(newFile()));
    
    clearAct = new QAction(tr("Clear all..."), this);
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clear()));
	
    printAct = new QAction(tr("&Print..."), this);
    QString printDesc = tr("Print the current view to file or printer.");
    printAct->setStatusTip(printDesc);
    printAct->setToolTip(printDesc);
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));
    
    exportAct = new QAction(tr("Export..."), this);
    connect(exportAct, SIGNAL(triggered()), this, SLOT(exportProc()));
    
    printSetupAct = new QAction(tr("&Printer setup..."), this);
		
//     connect(saveAllAct, SIGNAL(triggered()), this, SLOT(newFile()));
    
    exitAct = new QAction(tr("Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this->mainWindow, SLOT(close()));
}

void FileMenu::open()
{
  
    QComboBox* fileType = new QComboBox;
    fileType->addItem("X Y");
    fileType->addItem("X Y1 Y2");
    QComboBox* graphNum = new QComboBox;
    graphNum->addItem("0");
    graphNum->addItem("1");
    
    QWidget* fromButtons = new QWidget();
    QHBoxLayout* fromButtonsLayout = new QHBoxLayout();
    fromButtonsLayout->addWidget(new QRadioButton("File"));
    fromButtonsLayout->addWidget(new QRadioButton("Pipe"));
    fromButtonsLayout->addStretch(1);
    fromButtons->setLayout(fromButtonsLayout);
    
    QFileDialog::Options options = QFileDialog::DontUseNativeDialog;

    QFileDialog* fd = new QFileDialog(this, tr("Read Sets"), QDir::homePath(), "*");
    fd->setOptions(options);
    QLayout* layout = fd->layout();
    QGridLayout* gridbox = qobject_cast<QGridLayout*>(layout);
    
    if (gridbox) {
	    gridbox->addWidget(new QLabel("File type:"),4,0);
	    gridbox->addWidget(fileType,4,1);
	    gridbox->addWidget(new QLabel("Read from:"),5,0);
	    gridbox->addWidget(fromButtons,5,1);
	    gridbox->addWidget(new QLabel("Read to graph:"),6,0);
	    gridbox->addWidget(graphNum,6,1);
    }

    fd->setLayout(gridbox);
    QStringList fileNames;
    if (fd->exec())
	fileNames = fd->selectedFiles();
    
//  nothing selected      
    if (fileNames.size() == 0) return; 
      
    for (int i = 0; i < fileNames.size(); ++i)
	  printf("%s \n",fileNames.at(i).toAscii().constData());

    getdata(0,fileNames.at(0).toAscii().data(),DISK,XY);

    drawgraph();
}

void FileMenu::clear() 
{
    wipeout(0);
 
    inwin = TRUE;
    set_graph_active(0);
    drawgraph();
}

void FileMenu::print()
{
    QPrinter *printer = new QPrinter();
    
    //set printer defaults
    printer->setPageSize(QPrinter::Letter);
    printer->setOrientation(QPrinter::Landscape);
    printer->setResolution(600);
    
    QPrintDialog *dialog = new QPrintDialog(printer, this);
    dialog->setWindowTitle(tr("Print Document"));
    if (dialog->exec() != QDialog::Accepted)
	return;

    QPainter* painter = new QPainter(); 
    painter->begin(printer);
    this->mainWindow->gwidget->scene()->render(painter);
    painter->end();   
}

void FileMenu::exportProc()
{
    QPixmap* image = new QPixmap(800*3,600*3);
    QPainter *pngPainter = new QPainter(image);
    
    printf("Export\n");
    
//     pngPainter->setRenderHint(QPainter::Antialiasing);
    this->mainWindow->gwidget->scene()->render(pngPainter);
    pngPainter->end();
    image->save("qtgr.png");
    delete pngPainter;
    delete image;
    
}
