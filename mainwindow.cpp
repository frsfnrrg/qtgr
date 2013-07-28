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
#include "edit.h"
#include "view.h"
#include "tools.h"
#include "graphwidget.h"
#include "base/globals.h"

MainWindow::MainWindow()

{
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);
    scene->setBackgroundBrush(Qt::white);


    gwidget = new GraphWidget(scene,this);
    gwidget->setMouseTracking(true);
    gwidget->setMinimumWidth(806);
    gwidget->setMaximumWidth(806);

    setCentralWidget(gwidget);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();

    setCurrentFile("");
    setUnifiedTitleAndToolBarOnMac(true);

    // initialize grapics
    inwin = TRUE;
    //    set_default_graph(0);
    set_graph_active(0);
    drawgraph();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}


//slots
void MainWindow::newFile()

{
    if (maybeSave()) {
//         textEdit->clear();
        setCurrentFile("");
    }
}


bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}
//! [10]

//! [11]
bool MainWindow::saveAs()
//! [11] //! [12]
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}
//! [12]

//! [13]
void MainWindow::about()
//! [13] //! [14]
{
   QMessageBox::about(this, tr("About Application"),
            tr("QTGR is a port to QT of the graphing program XVGR.\n"
               "Formula transformation format is complicated:\n"
               "x = (index < 10)*y + (index >= 10)*(- x*x)"));
}
//! [14]

//! [15]
void MainWindow::documentWasModified()
//! [15] //! [16]
{
//     setWindowModified(textEdit->document()->isModified());
}

void MainWindow::autoScale()
{
   autoscale_proc(); 
}

// Actions
void MainWindow::createActions()
{
   
//     cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
//     cutAct->setShortcuts(QKeySequence::Cut);
//     cutAct->setStatusTip(tr("Cut the current selection's contents to the "
//                             "clipboard"));
//     connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));
// 
//     copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
//     copyAct->setShortcuts(QKeySequence::Copy);
//     copyAct->setStatusTip(tr("Copy the current selection's contents to the "
//                              "clipboard"));
//     connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));
// 
//     pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
//     pasteAct->setShortcuts(QKeySequence::Paste);
//     pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
//                               "selection"));
//     connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));
//     

    

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));


    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));



//     cutAct->setEnabled(false);
//     copyAct->setEnabled(false);
//     connect(textEdit, SIGNAL(copyAvailable(bool)),
//             cutAct, SLOT(setEnabled(bool)));
//     connect(textEdit, SIGNAL(copyAvailable(bool)),
//             copyAct, SLOT(setEnabled(bool)));
}



void MainWindow::createMenus()
{
    fileMenu = new FileMenu(this);
    this->menuBar()->addMenu(fileMenu);
    
    editMenu = new EditMenu(this);
    this->menuBar()->addMenu(editMenu);
    
    viewMenu = new ViewMenu(this);
    this->menuBar()->addMenu(viewMenu);
    
    toolsMenu = new ToolsMenu(this);
    this->menuBar()->addMenu(toolsMenu);

    this->menuBar()->addSeparator();

    helpMenu = this->menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars()
{
    fileToolBar = this->addToolBar(tr("File"));
    
    autoScaleAct = new QAction(tr("&AS"), this);
    autoScaleAct->setStatusTip(tr("Autoscale"));
    connect(autoScaleAct, SIGNAL(triggered()), this, SLOT(autoScale()));  
    fileToolBar->addAction(autoScaleAct);

    editToolBar = this->addToolBar(tr("Edit"));
    editToolBar->addAction(((EditMenu*) editMenu)->cutAct);
    editToolBar->addAction(((EditMenu*) editMenu)->copyAct);
    editToolBar->addAction(((EditMenu*) editMenu)->pasteAct);
}

void MainWindow::createStatusBar()
{
    this->statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings("Trolltech", "Application Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}


void MainWindow::writeSettings()

{
    QSettings settings("Trolltech", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}


//! [40]
bool MainWindow::maybeSave()
//! [40] //! [41]
{
//     if (textEdit->document()->isModified()) {
//         QMessageBox::StandardButton ret;
//         ret = QMessageBox::warning(this, tr("Application"),
//                      tr("The document has been modified.\n"
//                         "Do you want to save your changes?"),
//                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//         if (ret == QMessageBox::Save)
//             return save();
//         else if (ret == QMessageBox::Cancel)
//             return false;
//     }
    return true;
}

void MainWindow::loadFile(const QString &fileName)
//! [42] //! [43]
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
//     textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}



bool MainWindow::saveFile(const QString &fileName)

{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
//     out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

 void MainWindow::setCurrentFile(const QString &fileName)
//! [46] //! [47]
{
    curFile = fileName;
//     textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}
//! [47]

//! [48]
QString MainWindow::strippedName(const QString &fullFileName)
//! [48] //! [49]
{
    return QFileInfo(fullFileName).fileName();
}
//! [49]
