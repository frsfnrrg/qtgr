#include "sets.h"

SetsMenu::SetsMenu(MainWindow* mwin) :
    QMenu(mwin)
{
    this->mainWindow = mwin;
    this->setTitle(tr("Sets"));
    this->setTearOffEnabled(true);

    kadDialog = NULL;
    editDialog = NULL;

    createActions();
    populateMenu(this);
}

void SetsMenu::createActions() {
    kadAct = createQAction(tr("Kill/(De)Activate"),
                           tr("Remove, enable, or disable a set"),
                           tr(""),this);
    connect(kadAct, SIGNAL(triggered()), this, SLOT(kad()));

    editAct = createQAction(tr("Edit"),
                            tr("Edit the points, type, and more of a set"),
                            tr(""), this);
    connect(editAct, SIGNAL(triggered()), this, SLOT(edit()));

    moveAct = createQAction(tr("Move"),
                            tr("Move sets around"),
                            tr(""), this);

    copyAct = createQAction(tr("Copy"),
                            tr("Duplicate a set"),
                            tr(""), this);

    splitAct = createQAction(tr("Split"),
                            tr("Divide set"),
                            tr(""), this);

    joinAct = createQAction(tr("Join"),
                            tr("Join sets"),
                            tr(""), this);
}


void SetsMenu::populateMenu(QMenu* q) {
    q->addAction(kadAct);
    q->addAction(editAct);
    q->addSeparator();
    q->addAction(moveAct);
    q->addAction(copyAct);
    q->addSeparator();
    q->addAction(splitAct);
    q->addAction(joinAct);
}


QToolBar* SetsMenu::createToolBar() {
    QToolBar* q = new QToolBar(tr("Sets"));
    q->addAction(kadAct);
    q->addAction(editAct);
    q->addSeparator();
    q->addAction(moveAct);
    q->addAction(copyAct);
    q->addSeparator();
    q->addAction(splitAct);
    q->addAction(joinAct);
    return q;
}

void SetsMenu::edit() {
    if (editDialog) {
        editDialog->setVisible(true);
    } else {
        editDialog = new SetsEdit(this->mainWindow);
        editDialog->show();
    }
    editDialog->updateDialog();
}

void SetsMenu::updateEdit() {
    if (editDialog) editDialog->updateDialog();
}


void SetsMenu::kad() {
    if (kadDialog) {
        kadDialog->setVisible(true);
    } else {
        kadDialog = new SetsKAD(this->mainWindow);
        kadDialog->show();
    }
    kadDialog->updateDialog();
}

void SetsMenu::updateKAD() {
    if (kadDialog) kadDialog->updateDialog();
}
