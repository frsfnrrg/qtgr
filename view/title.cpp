#include "view/title.h"
#include "base/globals.h"
#include "menu.h"
#include "choosers.h"

ViewTitle::ViewTitle(MainWindow* mainWin) :
    Dialog(mainWin, "Title")
{

    ttext = new QLineEdit();
    tsize = new QDoubleSpinBox();
    tsize->setMinimum(0.0);
    tsize->setDecimals(2);
    tsize->setSingleStep(0.1);
    tfont = new FontComboBox();
    tcolor = new ColorComboBox();

    stext = new QLineEdit();
    ssize = new QDoubleSpinBox();
    ssize->setMinimum(0.0);
    ssize->setDecimals(2);
    ssize->setSingleStep(0.1);
    sfont = new FontComboBox();
    scolor = new ColorComboBox();

    // divide using QFrame magic??

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(makeLabel("Title"), 0,0);
    layout->addWidget(ttext, 0, 1, 1, 5);

    layout->addWidget(makeLabel("Size"), 1, 0);
    layout->addWidget(tsize, 1, 1);
    layout->addWidget(makeLabel("Color"), 1, 2);
    layout->addWidget(tcolor, 1, 3);
    layout->addWidget(makeLabel("Font"), 1, 4);
    layout->addWidget(tfont, 1, 5);

    layout->setRowMinimumHeight(2, 8);

    layout->addWidget(makeLabel("Subtitle"), 3,0);
    layout->addWidget(stext, 3, 1, 1, 5);

    layout->addWidget(makeLabel("Size"), 4, 0);
    layout->addWidget(ssize, 4, 1);
    layout->addWidget(makeLabel("Color"), 4, 2);
    layout->addWidget(scolor, 4, 3);
    layout->addWidget(makeLabel("Font"), 4, 4);
    layout->addWidget(sfont, 4, 5);

    this->setDialogLayout(layout);
}

void ViewTitle::updateDialog() {
    int gno = cg;
    ttext->setText(g[gno].labs.title.s);
    stext->setText(g[gno].labs.stitle.s);

    tsize->setValue(g[gno].labs.title.charsize);
    ssize->setValue(g[gno].labs.stitle.charsize);

    tfont->setCurrentIndex(g[gno].labs.title.font);
    sfont->setCurrentIndex(g[gno].labs.stitle.font);

    tcolor->setCurrentIndex(g[gno].labs.title.color);
    scolor->setCurrentIndex(g[gno].labs.stitle.color);
}

void ViewTitle::applyDialog() {
    int gno = cg;

    strcpy((char*)g[gno].labs.title.s,ttext->text().toAscii().data());
    strcpy((char*)g[gno].labs.stitle.s,stext->text().toAscii().data());

    g[gno].labs.title.charsize = tsize->value();
    g[gno].labs.stitle.charsize = ssize->value();

    g[gno].labs.title.font = tfont->currentIndex();
    g[gno].labs.stitle.font = sfont->currentIndex();

    g[gno].labs.title.color = tcolor->currentIndex();
    g[gno].labs.stitle.color = scolor->currentIndex();

    drawgraph();
}
