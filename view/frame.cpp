#include "view/frame.h"
#include "choosers.h"

#include "base/globals.h"

#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>

ViewFrame::ViewFrame(MainWindow* mainWin) :
    Dialog(mainWin, "Frame", true)
{
    graphType = new QComboBox();
    graphType->addItem(tr("Full"));
    graphType->addItem(tr("Half-open"));
    graphType->addItem(tr("None"));
    connect(graphType, SIGNAL(currentIndexChanged(int)), this, SLOT(setOOpts(int)));

    lineColor = new ColorComboBox();
    fillColor = new ColorComboBox();

    lineStyle = new QComboBox;
    lineStyle->addItem("None");
    lineStyle->addItem("Solid");
    lineStyle->addItem("Dashed");
    lineStyle->addItem("Dotted");
    lineStyle->addItem("Dash-Dot");
    lineStyle->addItem("Dash-DotDot");
    lineWidth = new QComboBox;
    for (int i=1; i<=MAX_LINEWIDTH; i++) {
      lineWidth->addItem(QString::number(i));
    }

    fillBG = new QCheckBox();
    connect(fillBG, SIGNAL(stateChanged(int)), this, SLOT(setFillOpt(int)));
    fillColor->setEnabled(false);

    lineColorLabel = makeLabel("Line Color");
    lineWidthLabel = makeLabel("Line Width");
    lineStyleLabel = makeLabel("Line Style");
    fillBGLabel = makeLabel("Fill background");
    fillColorLabel = makeLabel("Background color");
    fillColorLabel->setEnabled(false);
    QGridLayout* layout = new QGridLayout();

    autoHook(graphType);
    autoHook(lineColor);
    autoHook(lineWidth);
    autoHook(lineStyle);
    autoHook(fillBG);
    autoHook(fillColor);

    layout->addWidget(makeLabel("Type"),0,0);
    layout->addWidget(graphType,0,1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(lineColorLabel,2,0);
    layout->addWidget(lineColor,2,1);

    layout->setRowMinimumHeight(3, 1);

    layout->addWidget(lineWidthLabel,4,0);
    layout->addWidget(lineWidth,4,1);

    layout->setRowMinimumHeight(5, 1);

    layout->addWidget(lineStyleLabel,6,0);
    layout->addWidget(lineStyle,6,1);

    layout->setRowMinimumHeight(7, 8);

    layout->addWidget(fillBGLabel,8,0);
    layout->addWidget(fillBG,8,1);

    layout->setRowMinimumHeight(9, 1);

    layout->addWidget(fillColorLabel,10,0);
    layout->addWidget(fillColor,10,1);

    this->setDialogLayout(layout);
}

void ViewFrame::updateDialog() {
    if (g[cg].f.active == TRUE) {
        graphType->setCurrentIndex(g[cg].f.type);
    } else {
        graphType->setCurrentIndex(2);
    }

    lineColor->setCurrentIndex(g[cg].f.color);
    fillColor->setCurrentIndex(g[cg].f.color);

    fillBG->setChecked(g[cg].f.fillbg == TRUE);
    fillColor->setCurrentIndex(g[cg].f.bgcolor);

    lineWidth->setCurrentIndex(g[cg].f.linew - 1);
    lineStyle->setCurrentIndex(g[cg].f.lines);
}

void ViewFrame::applyDialog() {
    int factive, ftype;

    if (graphType->currentIndex() == 2) {
        factive = FALSE; ftype = 0;
    } else {
        factive = TRUE;
        ftype = graphType->currentIndex();
    }

    g[cg].f.active = factive;
    g[cg].f.type = ftype;
    g[cg].f.color =  lineColor->currentIndex();
    g[cg].f.linew = lineWidth->currentIndex() + 1;
    g[cg].f.lines = lineStyle->currentIndex();
    g[cg].f.fillbg = fillBG->isChecked() ? TRUE : FALSE;
    g[cg].f.bgcolor = fillColor->currentIndex();

    drawgraph();
}

void ViewFrame::setFillOpt(int v) {
    fillColor->setEnabled(v);
    fillColorLabel->setEnabled(v);
}

void ViewFrame::setOOpts(int i) {
    if (i == 2) {
        lineColor->setEnabled(false);
        lineColorLabel->setEnabled(false);
        lineWidth->setEnabled(false);
        lineWidthLabel->setEnabled(false);
        lineStyle->setEnabled(false);
        lineStyleLabel->setEnabled(false);
        fillBG->setEnabled(false);
        fillBGLabel->setEnabled(false);
        fillColor->setEnabled(false);
        fillColorLabel->setEnabled(false);
    } else {
        lineColor->setEnabled(true);
        lineColorLabel->setEnabled(true);
        lineWidth->setEnabled(true);
        lineWidthLabel->setEnabled(true);
        lineStyle->setEnabled(true);
        lineStyleLabel->setEnabled(true);
        fillBG->setEnabled(true);
        fillBGLabel->setEnabled(true);
        fillColor->setEnabled(fillBG->isChecked());
        fillColorLabel->setEnabled(fillBG->isChecked());
    }
}
