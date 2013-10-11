#include "view/text.h"
#include "base/globals.h"
#include "choosers.h"

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
    plotstr str;
    for (int i=0;i<MAXSTR;i++) {
        if (isactive_string(i) && !texts[i]) {
            texts[i] = new ViewTextElement(this, i);
            textsLayout->addWidget(texts[i]);
            printf("TT Added: %i\n", i);
        } else if (texts[i] != NULL) {
            elem = texts[i];
            textsLayout->removeWidget(texts[i]);
            delete elem;
            texts[i] = NULL;
            printf("TT Emptied: %i\n", i);
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

void ViewText::placeText() {
    int i = next_string();
    texts[i] = new ViewTextElement(this, i);
    textsLayout->addWidget(texts[i]);
}

void ViewText::addText(float x, float y) {

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

    textArea = new QPlainTextEdit();

    xCoord = new DoubleSpinBox();
    xCoord->setRange(0, 1.0);
    xCoord->setSingleStep(0.05);

    yCoord = new DoubleSpinBox();
    yCoord->setRange(0, 1.0);
    yCoord->setSingleStep(0.05);

    relocateButton = new QPushButton(tr("Move"));
    connect(relocateButton, SIGNAL(clicked()), this, SLOT(reloc()));

    par->autoHook(xCoord);
    par->autoHook(yCoord);
    par->autoHook(textArea);

    layout = new QGridLayout();

    layout->addWidget(makeQLabel(this, "Text"),0,0);

    layout->addWidget(textArea, 0, 1);

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
}

void ViewTextElement::reloc() {
    par->relocateText(num);
}

void ViewTextElement::applyValues() {
    // use sizeof
    strncpy((char*)pstr[num].s, textArea->toPlainText().toAscii().data(), MAXSTRLEN+1);
}

void ViewTextElement::updateValues() {
    // todo subclass for cleanliness
    textArea->blockSignals(true);
    textArea->clear();
    textArea->moveCursor(QTextCursor::End);
    textArea->insertPlainText(QString(pstr[num].s));
    textArea->blockSignals(false);
}

