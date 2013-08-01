#include "transform/integration.h"
#include "base/globals.h"
#include "setcombobox.h"
#include "prop.h"

TransformIntegration::TransformIntegration(MainWindow* mainWin) :
    Dialog(mainWin, "Integration")
{
    printf("creating integration dialog\n");

    resultL = new QLabel("Volia!");
    resultL->setText(".....");

    setNumber = new SetComboBox();
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
    resultL->setText(".....");
}

void TransformIntegration::applyDialog() {
    printf("applying integration dialog\n");

    int setno, itype;

    setno = setNumber->currentIndex();

    // like so
    if (integrationType->currentIndex() == 0) {
        itype = 1;
    } else {
        itype = 0;
    }

    double result;
    result = do_int(setno, itype);
    resultL->setText(QString::number(result));

    SetsSender::send();
}
