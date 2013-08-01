#include "view/title.h"
#include "base/globals.h"

ViewTitle::ViewTitle(MainWindow* mainWin) :
    Dialog(mainWin, "Title")
{
    propertiesDialog = NULL;

    titleField = new QLineEdit();

    subtitleField = new QLineEdit();

    propertiesButton = new QPushButton(tr("Properties"));
    connect(propertiesButton, SIGNAL(clicked()), this, SLOT(properties()));

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(new QLabel(tr("Title")), 0,0);
    layout->addWidget(titleField, 0, 1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(new QLabel(tr("Subtitle")), 2,0);
    layout->addWidget(subtitleField, 2, 1);

    layout->setRowMinimumHeight(3, 8);

    layout->addWidget(propertiesButton, 4, 0);

    layout->setColumnMinimumWidth(1, 200);

    this->setDialogLayout(layout);
}

void ViewTitle::updateDialog() {
    int gno = cg;
    titleField->setText(g[gno].labs.title.s);
    subtitleField->setText(g[gno].labs.stitle.s);
}

void ViewTitle::applyDialog() {
    int gno = cg;

    strcpy((char*)g[gno].labs.title.s,titleField->text().toAscii().data());
    strcpy((char*)g[gno].labs.stitle.s,subtitleField->text().toAscii().data());

    drawgraph();
}

void ViewTitle::properties() {

}

void ViewTitle::updateProperties() {

}

void ViewTitle::applyProperties() {

}

void ViewTitle::doneProperties() {

}
