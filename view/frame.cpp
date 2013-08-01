#include "view/frame.h"
#include "base/globals.h"

ViewFrame::ViewFrame(MainWindow* mainWin) :
    Dialog(mainWin, tr("Frame"))
{
    graphType = new QComboBox();
    graphType->addItem(tr("Full"));
    graphType->addItem(tr("Half-open"));
    graphType->addItem(tr("None"));


    QIcon colorIcon;
    QPixmap colorPix = QPixmap(20,20);

    lineColor = new QComboBox;
    fillColor = new QComboBox();
    for (int i=0; i<MAXCOLORS; i++) {
      colorPix.fill(this->mainWindow->gwidget->cmscolors[i]);
      colorIcon.addPixmap(colorPix);
      lineColor->addItem(colorIcon,"");
      fillColor->addItem(colorIcon,"");
    }

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

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(new QLabel(tr("Type:")),0,0);
    layout->addWidget(graphType,0,1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(new QLabel(tr("Line Color:")),2,0);
    layout->addWidget(lineColor,2,1);

    layout->setRowMinimumHeight(3, 1);

    layout->addWidget(new QLabel(tr("Line Width:")),4,0);
    layout->addWidget(lineWidth,4,1);

    layout->setRowMinimumHeight(5, 1);

    layout->addWidget(new QLabel(tr("Line Style:")),6,0);
    layout->addWidget(lineStyle,6,1);

    layout->setRowMinimumHeight(7, 8);

    layout->addWidget(new QLabel(tr("Fill background:")),8,0);
    layout->addWidget(fillBG,8,1);

    layout->setRowMinimumHeight(9, 1);

    layout->addWidget(new QLabel(tr("Background color:")),10,0);
    layout->addWidget(fillColor,10,1);

    this->setDialogLayout(layout);
}

void ViewFrame::updateDialog() {
    if (g[cg].f.active == ON) {
        graphType->setCurrentIndex(g[cg].f.type);
    } else {
        graphType->setCurrentIndex(2);
    }

    lineColor->setCurrentIndex(g[cg].f.color);
    fillColor->setCurrentIndex(g[cg].f.color);

    fillBG->setChecked(g[cg].f.fillbg == ON);
    fillColor->setCurrentIndex(g[cg].f.bgcolor);

    lineWidth->setCurrentIndex(g[cg].f.linew - 1);
    lineStyle->setCurrentIndex(g[cg].f.lines);
}

void ViewFrame::applyDialog() {
    int factive, ftype;

    if (graphType->currentIndex() == 2) {
        factive = OFF; ftype = 0;
    } else {
        factive = ON;
        ftype = graphType->currentIndex();
    }

    g[cg].f.active = factive;
    g[cg].f.type = ftype;
    g[cg].f.color =  lineColor->currentIndex();
    g[cg].f.linew = lineWidth->currentIndex() + 1;
    g[cg].f.lines = lineStyle->currentIndex();
    g[cg].f.fillbg = fillBG->isChecked() ? ON : OFF;
    g[cg].f.bgcolor = fillColor->currentIndex();

    drawgraph();
}

void ViewFrame::setFillOpt(int v) {
    fillColor->setEnabled(v);
}
