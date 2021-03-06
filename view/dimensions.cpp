#include "view/dimensions.h"
#include "base/globals.h"
#include "choosers.h"
#include "graphwidget.h"
#include "prop.h"
#include "mainwindow.h"
#include "tools.h"
#include "util.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>

const int OPTS_LEN = 8;

const struct {
    int ikey;
    const char* iname;
} opts[OPTS_LEN] = {
    {GRAPH_XY, "X Linear, Y Linear"},
    {GRAPH_LOGY, "X Linear, Y Logarithmic"},
    {GRAPH_LOGX, "X Logarithmic, Y Linear"},
    {GRAPH_LOGXY, "X Logarithmic, Y Logarithmic"},

    {GRAPH_BAR, "Vertical Bar"},
    {GRAPH_STACKEDBAR, "Vertical Bar Stacked"},
    {GRAPH_HBAR, "Horizontal Bar"},
    {GRAPH_STACKEDHBAR, "Horizontal Bar Stacked"}
};

/*
 * This dialog is designed to unify the old word, view, and graph type dialogs
 * into a cohesive whole.
 *
 */
ViewDimensions::ViewDimensions(MainWindow *parent) :
    Dialog(parent, "Dimensions", true)
{
    WorldDimProp::add(this);

    viewXMin = getUnitDoubleSpinBox();
    connect(viewXMin, SIGNAL(valueChanged(double)), this, SLOT(readjXMax()));
    viewXMax = getUnitDoubleSpinBox();
    connect(viewXMax, SIGNAL(valueChanged(double)), this, SLOT(readjXMin()));
    viewYMin = getUnitDoubleSpinBox();
    connect(viewYMin, SIGNAL(valueChanged(double)), this, SLOT(readjYMax()));
    viewYMax = getUnitDoubleSpinBox();
    connect(viewYMax, SIGNAL(valueChanged(double)), this, SLOT(readjYMin()));

    worldXMin = new QLineEdit();
    connect(worldXMin, SIGNAL(textEdited(QString)), this, SLOT(updateScale()));
    worldXMax = new QLineEdit();
    connect(worldXMax, SIGNAL(textEdited(QString)), this, SLOT(updateScale()));
    worldYMin = new QLineEdit();
    connect(worldYMin, SIGNAL(textEdited(QString)), this, SLOT(updateScale()));
    worldYMax = new QLineEdit();
    connect(worldYMax, SIGNAL(textEdited(QString)), this, SLOT(updateScale()));

    worldType = new QComboBox();
    for (int k=0;k<OPTS_LEN;k++) {
        worldType->addItem(opts[k].iname);
    }
    connect(worldType, SIGNAL(currentIndexChanged(int)), this, SLOT(updateScale()));

    viewSelect = makeButton("Rect Select", SLOT(viewRect()));
    setButtonBold(viewSelect);

    rescaleAxes = makeButton("Autoscale", SLOT(rescaleTicks()));
    setButtonBold(rescaleAxes);

    autoHook(viewXMin);
    autoHook(viewXMax);
    autoHook(viewYMin);
    autoHook(viewYMax);
    autoHook(worldXMin);
    autoHook(worldXMax);
    autoHook(worldYMin);
    autoHook(worldYMax);
    autoHook(worldType);

    QHBoxLayout* header = new QHBoxLayout();
    header->addWidget(makeLabel("Graph Type"), 0);
    header->addWidget(worldType, 0);
    header->addStretch(1);

    QGridLayout* wrldl = new QGridLayout();
    addPair(wrldl, 0, makeLabel("X Min"), worldXMin);
    addPair(wrldl, 1, makeLabel("X Max"), worldXMax);
    addPair(wrldl, 2, makeLabel("Y Min"), worldYMin);
    addPair(wrldl, 3, makeLabel("Y Max"), worldYMax);
    wrldl->setRowMinimumHeight(4, 12);
    wrldl->addWidget(rescaleAxes, 5, 0, 1, 2, Qt::AlignCenter);
    wrldl->setColumnMinimumWidth(1, 100);
    wrldl->setColumnStretch(0, 0);
    wrldl->setColumnStretch(1, 2);

    QGroupBox* wrldb = makeGroupBox("World Coords");
    wrldb->setLayout(wrldl);

    QVBoxLayout* wrld = new QVBoxLayout();
    wrld->addWidget(wrldb, 0);
    wrld->addStretch(1);

    QGridLayout* viewl = new QGridLayout();
    addPair(viewl, 0, makeLabel("X Min"), viewXMin);
    addPair(viewl, 1, makeLabel("X Max"), viewXMax);
    addPair(viewl, 2, makeLabel("Y Min"), viewYMin);
    addPair(viewl, 3, makeLabel("Y Max"), viewYMax);
    viewl->setRowMinimumHeight(4, 12);
    viewl->addWidget(viewSelect, 5, 0, 1, 2, Qt::AlignCenter);
    viewl->setColumnMinimumWidth(1, 120);
    viewl->setColumnStretch(0, 0);
    viewl->setColumnStretch(1, 2);

    QGroupBox* viewb = makeGroupBox("View Coords");
    viewb->setLayout(viewl);

    QVBoxLayout* view = new QVBoxLayout();
    view->addWidget(viewb, 0);
    view->addStretch(1);

    QHBoxLayout* bot = new QHBoxLayout();
    bot->addLayout(wrld);
    bot->addLayout(view);

    QVBoxLayout* ovr = new QVBoxLayout();
    ovr->addLayout(header);
    ovr->addStrut(12);
    ovr->addLayout(bot);

    this->setDialogLayout(ovr);
}


void ViewDimensions::readjXMin() {
    viewXMin->setMaximum(viewXMax->value());
}

void ViewDimensions::readjXMax() {
    viewXMax->setMinimum(viewXMin->value());
}

void ViewDimensions::readjYMin() {
    viewYMin->setMaximum(viewYMax->value());
}

void ViewDimensions::readjYMax() {
    viewYMax->setMinimum(viewYMin->value());
}


void ViewDimensions::updateDialog() {
    updateWorldDimensions(NULL);

    viewXMin->setValue(g[cg].v.xv1);
    viewXMax->setValue(g[cg].v.xv2);
    viewYMin->setValue(g[cg].v.yv1);
    viewYMax->setValue(g[cg].v.yv2);

    int vk = -1;
    switch (g[cg].type) {
    case GRAPH_POLAR:
    case GRAPH_SMITH:
    case GRAPH_STACKEDLINE:
        printf("type not implemented\n");
        break;

    case GRAPH_XY: vk = 0; break;
    case GRAPH_LOGY: vk = 1; break;
    case GRAPH_LOGX: vk = 2; break;
    case GRAPH_LOGXY: vk = 3; break;
    case GRAPH_BAR: vk = 4; break;
    case GRAPH_STACKEDBAR: vk = 5; break;
    case GRAPH_HBAR: vk = 6; break;
    case GRAPH_STACKEDHBAR: vk = 7; break;
    }
    if (vk != -1) {
        worldType->setCurrentIndex(vk);
    }

    readjXMin();
    readjXMax();
    readjYMin();
    readjYMax();
}

void ViewDimensions::applyDialog() {
    double val;

    if (leVal(worldXMin, &val)) g[cg].w.xg1 = val;
    if (leVal(worldXMax, &val)) g[cg].w.xg2 = val;
    if (leVal(worldYMin, &val)) g[cg].w.yg1 = val;
    if (leVal(worldYMax, &val)) g[cg].w.yg2 = val;

    g[cg].v.xv1 = viewXMin->value();
    g[cg].v.xv2 = viewXMax->value();
    g[cg].v.yv1 = viewYMin->value();
    g[cg].v.yv2 = viewYMax->value();

    g[cg].type =  opts[worldType->currentIndex()].ikey;
    drawgraph();
    WorldDimProp::send(this);
}

void ViewDimensions::finishRect(double x1, double x2, double y1, double y2) {
    g[cg].v.xv1 = x1;
    g[cg].v.xv2 = x2;
    g[cg].v.yv1 = y1;
    g[cg].v.yv2 = y2;

    viewXMin->setValue(x1);
    viewXMax->setValue(x2);
    viewYMin->setValue(y1);
    viewYMax->setValue(y2);

    readjXMin();
    readjXMax();
    readjYMin();
    readjYMax();

    drawgraph();
}

void ViewDimensions::updateWorldDimensions(QObject* sender) {
    if (sender == this) return;

    worldXMin->setText(QString::number(g[cg].w.xg1,'g',9));
    worldXMax->setText(QString::number(g[cg].w.xg2,'g',9));
    worldYMin->setText(QString::number(g[cg].w.yg1,'g',9));
    worldYMax->setText(QString::number(g[cg].w.yg2,'g',9));

    updateScale();
}

void ViewDimensions::viewRect() {
    GraphWidget::startRect(this);
}

const char* error_style = "QLineEdit{color: red;}";

void ViewDimensions::updateScale() {
    bool x1,x2,y1,y2;

    double valn,valx;
    int o = opts[worldType->currentIndex()].ikey;

    x1 = leVal(worldXMin, &valn);
    x2 = leVal(worldXMax, &valx);
    if (o == GRAPH_LOGX || o == GRAPH_LOGXY) {
        x1 &= valn > 0.0;
        x2 &= valx > 0.0;
    }
    if (x1 && x2 && valn >= valx) {
        x1 = x2 = false;
    }

    y1 = leVal(worldYMin, &valn);
    y2 = leVal(worldYMax, &valx);
    if (o == GRAPH_LOGY || o == GRAPH_LOGXY) {
        y1 &= valn > 0.0;
        y2 &= valx > 0.0;
    }
    if (y1 && y2 && valn >= valx) {
        y1 = y2 = false;
    }

    worldXMin->setStyleSheet(x1 ? "" : error_style);
    worldXMax->setStyleSheet(x2 ? "" : error_style);
    worldYMin->setStyleSheet(y1 ? "" : error_style);
    worldYMax->setStyleSheet(y2 ? "" : error_style);
}

void ViewDimensions::rescaleTicks() {
    mainWindow->toolsMenu->autoScale();
}
