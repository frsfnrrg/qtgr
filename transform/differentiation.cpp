#include "transform/differentiation.h"
#include "base/globals.h"
#include "setcombobox.h"
#include "prop.h"
#include "tools.h"
#include "tools/options.h"

TransformDifferentiation::TransformDifferentiation(MainWindow* mainWin) :
    Dialog(mainWin, "Differentiate")
{
    // hmmm.. extract this into a static Dialog method?
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

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(new QLabel(tr("Set")), 0,0);
    layout->addWidget(setNumber, 0, 1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(new QLabel(tr("Target")), 2,0);
    layout->addWidget(destination, 2, 1);

    layout->setRowMinimumHeight(3, 8);

    layout->addWidget(new QLabel(tr("Difference Type")), 4,0);
    layout->addWidget(diffType, 4, 1);

    layout->setColumnMinimumWidth(1, 150);

    this->setDialogLayout(layout);
}

void TransformDifferentiation::updateDialog() {
    printf("updating diff dialog\n");
}

void TransformDifferentiation::applyDialog() {
    printf("applying diff dialog\n");

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
    }

    SetsSender::send();
}

