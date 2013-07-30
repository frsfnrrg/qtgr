#include <QtGui>
#include "mainwindow.h"
#include "edit.h"
#include "base/globals.h"
#include "transform.h"
#include "prop.h"

EditMenu::EditMenu(MainWindow* mainWin)
{  
    this->mainWindow = mainWin;
    this->setTitle(tr("Edit"));
    createActions();
    createMenus();
}


void EditMenu::createMenus()
{
    this->setTearOffEnabled(true);
    this->addMenu(new TransformMenu(this->mainWindow));
    this->addSeparator();
    this->addAction(cutAct);
    this->addAction(copyAct);
    this->addAction(pasteAct);
}

void EditMenu::createActions()
{
    cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cut"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));

    copyAct = new QAction(QIcon(":/images/copy.png"), tr("Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));

    pasteAct = new QAction(QIcon(":/images/paste.png"), tr("Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    
    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
}

void EditMenu::autoScale()
{
    autoscale_proc();
    WorldDimProp::send();
}



