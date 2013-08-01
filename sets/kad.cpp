#include "sets/kad.h"
#include "base/globals.h"
#include "setcombobox.h"

SetsKAD::SetsKAD(MainWindow* mainWin) :
    Dialog(mainWin, tr("Kill/(De)Activate Sets"))
{
    setNumber = new SetComboBox();
    connect(setNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    QButtonGroup* choices = new QButtonGroup();
    adChoice = new QRadioButton(tr("Activate"));
    killChoice = new QRadioButton(tr("Kill"));
    choices->addButton(adChoice);
    choices->addButton(killChoice);
    adChoice->setChecked(true);

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(new QLabel("Set:"), 0, 0);
    layout->addWidget(setNumber, 0, 1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(adChoice, 2, 0, 1, 2);
    layout->setRowMinimumHeight(3, 2);
    layout->addWidget(killChoice, 4, 0, 1, 2);

    this->setDialogLayout(layout);
}

void SetsKAD::updateDialog() {
    // TODO: update when a new set is read..
    int gno = cg;
    int cset = setNumber->currentIndex();
    printf("%i: %i %i\n", cset, g[gno].p[cset].deact, g[gno].p[cset].active);
    if (isactive(gno, cset)) {
        if (g[gno].p[cset].deact == 0) {
            adChoice->setText(tr("Deactivate"));
        } else {
            adChoice->setText(tr("Activate"));
        }
        adChoice->setEnabled(true);
        killChoice->setEnabled(true);
    } else {
        adChoice->setEnabled(false);
        killChoice->setEnabled(false);
    }
}

void SetsKAD::applyDialog() {
    int gno = cg;
    int cset = setNumber->currentIndex();

    if (!isactive(gno,cset)) {
        return;
    }

    if (adChoice->isChecked()) {
        if (g[gno].p[cset].deact == 0) {
            g[gno].p[cset].deact = 1;
            set_prop(gno, SET, SETNUM, cset, ACTIVE, OFF, 0);
            adChoice->setText(tr("Activate"));
        } else {
            g[gno].p[cset].deact = 0;
            set_prop(gno, SET, SETNUM, cset, ACTIVE, ON, 0);
            adChoice->setText(tr("Deactivate"));
        }
    } else {
        // default, hard kill; soft is 1
        do_kill(gno, cset, 0);

        adChoice->setEnabled(false);
        killChoice->setEnabled(false);
    }

    drawgraph();
}
