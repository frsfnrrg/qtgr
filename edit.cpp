#include "edit.h"

#include <QToolBar>

EditMenu::EditMenu(MainWindow* mainWin) :
    Menu(mainWin,"Edit",true)
{
    createActions();
    populateMenu(this);
}

void EditMenu::populateToolBar(QToolBar* q) {
    q->addAction(cutAct);
    q->addAction(copyAct);
    q->addAction(pasteAct);
}

void EditMenu::populateMenu(QMenu* q)
{
    q->addAction(cutAct);
    q->addAction(copyAct);
    q->addAction(pasteAct);
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
    pasteAct->setEnabled(false);
}



