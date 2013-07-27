#include "transform/integration.h"

TransformIntegration::TransformIntegration(MainWindow* mainWin) :
    Dialog(mainWin, tr("Transforms: Integration"))
{
    printf("creating integration dialog\n");

    resultL = new QLabel("Volia!");
    resultL->setText(".....");

    setNumber = new QComboBox();
    for (int i=0;i<TransformIntegration::maxsets;i++) {
        setNumber->addItem(QString::number(i));
    }
    connect(setNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    integrationType = new QComboBox();
    integrationType->addItem(tr("Result"));
    integrationType->addItem(tr("Result and plot"));

    // layout
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(new QLabel(tr("Select Set:")),0,0);
    layout->addWidget(setNumber,0,1);

    layout->addWidget(new QLabel(""),1,0,1,3);

    layout->addWidget(new QLabel(tr("Select Type:")),2,0);
    layout->addWidget(integrationType,2,1);

    layout->addWidget(new QLabel(""),3,0,1,3);

    layout->addWidget(new QLabel(tr("Result")), 4,0);
    layout->addWidget(resultL, 4, 1);

    this->setDialogLayout(layout);
}

void TransformIntegration::updateDialog() {
    printf("updating integration dialog\n");
}

void TransformIntegration::applyDialog() {
    printf("applying integration dialog\n");
}
