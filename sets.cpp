#include "sets.h"

SetsMenu::SetsMenu(MainWindow* mwin) :
    Menu(mwin, "Sets", true)
{
    kadDialog = NULL;
    editDialog = NULL;
    mcsDialog = NULL;
    joinDialog = NULL;
    splitDialog = NULL;

    createActions();

    populateMenu(this);
}

void SetsMenu::createActions() {
    kadAct = makeAction("Kill/(De)Activate",
                        "Remove, enable, or disable a set",
                        "", SLOT(kad()));

    editAct = makeAction("Edit",
                         "Edit the points, type, and more of a set",
                         "", SLOT(edit()));

    mcsAct = makeAction("Reorder sets",
                                 "Rearrange sets; move them; copy them; swap them",
                                 "", SLOT(mcs()));

    splitAct = makeAction("Split",
                          "Divide set",
                          "", SLOT(split()));

    joinAct = makeAction("Join",
                         "Join sets",
                         "", SLOT(join()));
}

void SetsMenu::populateMenu(QMenu* q) {
    q->addAction(kadAct);
    q->addAction(editAct);
    q->addSeparator();
    q->addAction(mcsAct);
    q->addSeparator();
    q->addAction(splitAct);
    q->addAction(joinAct);
}

QToolBar* SetsMenu::createToolBar() {
    QToolBar* q = new QToolBar(title());
    q->addAction(kadAct);
    q->addAction(editAct);
    q->addSeparator();
    q->addAction(mcsAct);
    q->addSeparator();
    q->addAction(splitAct);
    q->addAction(joinAct);
    return q;
}

void SetsMenu::edit() {
    if (showDialog(editDialog)) return;
    editDialog = new SetsEdit(mainWindow);
    loadDialog(editDialog);
}

void SetsMenu::kad() {
    if (showDialog(kadDialog)) return;
    kadDialog = new SetsKAD(mainWindow);
    loadDialog(kadDialog);
}

void SetsMenu::mcs() {
    if (showDialog(mcsDialog)) return;
    mcsDialog = new SetsMCS(mainWindow);
    loadDialog(mcsDialog);
}

void SetsMenu::join() {
    // FILL ME
}

void SetsMenu::split() {
    // FILL ME
}
