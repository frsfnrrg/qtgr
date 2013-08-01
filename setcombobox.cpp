#include "setcombobox.h"
#include "base/globals.h"

LegendSender* SetComboBox::legendSender = NULL;

void LegendSender::sendUpdate() {
    emit updateLegends();
}

/*
 Note: another level is to explicitly
 show _dead_, not _disabled_, sets as disabled
 on the combobox. This may lead to creating a model
 for the combobox, but that is fine...
 */

SetComboBox::SetComboBox() :
    QComboBox()
{
    for (int i=0;i<MAXPLOT;i++) {
        this->addItem(QString::number(i) + ": " + g[cg].l.str[i].s);
    }

    if (!SetComboBox::legendSender) {
        SetComboBox::legendSender = new LegendSender();
    }
    connect(SetComboBox::legendSender,SIGNAL(updateLegends()),
            this, SLOT(updateSetChooserLabels()));
    this->setMinimumWidth(100);
}

void SetComboBox::updateSetChooserLabels() {
    for (int i=0;i<MAXPLOT;i++) {
        this->setItemText(i, QString::number(i) + ": " + g[cg].l.str[i].s);
    }
}

void SetComboBox::sendUpdate() {
    if (!SetComboBox::legendSender) {
        SetComboBox::legendSender = new LegendSender();
    }
    SetComboBox::legendSender->sendUpdate();
}
