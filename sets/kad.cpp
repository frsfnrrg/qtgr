#include "sets/kad.h"
#include "choosers.h"
#include "prop.h"

#include "base/globals.h"

#include <QButtonGroup>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>

SetsKAD::SetsKAD(MainWindow* mainWin) :
    Dialog(mainWin, "Kill/(De)Activate Sets")
{
    setNumber = new SetComboBox(true);
    connect(setNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    QButtonGroup* choices = new QButtonGroup();
    actChoice = new QRadioButton(tr("Activate"));
    deactChoice = new QRadioButton(tr("Deactivate"));
    killChoice = new QRadioButton(tr("Kill"));
    choices->addButton(actChoice);
    choices->addButton(deactChoice);
    choices->addButton(killChoice);
    actChoice->setChecked(true);

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(new QLabel(tr("Set")), 0, 0);
    layout->addWidget(setNumber, 0, 1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(actChoice, 2, 0, 1, 2);
    layout->setRowMinimumHeight(3, 2);
    layout->addWidget(deactChoice, 4, 0, 1, 2);
    layout->setRowMinimumHeight(5, 2);
    layout->addWidget(killChoice, 6, 0, 1, 2);

    this->setDialogLayout(layout);

    SetsSender::addViaDialog(this);
}

void shift_to_first(QRadioButton* a, QRadioButton* b) {
    if (b->isChecked()) {
        b->setChecked(false);
        a->setChecked(true);
    }
    b->setEnabled(false);
    a->setEnabled(true);
}

void SetsKAD::updateDialog() {
    // TODO: update when a new set is read..
    int gno = cg;
    int cset = setNumber->currentIndex() - 1;

    if (cset == -1) {
        actChoice->setEnabled(true);
        deactChoice->setEnabled(true);
        killChoice->setEnabled(true);
        return;
    }

    if (g[gno].p[cset].active == FALSE && g[gno].p[cset].deact == 0) {
        actChoice->setEnabled(false);
        deactChoice->setEnabled(false);
        killChoice->setEnabled(false);
        return;
    }

    if (g[gno].p[cset].deact == 0) {
        shift_to_first(deactChoice, actChoice);
    } else {
        shift_to_first(actChoice, deactChoice);
    }
    killChoice->setEnabled(true);
}


void SetsKAD::applyDialog() {
    int gno = cg;
    int cset = setNumber->currentIndex() - 1;
    if (cset == -1) {
        if (deactChoice->isChecked()) {
            for (cset=0;cset<g[gno].maxplot;cset++) {
                if (g[gno].p[cset].active == TRUE) {
                    g[gno].p[cset].deact = 1;
                    g[gno].p[cset].active = FALSE;
                }
            }
        } if (actChoice->isChecked()) {
            for (cset=0;cset<g[gno].maxplot;cset++) {
                if (g[gno].p[cset].active == FALSE && g[gno].p[cset].deact == 1) {
                    g[gno].p[cset].deact = 0;
                    g[gno].p[cset].active = TRUE;
                }
            }
        } else {
            for (cset=0;cset<g[gno].maxplot;cset++) {
                if (g[gno].p[cset].active == TRUE || g[gno].p[cset].deact == 1) {
                    do_kill(gno, cset, 0);
                }
            }
        }
        SetsSender::send();

        drawgraph();
        return;
    }

    if (g[gno].p[cset].active == FALSE && g[gno].p[cset].deact == 0) {
        return;
    }

    if (deactChoice->isChecked()) {
        g[gno].p[cset].deact = 1;
        g[gno].p[cset].active = FALSE;
        shift_to_first(actChoice, deactChoice);
    } else if (actChoice->isChecked()) {
        g[gno].p[cset].deact = 0;
        g[gno].p[cset].active = TRUE;
        shift_to_first(deactChoice, actChoice);
    } else {
        // default, hard kill; soft is 1
        do_kill(gno, cset, 0);
    }
    SetsSender::send();

    drawgraph();
}
