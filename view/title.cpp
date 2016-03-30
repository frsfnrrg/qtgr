#include "view/title.h"
#include "choosers.h"

#include "base/globals.h"

#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>

ViewTitle::ViewTitle(MainWindow* mainWin) :
    Dialog(mainWin, "Title", true)
{

    ttext = new QLineEdit();
    tsize = makeTextSizer();
    tfont = new FontComboBox();
    tcolor = new ColorComboBox();

    stext = new QLineEdit();
    ssize = makeTextSizer();
    sfont = new FontComboBox();
    scolor = new ColorComboBox();

    autoHook(ttext);
    autoHook(tsize);
    autoHook(tfont);
    autoHook(tcolor);
    autoHook(stext);
    autoHook(ssize);
    autoHook(sfont);
    autoHook(scolor);

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
    ttext->setFocus();
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
    if (g[cg].labs.title.s) free(g[cg].labs.title.s);
    int tlen = ttext->text().toUtf8().length();
    g[cg].labs.title.s = (char*)malloc(tlen+1);
    strncpy(g[cg].labs.title.s, ttext->text().toUtf8().constData(), tlen+1);

    if (g[cg].labs.stitle.s) free(g[cg].labs.stitle.s);
    int slen = stext->text().toUtf8().length();
    g[cg].labs.stitle.s = (char*)malloc(slen+1);
    strncpy(g[cg].labs.stitle.s, stext->text().toUtf8().constData(), slen+1);

    g[cg].labs.title.charsize = tsize->value();
    g[cg].labs.stitle.charsize = ssize->value();

    g[cg].labs.title.font = tfont->currentIndex();
    g[cg].labs.stitle.font = sfont->currentIndex();

    g[cg].labs.title.color = tcolor->currentIndex();
    g[cg].labs.stitle.color = scolor->currentIndex();

    drawgraph();
}
