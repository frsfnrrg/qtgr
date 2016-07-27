#include "sets/join.h"
#include "choosers.h"
#include "prop.h"
#include "base/globals.h"

#include <QButtonGroup>
#include <QLabel>
#include <QGridLayout>
#include <QRadioButton>

SetsJoin::SetsJoin(MainWindow* mainWin) :
    Dialog(mainWin, "Move, Copy, Swap")
{
    setLeft = new SetComboBox();
    setRight = new SetComboBox();
    connect(setLeft, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));
    connect(setRight, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));
    QButtonGroup* lr = new QButtonGroup();
    mergeLeft = new QRadioButton(tr("Merge left"));
    mergeRight = new QRadioButton(tr("Merge right"));
    lr->addButton(mergeLeft);
    lr->addButton(mergeRight);
    mergeLeft->setChecked(true);
    setTip(setLeft, "Set to be joined (on the left).");
    setTip(setRight,"Set to be joined (on the right).");
    setTip(mergeLeft, "Product replaces left set.");
    setTip(mergeRight, "Product replaces right set.");

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(setLeft, 0, 0);
    layout->addWidget(setRight, 0, 1);
    layout->addWidget(mergeLeft, 1, 0);
    layout->addWidget(mergeRight, 1, 1);

    this->setDialogLayout(layout);

    SetsSender::addViaDialog(this);
}

void SetsJoin::updateDialog() {
    bool cant = setLeft->currentIndex() == setRight->currentIndex() ||
            !isactive_set(cg, setLeft->currentIndex()) ||
            !isactive_set(cg, setRight->currentIndex());
    deactivate(cant);
}
void SetsJoin::applyDialog() {
    do_join_sets(cg, setLeft->currentIndex(), cg, setRight->currentIndex());
    // swap afterwards to set direction
    if (mergeLeft->isChecked()) {
        do_swapset(cg, setLeft->currentIndex(), cg, setRight->currentIndex());
    }
    drawgraph();
    SetsSender::send();
}
