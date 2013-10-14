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
    QVBoxLayout* exp = new QVBoxLayout();
    exp->addLayout(textsLayout, 0);
    exp->addStretch(1);
    frame->setLayout(exp);

    scrollBox = new QScrollArea();
    scrollBox->setWidgetResizable(true);
    scrollBox->setWidget(frame);
    scrollBox->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    scrollBox->setMinimumWidth(500);
    scrollBox->setMinimumHeight(100);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(placeTextButton);
    layout->addStrut(5);
    layout->addWidget(scrollBox);

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
    // next string takes the next not enabled or not empty string
    int i = next_string();
    if (!texts[i]) {// if the string is empty, make it!
        pstr[i].active = ON;
        texts[i] = new ViewTextElement(this, i);
        textsLayout->addWidget(texts[i]);
    }
    // this doesn't do anything?
    scrollToField(i);
    stringPlacer.set(this, tr("Click to place string"), i);
}

void ViewText::addText(int id, float x, float y) {
    if (texts[id]) {
        texts[id]->setLocation(x,y,true);
    }

    drawgraph();
}

class StringRelocater : public MouseCallBack
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
        view->setText(id, double(x)/double(w), 1.0 - double(y)/double(h));
    }
} stringRelocater;

void ViewText::relocateText(int id) {
    stringRelocater.set(this, tr("Click to move string"), id);
}

void ViewText::setText(int id, float x, float y) {
    if (texts[id]) {
        texts[id]->setLocation(x,y);

        drawgraph();
    }
}

void ViewText::deleteText(int id) {
    kill_string(id);
    if (texts[id]) {
        textsLayout->removeWidget(texts[id]);
        delete texts[id];
        texts[id] = NULL;
    }

    drawgraph();
}

void ViewText::scrollToField(int id) {
    if (texts[id]) {
        QPoint loc = texts[id]->geometry().center();
        scrollBox->ensureVisible(loc.x(), loc.y());
    }
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

    deleteButton = new QPushButton(tr("Kill"));
    setButtonBold(deleteButton);
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(del()));

    xLabel = makeQLabel(this, "X");
    yLabel = makeQLabel(this, "Y");

    par->autoHook(xCoord);
    par->autoHook(yCoord);
    par->autoHook(textArea);

    rlayout = new QGridLayout();

    rlayout->addWidget(xLabel, 0, 0);
    rlayout->addWidget(yLabel, 1, 0);

    rlayout->addWidget(xCoord, 0, 1);
    rlayout->addWidget(yCoord, 1, 1);

    rlayout->addWidget(relocateButton, 2, 0, 1, 2);

    rlayout->setColumnMinimumWidth(2, 8);

    rlayout->addWidget(moreButton, 0, 3);

    // need a good placement, so nobody accidentally clicks this...
    rlayout->addWidget(deleteButton, 2, 3, Qt::AlignVCenter | Qt::AlignRight);

    rlayout->setRowStretch(0, 1);
    rlayout->setRowStretch(1, 1);
    rlayout->setRowStretch(2, 1);
    rlayout->setRowStretch(3, 2);

    layout = new QHBoxLayout();
    layout->addWidget(textArea);
    layout->addSpacing(8);
    layout->addLayout(rlayout);

    this->setMinimumWidth(400);
    this->setMinimumHeight(rlayout->sizeHint().height());
    this->setFrameShadow(QFrame::Plain);
    this->setFrameShape(QFrame::NoFrame);

    this->setLayout(layout);
}

ViewTextElement::~ViewTextElement() {
    delete textArea;
    delete xCoord;
    delete yCoord;

    delete xLabel;
    delete yLabel;

    delete relocateButton;
    delete moreButton;
    delete deleteButton;

    // the order of these two matters: find out why?
    delete rlayout;
    delete layout;
}

void ViewTextElement::setLocation(double x, double y, bool focus) {
    xCoord->setValue(x);
    yCoord->setValue(y);

    pstr[num].x = x;
    pstr[num].y = y;

    if (focus) {
        par->raise();
        par->scrollToField(num);
        textArea->activateWindow();
        textArea->setFocus();
    }
}

void ViewTextElement::reloc() {
    par->relocateText(num);
}

void ViewTextElement::del() {
    par->deleteText(num);
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



