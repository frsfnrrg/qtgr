#include "transform/evaluate.h"
#include "choosers.h"
#include "prop.h"
#include "tools.h"
#include "tools/options.h"
#include "mainwindow.h"

#include "base/globals.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>

TransformEvaluate::TransformEvaluate(MainWindow* mainWin) :
    Dialog(mainWin, "Evaluate")
{
    SetsSender::addViaDialog(this);

    setNumber = new SetComboBox();
    connect(setNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    destination = new QComboBox();
    destination->addItem(tr("New"));
    destination->addItem(tr("Same"));
    destination->setCurrentIndex(0);

    formulaBoxLabel = makeLabel("Formula");
    destinationLabel = makeLabel("Target");

    formulaBox = new QLineEdit();
    formulaBox->setMaxLength(MAX_STRING_LENGTH);

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(makeLabel("Set"), 0,0);
    layout->addWidget(setNumber, 0, 1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(destinationLabel, 2,0);
    layout->addWidget(destination, 2, 1);

    layout->setRowMinimumHeight(3, 8);

    layout->addWidget(formulaBoxLabel, 4,0);
    layout->addWidget(formulaBox, 4, 1);

    this->setDialogLayout(layout);
}

void TransformEvaluate::updateDialog() {
    int setno = setNumber->currentIndex();
    bool null = !isactive_set(cg, setno);
    formulaBox->setDisabled(null);
    destination->setDisabled(null);
    formulaBoxLabel->setDisabled(null);
    destinationLabel->setDisabled(null);
}

void TransformEvaluate::applyDialog() {
    int setno, loadto, graphto;

    setno = this->setNumber->currentIndex();

    graphto = cg;

    if (destination->currentIndex() == 0) {
        loadto = 1;
    } else {
        loadto = 0; // send to the next set
    }

    // Copy the string over to ensure it backing data isn't
    // erased during operation
    char fstr[MAX_STRING_LENGTH];
    strncpy(fstr, formulaBox->text().toLocal8Bit().data(), MAX_STRING_LENGTH);
    do_compute(setno, loadto, graphto, fstr);

    // recognized double redraw: in both
    if (ToolsOptions::isRescaleOnTransform()) {
        mainWindow->toolsMenu->autoScale();
    } else {
        drawgraph();
    }

    SetsSender::send();
}
