#include "transform/differentiation.h"
#include "choosers.h"
#include "prop.h"
#include "tools.h"
#include "tools/options.h"
#include "mainwindow.h"

#include "base/globals.h"

#include <QGridLayout>
#include <QLabel>

TransformDifferentiation::TransformDifferentiation(MainWindow* mainWin) :
    Dialog(mainWin, "Differentiate")
{
    SetsSender::addViaDialog(this);

    setNumber = new SetComboBox();
    connect(setNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    destination = new QComboBox();
    destination->addItem(tr("New"));
    destination->addItem(tr("Same"));
    destination->setCurrentIndex(0);

    diffType = new QComboBox();
    diffType->addItem(tr("Centered"));
    diffType->addItem(tr("Forward"));
    diffType->addItem(tr("Backward"));
    diffType->setCurrentIndex(0);

    diffTypeLabel = makeLabel("Difference");
    destinationLabel = makeLabel("Target");

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(makeLabel("Set"), 0,0);
    layout->addWidget(setNumber, 0, 1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(destinationLabel, 2,0);
    layout->addWidget(destination, 2, 1);

    layout->setRowMinimumHeight(3, 8);

    layout->addWidget(diffTypeLabel, 4,0);
    layout->addWidget(diffType, 4, 1);

    layout->setColumnMinimumWidth(1, 150);

    this->setDialogLayout(layout);
}

void TransformDifferentiation::updateDialog() {
    int setno = setNumber->currentIndex();
    bool null = !isactive_set(cg, setno);
    diffType->setDisabled(null);
    destination->setDisabled(null);
    diffTypeLabel->setDisabled(null);
    destinationLabel->setDisabled(null);
}

void TransformDifferentiation::applyDialog() {
    int setno, itype;
    setno = setNumber->currentIndex();

    switch (diffType->currentIndex()) {
    case 0:
        itype = 2;
        break;
    case 1:
        itype = 0;
        break;
    case 2:
        itype = 1;
        break;
    default:
        return;
    }

    do_differ(setno, itype);

    // recognized double redraw: in both
    if (ToolsOptions::isRescaleOnTransform()) {
        mainWindow->toolsMenu->autoScale();
    } else {
        drawgraph();
    }

    SetsSender::send();
}

