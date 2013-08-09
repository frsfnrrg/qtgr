#include "transform/evaluate.h"
#include "base/globals.h"
#include "setcombobox.h"
#include "prop.h"
#include "tools.h"
#include "tools/options.h"

TransformEvaluate::TransformEvaluate(MainWindow* mainWin) :
    Dialog(mainWin, "Evaluate")
{
    // hmmm.. extract this into a static Dialog method?
    setNumber = new SetComboBox();
    connect(setNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    destination = new QComboBox();
    destination->addItem(tr("New"));
    destination->addItem(tr("Same"));
    destination->setCurrentIndex(0);

    formulaBox = new QLineEdit();

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(new QLabel(tr("Set")), 0,0);
    layout->addWidget(setNumber, 0, 1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(new QLabel(tr("Target")), 2,0);
    layout->addWidget(destination, 2, 1);

    layout->setRowMinimumHeight(3, 8);

    layout->addWidget(new QLabel("Formula"), 4,0);
    layout->addWidget(formulaBox, 4, 1);

    this->setDialogLayout(layout);
}

void TransformEvaluate::updateDialog() {

}

void TransformEvaluate::applyDialog() {
    int setno, loadto, graphto;
    char* fstr;

    setno = this->setNumber->currentIndex();

    graphto = cg;

    if (destination->currentIndex() == 0) {
        loadto = 1;
    } else {
        loadto = 0; // send to the next set
    }

    fstr = formulaBox->text().toLocal8Bit().data();

    do_compute(setno, loadto, graphto, fstr);

    // recognized double redraw: in both
    if (ToolsOptions::isRescaleOnTransform()) {
        mainWindow->toolsMenu->autoScale();
    }

    SetsSender::send();
}
