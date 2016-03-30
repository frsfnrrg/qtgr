#include "view/text.h"
#include "base/globals.h"
#include "choosers.h"
#include "graphwidget.h"
#include "mainwindow.h"
#include "util.h"

#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QGroupBox>

ViewText::ViewText(MainWindow* mainWin) :
    Dialog(mainWin, "Free Strings", true)
{
    propsDialog = NULL;

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
            if (propsDialog) {
                propsDialog->addItem(i);
            }
        } else if (texts[i] && !isactive_string(i)) {
            elem = texts[i];
            if (propsDialog) {
                propsDialog->removeItem(textsLayout->indexOf(texts[i]));
            }
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

    void mouse(double vx, double vy) {
        view->mainWindow->gwidget->mouseClickCall = NULL;
        view->mainWindow->gwidget->unsetCursor();
        view->mainWindow->statusBar()->clearMessage();
        view->addText(id, vx, vy);
    }
} stringPlacer;

void ViewText::placeText() {
    // next string takes the next not enabled or not empty string
    int i = next_string();
    if (!texts[i]) {// if the string is empty, make it!
        pstr[i].active = TRUE;
        texts[i] = new ViewTextElement(this, i);
        textsLayout->addWidget(texts[i]);
        if (propsDialog) propsDialog->addItem(i);
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

    void mouse(double vx, double vy) {
        view->mainWindow->gwidget->mouseClickCall = NULL;
        view->mainWindow->gwidget->unsetCursor();
        view->mainWindow->statusBar()->clearMessage();
        view->setText(id, vx, vy);
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
        if (propsDialog) {
            propsDialog->removeItem(textsLayout->indexOf(texts[id]));
        }
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

void ViewText::loadTextProperties(int num) {
    if (showDialog(propsDialog)) return;

    propsDialog = new ViewTextProperties(mainWindow);
    for (int i=0;i<textsLayout->count();i++) {
        propsDialog->addItem( ( (ViewTextElement*) textsLayout->itemAt(i)->widget())->num );
    }
    propsDialog->setItem(textsLayout->indexOf(texts[num]));
    loadDialog(propsDialog);
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
    connect(moreButton, SIGNAL(clicked()), this, SLOT(prop()));

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

void ViewTextElement::prop() {
    par->loadTextProperties(num);
}

void ViewTextElement::applyValues() {
    // use sizeof for field
    if (pstr[num].s) free(pstr[num].s);
    int len = textArea->toPlainText().toUtf8().length();
    pstr[num].s = (char*)malloc(len);
    strncpy(pstr[num].s, textArea->toPlainText().toUtf8().constData(), len);
    pstr[num].x = xCoord->value();
    pstr[num].y = yCoord->value();
}

void ViewTextElement::updateValues() {
    textArea->setText(QString(pstr[num].s));
    xCoord->setValue(pstr[num].x);
    yCoord->setValue(pstr[num].y);
}

ViewTextProperties::ViewTextProperties(MainWindow* mainWin) :
    Dialog(mainWin, "String Properties", true)
{
    tNum = new QComboBox();
    tNum->setMinimumWidth(85);
    connect(tNum, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    tApplyTextStyle = makeButton("Apply text style to all", SLOT(spreadTextStyle()));
    setButtonBold(tApplyTextStyle);

    tFont = new FontComboBox();
    tColor = new ColorComboBox();
    tSize = new DoubleRangeSelector(0.0,5.0,2,0.2);

    tJust = new QComboBox();
    tJust->addItem(tr("Left"));
    tJust->addItem(tr("Right"));
    tJust->addItem(tr("Center"));

    tAngle = new IntegerRangeSelector(0, 360, 15);

    autoHook(tFont);
    autoHook(tColor);
    autoHook(tSize);
    autoHook(tJust);
    autoHook(tAngle);

    QHBoxLayout* top = new QHBoxLayout();
    top->addWidget(makeLabel("String"));
    top->addWidget(tNum);
    top->addStretch(1);

    QGridLayout* opts = new QGridLayout();
    addPair(opts, 0, makeLabel("Font"), tFont);
    addPair(opts, 1, makeLabel("Color"), tColor);
    addPair(opts, 2, makeLabel("Size"), tSize);
    opts->setRowMinimumHeight(3, 2);
    opts->addWidget(tApplyTextStyle, 4, 0, 1, 2, Qt::AlignVCenter | Qt::AlignRight);
    opts->setRowMinimumHeight(5, 6);
    addPair(opts, 6, makeLabel("Just"), tJust);
    addPair(opts, 7, makeLabel("Angle"), tAngle);

    opts->setColumnMinimumWidth(1, 200);

    tSet = makeGroupBox("Properties");
    tSet->setLayout(opts);

    QVBoxLayout* main = new QVBoxLayout();
    main->addLayout(top);
    main->addSpacing(6);
    main->addWidget(tSet);
    main->addStretch(1);

    this->setDialogLayout(main);
}

void ViewTextProperties::updateDialog() {
    int id = getID();
    tSet->setEnabled(id != -1);
    if (id == -1) {
        return;
    }

    tFont->setCurrentIndex(pstr[id].font);
    tColor->setCurrentIndex(pstr[id].color);
    tSize->setValue(pstr[id].charsize);

    tJust->setCurrentIndex(pstr[id].just);
    tAngle->setValue(pstr[id].rot);
}

void ViewTextProperties::applyDialog() {
    int id = getID();
    if (id == -1) return;

    pstr[id].font = tFont->currentIndex();
    pstr[id].color = tColor->currentIndex();
    pstr[id].charsize = tSize->value();

    pstr[id].just = tJust->currentIndex();
    pstr[id].rot = tAngle->value();

    drawgraph();
}

int ViewTextProperties::getID() {
    if (tNum->count() == 0) return -1;

    bool ok;
    int id = tNum->currentText().toInt(&ok);
    if (!ok) {
        printf("Uh oh. So not okay.\n");
        return -1;
    }
    return id;\
}

void ViewTextProperties::addItem(int id) {
    if (tNum->count() == 0) {
        tNum->addItem(QString::number(id));
        tNum->setCurrentIndex(0);
    } else {
        tNum->addItem(QString::number(id));
    }
}

void ViewTextProperties::setItem(int loc) {
    tNum->setCurrentIndex(loc);
}

void ViewTextProperties::removeItem(int loc) {
    tNum->removeItem(loc);
}

void ViewTextProperties::spreadTextStyle() {
    int id = getID();
    if (id == -1) return;

    int font = tFont->currentIndex();
    int color = tColor->currentIndex();
    double size = tSize->value();

    for (int i=0;i<MAXSTR;i++) {
        pstr[i].font = font;
        pstr[i].color = color;
        pstr[i].charsize = size;
    }

    drawgraph();
}
