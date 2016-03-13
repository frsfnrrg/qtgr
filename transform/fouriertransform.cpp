#include "transform/fouriertransform.h"
#include "choosers.h"
#include "mainwindow.h"
#include "base/globals.h"
#include "tools.h"
#include "tools/options.h"
#include "prop.h"
#include "util.h"

#include <QGridLayout>
#include <QLabel>

TransformFourier::TransformFourier(MainWindow* mainWin) :
    Dialog(mainWin, "Fourier Transform")
{
    setNumber = new SetComboBox();
    connect(setNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    windowLabel = makeLabel("Data Window");
    loadLabel = makeLabel("Load Result As");
    loadXLabel = makeLabel("Let result X=");
    dataTypeLabel = makeLabel("Data type");
    operationLabel = makeLabel("Perform");

    windowType = new QComboBox();
    windowType->addItem(tr("None (Rectangular)"));
    windowType->addItem(tr("Triangular"));
    windowType->addItem(tr("Hanning"));
    windowType->addItem(tr("Welch"));
    windowType->addItem(tr("Hamming"));
    windowType->addItem(tr("Blackman"));
    windowType->addItem(tr("Parsing"));

    loadType = new QComboBox();
    loadType->addItem(tr("Magnitude"));
    loadType->addItem(tr("Phase"));
    loadType->addItem(tr("Coefficients"));

    loadX = new QComboBox();
    loadX->addItem(tr("Index"));
    loadX->addItem(tr("Frequency"));
    loadX->addItem(tr("Period"));

    dataType = new QComboBox();
    dataType->addItem(tr("Real"));
    dataType->addItem(tr("Complex"));

    operation = new QComboBox();
    operation->addItem(tr("Forward FFT"));
    operation->addItem(tr("Reverse FFT"));
    operation->addItem(tr("Forward DFT"));
    operation->addItem(tr("Reverse DFT"));
    operation->addItem(tr("Window only"));

    QGridLayout* layout = new QGridLayout();
    addPair(layout, 0, makeLabel("Set"), setNumber);
    layout->setRowMinimumHeight(1, 8);
    addPair(layout, 2, operationLabel, operation);
    layout->setRowMinimumHeight(3, 2);
    addPair(layout, 4, windowLabel, windowType);
    layout->setRowMinimumHeight(5, 2);
    addPair(layout, 6, loadLabel, loadType);
    layout->setRowMinimumHeight(7, 2);
    addPair(layout, 8, loadXLabel, loadX);
    layout->setRowMinimumHeight(9, 2);
    addPair(layout, 10, dataTypeLabel, dataType);

    this->setDialogLayout(layout);
}

void TransformFourier::updateDialog() {
    int setno = setNumber->currentIndex();
    bool noSet = g[cg].p[setno].active == FALSE && g[cg].p[setno].deact == 0;
//    destination->setDisabled(noSet);
//    destinationLabel->setDisabled(noSet);
    windowLabel->setDisabled(noSet);
    loadLabel->setDisabled(noSet);
    loadXLabel->setDisabled(noSet);
    dataTypeLabel->setDisabled(noSet);
    operationLabel->setDisabled(noSet);
    windowType->setDisabled(noSet);
    loadType->setDisabled(noSet);
    loadX->setDisabled(noSet);
    dataType->setDisabled(noSet);
    operation->setDisabled(noSet);
}

void TransformFourier::applyDialog() {
    int setno;

    setno = this->setNumber->currentIndex();

    if (g[cg].p[setno].active == FALSE && g[cg].p[setno].deact == 0) {
        return;
    }


    int fftflag, loadx, invflag, type, wind, load;

    int i = operation->currentIndex();
    invflag = i % 2 == 1;
    fftflag = i < 2;
    type = dataType->currentIndex();
    loadx = loadX->currentIndex();
    load = loadType->currentIndex();
    wind = windowType->currentIndex();
    if (i >= 4) { // only for window
        do_window(setno, type, wind);
    } else {
        do_fourier(fftflag, setno, load, loadx, invflag, type, wind);
    }

    // recognized double redraw: in both
    if (ToolsOptions::isRescaleOnTransform()) {
        mainWindow->toolsMenu->autoScale();
    } else {
        drawgraph();
    }

    SetsSender::send();
}

