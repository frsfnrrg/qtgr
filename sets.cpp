#include "sets.h"

SetsMenu::SetsMenu(MainWindow* mwin) :
    QMenu(mwin)
{
    this->mainWindow = mwin;
    this->setTitle(tr("Sets"));
    this->setTearOffEnabled(true);

    createActions();
    createMenus();
}

void SetsMenu::createMenus() {
    this->addAction(kadAct);
    this->addAction(editAct);
}

void SetsMenu::createActions() {
    kadAct = createQAction(tr("Kill/Activate"),
                           tr("Remove, enable, or disable a set"),
                           tr(""),this);
    editAct = createQAction(tr("Edit set"),
                            tr("Edit the points in a set"),
                            tr(""), this);
}
