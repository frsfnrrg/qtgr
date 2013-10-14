#include "view/text.h"
#include "base/globals.h"
#include "choosers.h"
#include "graphwidget.h"
#include "mainwindow.h"

ViewText::ViewText(MainWindow* mainWin) :
    Dialog(mainWin, "Free Strings", true)
{
    for (int i=0;i<MAXSTR;i++) {
        texts[i] = NULL;
    }

    placeTextButton = makeButton("Add New String", SLOT(placeText()));
    setButtonBold(placeTextButton);

    textsLayout = new QVBoxLayout();

    texts[0] = new ViewTextElement(this, 0);
    textsLayout->addWidget(texts[0]);

    QWidget* frame = new QWidget();
    frame->setLayout(textsLayout);

    QScrollArea* tscrBox = new QScrollArea();
    tscrBox->setWidgetResizable(true);
    tscrBox->setWidget(frame);



    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(placeTextButton);
    layout->addStrut(5);
    layout->addWidget(tscrBox);

    this->setDialogLayout(layout);
}

void ViewText::updateDialog() {
    ViewTextElement* elem;
    for (int i=0;i<MAXSTR;i++) {
        if (isactive_string(i) && !texts[i]) {
            texts[i] = new ViewTextElement(this, i);
            textsLayout->addWidget(texts[i]);
        } else if (texts[i] && !isactive_string(i)) {
            elem = texts[i];
            textsLayout->removeWidget(texts[i]);
            delete elem;
            texts[i] = NULL;
        }

        if (texts[i]) texts[i]->updateValues();
    }
}

void ViewText::applyDialog() {
    for (int i=0;i<MAXSTR;i++) {
        if (texts[i]) texts[i]->applyValues();
    }
    drawgraph();
}

class StringPlacingThingy : public MouseCallBack
{
private:
    ViewText* view;
    int id;
public:
    void set(ViewText* t, QString txt, int n) {
        view = t;
        id = n;
        view->mainWindow->gwidget->mouseClickCall = this;
        view->mainWindow->gwidget->setCursor(Qt::CrossCursor);
        view->mainWindow->statusBar()->showMessage(txt);
    }

    void mouse(int x, int y, int w, int h) {
        view->mainWindow->gwidget->mouseClickCall = NULL;
        view->mainWindow->gwidget->unsetCursor();
        view->mainWindow->statusBar()->clearMessage();
        view->addText(id, double(x)/double(w), 1.0 - double(y)/double(h));
    }
} stringPlacer;

void ViewText::placeText() {
    int i = next_string();
    pstr[i].active = ON;
    texts[i] = new ViewTextElement(this, i);
    textsLayout->addWidget(texts[i]);
    stringPlacer.set(this, tr("Click to place string"), i);
}

void ViewText::addText(int id, float x, float y) {
    texts[id]->xCoord->setValue(x);
    texts[id]->yCoord->setValue(y);

    pstr[id].x = x;
    pstr[id].y = y;

    // focus on text area?

    drawgraph();
}



void ViewText::relocateText(int id) {

}

void ViewText::setText(int id, float x, float y) {

}

ViewTextElement::ViewTextElement(ViewText* parent, int id) :
    QFrame()
{
    par = parent;
    num = id;

    textArea = new LongTextEdit();

    xCoord = new DoubleSpinBox();
    xCoord->setRange(0, 1.0);
    xCoord->setSingleStep(0.05);
    xCoord->setDecimals(3);

    yCoord = new DoubleSpinBox();
    yCoord->setRange(0, 1.0);
    yCoord->setSingleStep(0.05);
    yCoord->setDecimals(3);

    relocateButton = new QPushButton(tr("Move"));
    setButtonBold(relocateButton);
    connect(relocateButton, SIGNAL(clicked()), this, SLOT(reloc()));

    moreButton = new QPushButton(tr("More..."));

    deleteButton = new QPushButton("X");

    xLabel = makeQLabel(this, "X");
    yLabel = makeQLabel(this, "Y");

    par->autoHook(xCoord);
    par->autoHook(yCoord);
    par->autoHook(textArea);

    layout = new QGridLayout();

    layout->setColumnMinimumWidth(0, 3);

    layout->addWidget(textArea, 0, 1, 3, 1);

    layout->setColumnMinimumWidth(2, 12);

    layout->addWidget(xLabel, 0, 3);
    layout->addWidget(yLabel, 1, 3);

    layout->addWidget(xCoord, 0, 4);
    layout->addWidget(yCoord, 1, 4);

    layout->setColumnMinimumWidth(5, 8);

    layout->addWidget(relocateButton, 0, 6);

    layout->addWidget(moreButton, 1, 6);

    // need a good placement, so nobody accidentally clicks this...
    layout->addWidget(deleteButton, 2, 6, Qt::AlignVCenter | Qt::AlignRight);

    this->setMinimumWidth(400);
    this->setMinimumHeight(75);
    this->setFrameShadow(QFrame::Plain);
    this->setFrameShape(QFrame::NoFrame);

    this->setLayout(layout);
}

ViewTextElement::~ViewTextElement() {
    delete textArea;
    delete xCoord;
    delete yCoord;
    delete relocateButton;
    delete layout;
    delete moreButton;
    delete xLabel;
    delete yLabel;
    delete deleteButton;
}

void ViewTextElement::reloc() {
    par->relocateText(num);
}

void ViewTextElement::applyValues() {
    // use sizeof for field
    strncpy((char*)pstr[num].s, textArea->toPlainText().toAscii().data(), MAXSTRLEN+1);
    pstr[num].x = xCoord->value();
    pstr[num].y = yCoord->value();
}

void ViewTextElement::updateValues() {
    textArea->setText(QString(pstr[num].s));
    xCoord->setValue(pstr[num].x);
    yCoord->setValue(pstr[num].y);
}



