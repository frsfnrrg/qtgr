#include "transform.h"

TransformMenu::TransformMenu(MainWindow* mainWin) :
    QMenu(mainWin)
{
    this->mainWindow = mainWin;
    this->setTitle(tr("Transforms"));
    createActions();
    createMenus();
}

void TransformMenu::createActions() {
    integrateAct = new QAction(tr("Integrate"), this);
    integrateAct->setStatusTip(tr("Integrate a set"));

    differentiateAct = new QAction(tr("Differentiate"), this);
    differentiateAct->setStatusTip(tr("Differentiate a set"));
}

void TransformMenu::createMenus() {
    this->setTearOffEnabled(true);
    this->addAction(integrateAct);
    this->addAction(differentiateAct);
}

// TODO: create the set of dialogs...
// (maybe in a subfolder?)
