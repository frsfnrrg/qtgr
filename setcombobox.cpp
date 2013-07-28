#include "setcombobox.h"
#include "base/globals.h"

LegendSender* SetComboBox::legendSender = NULL;

void LegendSender::sendUpdate() {
    emit updateLegends();
}

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
