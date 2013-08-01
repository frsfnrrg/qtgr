#include "sets/sedit.h"
#include "base/globals.h"
#include "setcombobox.h"

SetsEdit::SetsEdit(MainWindow* mwin) :
    Dialog(mwin, "Edit Sets")
{
    setNumber = new SetComboBox();
    connect(setNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(new QLabel(tr("Set: ")), 0, 0);
    layout->addWidget(setNumber, 0, 1);

    this->setDialogLayout(layout);
}

void SetsEdit::updateDialog() {

}

void SetsEdit::applyDialog() {

}
