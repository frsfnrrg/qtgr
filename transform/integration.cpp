#include "transform/integration.h"

TransformIntegration::TransformIntegration(MainWindow* mainWin) :
    Dialog(mainWin)
{
    this->setWindowTitle(tr("Transforms: Integration"));

    integrationType = new QComboBox();
    integrationType->addItem(tr("Result"));
    integrationType->addItem(tr("Result and plot"));

    result = new QLabel("......");

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(new QLabel(tr("Select Type:"),0,0));
    layout->addWidget(integrationType,0,1);

    // spacer
    layout->addWidget(new QLabel(""),1,0,1,3);

    // if we really want to, use a nested, multilevel thingy.
    layout->addWidget(new QLabel(tr("Result")), 2,0);
    layout->addWidget(result, 2, 1);

    this->setLayout(layout);
}

void TransformIntegration::updateDialog() {
    printf("updating integration dialog\n");
}

void TransformIntegration::applyDialog() {
    printf("applying integration dialog\n");
}
