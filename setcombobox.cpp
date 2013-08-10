#include "setcombobox.h"
#include "base/globals.h"
#include "prop.h"

/*
 Note: another level is to explicitly
 show _dead_, not _disabled_, sets as disabled
 on the combobox. This may lead to creating a model
 for the combobox, but that is fine...
 */



SetComboBox::SetComboBox(bool a) :
    QComboBox()
{
    add = a;
    if (add) {
        this->addItem("-- All live sets --");
    }
    for (int i=0;i<MAXPLOT;i++) {
        this->addItem("");
    }
    updateSets();

    SetsSender::add(this);
    this->setMinimumWidth(100);
}

void SetComboBox::updateSets() {
    for (int i=0;i<MAXPLOT;i++) {
        if (g[cg].p[i].active == OFF && g[cg].p[i].deact == 0) {
            this->setItemText(i+add, QString("~: ") + g[cg].l.str[i].s);
        } else {
            this->setItemText(i+add, QString::number(i) + ": " + g[cg].l.str[i].s);
        }
    }
}
