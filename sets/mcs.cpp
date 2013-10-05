#include "sets/mcs.h"
#include "choosers.h"
#include "prop.h"
#include "base/globals.h"

SetsMCS::SetsMCS(MainWindow* mainWin) :
    Dialog(mainWin, "Move, Copy, Swap")
{
    setNumber = new SetComboBox();
    connect(setNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    QButtonGroup* choices = new QButtonGroup();
    moveChoice = new QRadioButton(tr("Move"));
    copyChoice = new QRadioButton(tr("Copy"));
    swapChoice = new QRadioButton(tr("Swap"));
    choices->addButton(moveChoice);
    choices->addButton(copyChoice);
    choices->addButton(swapChoice);
    swapChoice->setChecked(true);

    targetNumber = new SetComboBox();
    connect(targetNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTarget()));
    targetNumberLabel = new QLabel(tr("To"));

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(new QLabel(tr("From")), 0, 0);
    layout->addWidget(setNumber, 0, 1);
    layout->setRowMinimumHeight(1, 8);
    layout->addWidget(targetNumberLabel, 2, 0);
    layout->addWidget(targetNumber, 2, 1);

    layout->setRowMinimumHeight(3, 8);

    layout->addWidget(moveChoice, 4, 1, 1, 1);
    layout->setRowMinimumHeight(5, 2);
    layout->addWidget(copyChoice, 6, 1, 1, 1);
    layout->setRowMinimumHeight(7, 2);
    layout->addWidget(swapChoice, 8, 1, 1, 1);

    layout->setColumnMinimumWidth(1, 150);
    layout->setColumnMinimumWidth(0, 100);

    this->setDialogLayout(layout);

    SetsSender::add(this);
}

void SetsMCS::updateSets() {
    updateTarget();
}

void SetsMCS::updateDialog() {
    updateTarget();
}

void SetsMCS::updateTarget() {
    // i.e, change label to show "(Overwrites)"
    int cs = targetNumber->currentIndex();
    if (cs == setNumber->currentIndex()) {
        moveChoice->setText(tr("Move (No-op)"));
        copyChoice->setText(tr("Copy (No-op)"));
        swapChoice->setText(tr("Swap (No-op)"));
    } else {
        if (g[cg].p[cs].active == ON || g[cg].p[cs].deact == 1) {
            moveChoice->setText(tr("Move (Overwrites)"));
            copyChoice->setText(tr("Copy (Overwrites)"));
        } else {
            moveChoice->setText(tr("Move"));
            copyChoice->setText(tr("Copy"));
        }
        swapChoice->setText(tr("Swap"));
    }
}

void SetsMCS::applyDialog() {
    int from, to;
    from = setNumber->currentIndex();
    to = targetNumber->currentIndex();
    if (moveChoice->isChecked()) {
        do_moveset(cg, from, cg, to);
    } else if (copyChoice->isChecked()) {
        do_copyset(cg, from, cg, to);
    } else {
        do_swapset(cg, from, cg, to);
    }

    drawgraph();
    SetsSender::send();
}
