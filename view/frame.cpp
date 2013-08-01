#include "view/frame.h"

ViewFrame::ViewFrame(MainWindow* mainWin) :
    Dialog(mainWin, tr("Frame"))
{
    graphType = new QComboBox();
    graphType->addItem(tr("Full"));
    graphType->addItem(tr("Half-open"));
    graphType->addItem(tr("None"));

    lineColor = new QComboBox();

    lineWidth = new QComboBox();

    lineStyle = new QComboBox();

    fillBG = new QCheckBox();

    fillColor = new QComboBox();

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(new QLabel(tr("Type:")),0,0);
    layout->addWidget(graphType,0,1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(new QLabel(tr("Line Color:")),2,0);
    layout->addWidget(lineColor,2,1);

    layout->setRowMinimumHeight(3, 8);

    layout->addWidget(new QLabel(tr("Line Width:")),4,0);
    layout->addWidget(lineWidth,4,1);

    layout->setRowMinimumHeight(5, 8);

    layout->addWidget(new QLabel(tr("Line Style:")),6,0);
    layout->addWidget(lineStyle,6,1);

    layout->setRowMinimumHeight(7, 8);

    layout->addWidget(new QLabel(tr("Fill background:")),8,0);
    layout->addWidget(fillBG,8,1);

    layout->setRowMinimumHeight(7, 8);

    layout->addWidget(new QLabel(tr("Background color:")),10,0);
    layout->addWidget(fillColor,10,1);

    this->setDialogLayout(layout);
}

void ViewFrame::updateDialog() {

}

void ViewFrame::applyDialog() {

}
