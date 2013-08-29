#include "transform/integration.h"
#include "base/globals.h"
#include "choosers.h"
#include "prop.h"
#include "tools.h"
#include "tools/options.h"

TransformIntegration::TransformIntegration(MainWindow* mainWin) :
    Dialog(mainWin, "Integration")
{
    resultL = new QLabel(".....");

    setNumber = new SetComboBox();
    connect(setNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    integrationType = new QComboBox();
    integrationType->addItem(tr("Result"));
    integrationType->addItem(tr("Result and plot"));

    resultLabel = makeLabel("Result");
    typeLabel = makeLabel("Type:");

    // layout
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(makeLabel("Set:"),0,0);
    layout->addWidget(setNumber,0,1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(typeLabel,2,0);
    layout->addWidget(integrationType,2,1);

    layout->setRowMinimumHeight(3, 8);

    layout->addWidget(resultLabel, 4,0);
    layout->addWidget(resultL, 4, 1);

    this->setDialogLayout(layout);
}

void TransformIntegration::updateDialog() {
    resultL->setText(".....");
    int setno = setNumber->currentIndex();
    bool null = g[cg].p[setno].active == OFF && g[cg].p[setno].deact == 0;
    integrationType->setDisabled(null);
    resultL->setDisabled(null);
    resultLabel->setDisabled(null);
    typeLabel->setDisabled(null);
}

void TransformIntegration::applyDialog() {
    int setno, itype;

    setno = setNumber->currentIndex();
    if (g[cg].p[setno].active == OFF && g[cg].p[setno].deact == 0) {
        return;
    }

    // like so
    if (integrationType->currentIndex() == 0) {
        itype = 1;
    } else {
        itype = 0;
    }

    double result;
    result = do_int(setno, itype);
    resultL->setText(QString::number(result));

    // recognized double redraw: in both
    if (itype == 0 && ToolsOptions::isRescaleOnTransform()) {
        mainWindow->toolsMenu->autoScale();
    }

    SetsSender::send();
}
