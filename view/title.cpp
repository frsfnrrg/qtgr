#include "view/title.h"
#include "base/globals.h"
#include "menu.h"

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
    if (showDialog(propertiesDialog)) return;
    propertiesDialog = new ViewTitleProperties(mainWindow);
    loadDialog(propertiesDialog);
}

ViewTitleProperties::ViewTitleProperties(MainWindow* mw) :
    Dialog(mw, "Titling Properties")
{
    QHBoxLayout* layout = new QHBoxLayout();

    {
        tsize = new QDoubleSpinBox();
        tsize->setMinimum(0.0);
        tsize->setDecimals(3);
        tsize->setSingleStep(0.1);
        tfont = new QComboBox();
        tcolor = new QComboBox();

        QGridLayout* tl = new QGridLayout();

        tl->addWidget(new QLabel(tr("Title")), 0, 0, 1, 2);

        tl->setRowMinimumHeight(1, 12);
        tl->addWidget(new QLabel(tr("Font")), 2, 0);
        tl->addWidget(tfont, 2, 1);

        tl->setRowMinimumHeight(3, 5);
        tl->addWidget(new QLabel(tr("Size")), 4, 0);
        tl->addWidget(tsize, 4, 1);

        tl->setRowMinimumHeight(5, 5);
        tl->addWidget(new QLabel(tr("Color")), 6, 0);
        tl->addWidget(tcolor, 6, 1);

        layout->addLayout(tl);
    }
    layout->addSpacing(10);
    {
        ssize = new QDoubleSpinBox();
        ssize->setMinimum(0.0);
        ssize->setDecimals(3);
        ssize->setSingleStep(0.1);
        sfont = new QComboBox();
        scolor = new QComboBox();

        QGridLayout* sl = new QGridLayout();

        sl->addWidget(new QLabel(tr("Subtitle")), 0, 0, 1, 2);

        sl->setRowMinimumHeight(1, 12);
        sl->addWidget(new QLabel(tr("Font")), 2, 0);
        sl->addWidget(sfont, 2, 1);

        sl->setRowMinimumHeight(3, 5);
        sl->addWidget(new QLabel(tr("Size")), 4, 0);
        sl->addWidget(ssize, 4, 1);

        sl->setRowMinimumHeight(5, 5);
        sl->addWidget(new QLabel(tr("Color")), 6, 0);
        sl->addWidget(scolor, 6, 1);

        layout->addLayout(sl);
    }
    layout->addStretch();

    setDialogLayout(layout);
}

void ViewTitleProperties::updateDialog() {
    tsize->setValue(g[cg].labs.title.charsize);
    ssize->setValue(g[cg].labs.stitle.charsize);
}


void ViewTitleProperties::applyDialog() {
    g[cg].labs.title.charsize = tsize->value();
    g[cg].labs.stitle.charsize = ssize->value();

    drawgraph();
}
