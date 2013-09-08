#include "view/axis.h"
#include "choosers.h"
#include "util.h"
#include "base/globals.h"
#include "prop.h"

QComboBox* makeAxisSelector() {
    QComboBox* q = new QComboBox();
    q->addItem("X axis");
    q->addItem("Y axis");
    q->addItem("Zero X axis");
    q->addItem("Zero Y axis");
    q->addItem("Alternate X axis");
    q->addItem("Alternate Y axis");
    return q;
}

QComboBox* makeSideSelector(bool b) {
    QComboBox* q = new QComboBox();
    if (b) q->addItem("None");
    q->addItem("Normal");
    q->addItem("Opposite");
    q->addItem("Both");
    q->setCurrentIndex(1);
    return q;
}

ViewAxis::ViewAxis(MainWindow *parent) :
    Dialog(parent, "Axis", true)
{
    WorldDimProp::add(this);

    editAxis = makeAxisSelector();
    connect(editAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    axisLabel = new QLineEdit();
    axisLabel->setMinimumWidth(300);

    uMinLabel = makeLabel("W Min");
    uMaxLabel = makeLabel("W Max");

    uMin = new QLineEdit();
    uMax = new QLineEdit();

    majTic = new QLineEdit();
    minTic = new QLineEdit();

    startOpt = new QCheckBox(tr("Min Tick:"));
    connect(startOpt, SIGNAL(stateChanged(int)), this, SLOT(fadeMinTick()));

    uStart = new QLineEdit();

    stopOpt = new QCheckBox(tr("Max Tick:"));
    connect(stopOpt, SIGNAL(stateChanged(int)), this, SLOT(fadeMaxTick()));

    uStop = new QLineEdit();

    labelFormat = new QComboBox();
    labelFormat->addItem("Decimal");
    labelFormat->addItem("Exponential");
    labelFormat->addItem("Power");

    labelPrecision = new QComboBox;
    for (int i=0; i<10; i++) {
        labelPrecision->addItem(QString::number(i));
    }
    labelPrecision->setCurrentIndex(1);

    labelSkip = new IntegerSpinBox();
    labelSkip->setMinimum(0);
    labelSkip->setMaximum(10);

    labelFormatLabel = makeLabel("Format:");
    labelPrecisionLabel = makeLabel("Precision:");
    labelSkipLabel = makeLabel("Skip:");

    textSide = makeSideSelector(true);
    connect(textSide, SIGNAL(currentIndexChanged(int)), this, SLOT(fadeText()));
    textProps = makeButton("Text Properties", SLOT(loadText()));
    textDialog = NULL;

    tickSide = makeSideSelector(false);
    tickProps = makeButton("Tick Properties", SLOT(loadTicks()));
    tickDialog = NULL;

    autoHook(axisLabel);
    autoHook(uMin);
    autoHook(uMax);
    autoHook(majTic);
    autoHook(minTic);
    autoHook(startOpt);
    autoHook(uStart);
    autoHook(stopOpt);
    autoHook(uStop);
    autoHook(labelFormat);
    autoHook(labelPrecision);
    autoHook(labelSkip);
    autoHook(textSide);
    autoHook(tickSide);

    QGridLayout* scr = new QGridLayout();
    addPair(scr, 0, uMinLabel, uMin);
    addPair(scr, 1, uMaxLabel, uMax);
    addPair(scr, 2, makeLabel("Major Tick:"), majTic);
    addPair(scr, 3, makeLabel("Minor Tick:"), minTic);
    // TODO: clarify the start/stop type: use two lines??
    addPair(scr, 4, startOpt, uStart);
    addPair(scr, 5, stopOpt, uStop);
    // TODO: add an autoScale Axis button

    QGridLayout* lbl = new QGridLayout();
    addPair(lbl, 0, makeLabel("Side:"), textSide);
    lbl->setRowMinimumHeight(1, 4);
    addPair(lbl, 2, labelFormatLabel, labelFormat);
    addPair(lbl, 3, labelPrecisionLabel, labelPrecision);
    addPair(lbl, 4, labelSkipLabel, labelSkip);
    lbl->setRowMinimumHeight(5, 4);
    lbl->addWidget(textProps, 6, 0, 1, 2);

    QGridLayout* lns = new QGridLayout();
    addPair(lns, 0, makeLabel("Side:"), tickSide);
    lns->addWidget(tickProps, 1, 0, 1, 2);

    QGridLayout* tp = new QGridLayout();
    addPair(tp, 0, makeLabel("Edit:"), editAxis);
    tp->addWidget(makeLabel("Axis Label:"), 1, 0);
    tp->addWidget(axisLabel, 1, 1, 1, 2);
    tp->setRowMinimumHeight(2, 8);

    tp->setColumnStretch(0, 0);
    tp->setColumnStretch(1, 0);
    tp->setColumnStretch(2, 2);

    QVBoxLayout* layout = new QVBoxLayout();
    QGroupBox* scrb = new QGroupBox(tr("Scale"));
    scrb->setLayout(scr);
    QGroupBox* lblb = new QGroupBox(tr("Labels"));
    lblb->setLayout(lbl);
    QGroupBox* lnsb = new QGroupBox(tr("Ticks, Gridlines"));
    lnsb->setLayout(lns);

    QVBoxLayout* lhv = new QVBoxLayout();
    lhv->addWidget(scrb);
    lhv->addStretch(1);

    QVBoxLayout* rhv = new QVBoxLayout();
    rhv->addWidget(lblb);
    rhv->addWidget(lnsb);
    rhv->addStretch(1);

    QHBoxLayout* mdiv = new QHBoxLayout();
    mdiv->addLayout(rhv, 1);
    mdiv->addLayout(lhv, 2);

    layout->addLayout(tp);
    layout->addLayout(mdiv);

    this->setDialogLayout(layout);
}

void ViewAxis::updateWorldDimensions(QObject* q) {
    if (q == this) return;

    int axis = editAxis->currentIndex();

    if (axis % 2  == Y_AXIS) {
        uMin->setText(QString::number(g[cg].w.yg1,'g',9));
        uMax->setText(QString::number(g[cg].w.yg2,'g',9));
    } else {
        uMin->setText(QString::number(g[cg].w.xg1,'g',9));
        uMax->setText(QString::number(g[cg].w.xg2,'g',9));
    }

    majTic->setText(QString::number(g[cg].t[axis].tmajor,'g',9));
    minTic->setText(QString::number(g[cg].t[axis].tminor,'g',9));
}

void ViewAxis::updateDialog() {
    int axis = editAxis->currentIndex();
    int indx;
    tickmarks t = g[cg].t[axis];

    if (axis % 2 == Y_AXIS) {
        uMinLabel->setText(tr("Y Min"));
        uMaxLabel->setText(tr("Y Max"));
        uMin->setText(QString::number(g[cg].w.yg1,'g',9));
        uMax->setText(QString::number(g[cg].w.yg2,'g',9));
    } else {
        uMinLabel->setText(tr("X Min"));
        uMaxLabel->setText(tr("X Max"));
        uMin->setText(QString::number(g[cg].w.xg1,'g',9));
        uMax->setText(QString::number(g[cg].w.xg2,'g',9));
    }

    axisLabel->setText(QString::fromLocal8Bit(t.label.s));

    majTic->setText(QString::number(t.tmajor,'g',9));
    minTic->setText(QString::number(t.tminor,'g',9));

    startOpt->setChecked(t.tl_starttype == AUTO);
    stopOpt->setChecked(t.tl_stoptype == AUTO);
    uStart->setText(QString::number(t.tl_start, 'g',9));
    uStop->setText(QString::number(t.tl_stop, 'g',9));

    labelFormat->setCurrentIndex(get_format_index(t.tl_format));
    labelPrecision->setCurrentIndex(t.tl_prec);
    labelSkip->setValue(t.tl_skip);

    if (t.tl_flag == OFF) {
        textSide->setCurrentIndex(0);
    } else {
        if (t.tl_op == BOTH) {
            textSide->setCurrentIndex(3);
        } else if (axis % 2 == Y_AXIS) {
            textSide->setCurrentIndex(t.tl_op == LEFT ? 1 : 2);
        } else {
            textSide->setCurrentIndex(t.tl_op == BOTTOM ? 1 : 2);
        }
    }

    // note: sync with ticks sub-dialog; should be doable (pass in constructor)
    if (t.t_op == BOTH) {
        tickSide->setCurrentIndex(2);
    } else if (axis % 2 == Y_AXIS) {
        tickSide->setCurrentIndex(t.t_op == LEFT ? 0 : 1);
    } else {
        tickSide->setCurrentIndex(t.t_op == BOTTOM ? 0 : 1);
    }
}

void ViewAxis::applyDialog() {
    double val;
    int indx;
    int axis = editAxis->currentIndex();
    tickmarks t = g[cg].t[axis];

    if (axis % 2 == Y_AXIS) {
        if (leVal(uMin, &val)) g[cg].w.yg1 = val;
        if (leVal(uMax, &val)) g[cg].w.yg2 = val;
    } else {
        if (leVal(uMin, &val)) g[cg].w.xg1 = val;
        if (leVal(uMax, &val)) g[cg].w.xg2 = val;
    }

    strcpy(t.label.s,
           axisLabel->text().toAscii().data());

    if (leVal(majTic, &val)) t.tmajor = val;
    if (leVal(majTic, &val)) t.tminor = val;

    t.tl_starttype = startOpt->isChecked() ? AUTO : SPEC;
    t.tl_stoptype = stopOpt->isChecked() ? AUTO : SPEC;

    if (leVal(uStart, &val)) t.tl_start = val;
    if (leVal(uStop, &val)) t.tl_stop = val;

    t.tl_format = format_types[labelFormat->currentIndex()];
    t.tl_prec = labelPrecision->currentIndex();
    t.tl_skip = labelSkip->value();

    indx = textSide->currentIndex();
    if (indx == 0) {
        t.tl_flag = OFF;
    } else {
        t.tl_flag = ON;
        if (indx == 3) {
            t.tl_op = BOTH;
        } else if (axis % 2 == Y_AXIS) {
            t.tl_op = (indx == 1) ? LEFT : RIGHT;
        } else {
            t.tl_op = (indx == 1) ? BOTTOM : TOP;
        }
    }

    indx = tickSide->currentIndex();
    if (indx == 2) {
        t.t_op = BOTH;
    } else if (axis % 2 == Y_AXIS) {
        t.t_op = (indx == 0) ? LEFT : RIGHT;
    } else {
        t.t_op = (indx == 0) ? BOTTOM : TOP;
    }

    g[cg].t[axis] = t;
    WorldDimProp::send(this);
    drawgraph();
}

void ViewAxis::loadText() {
    if (textDialog) {
        textDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        showDialog(textDialog);
    } else {
        textDialog = new ViewAxisText(mainWindow);
        textDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        loadDialog(textDialog);
    }
}

void ViewAxis::loadTicks() {
    if (tickDialog) {
        tickDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        showDialog(tickDialog);
    } else {
        tickDialog = new ViewAxisTicks(mainWindow);
        tickDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        loadDialog(tickDialog);
    }
}

void ViewAxis::fadeText() {
    bool on = textSide->currentIndex() != 0;
    labelFormat->setEnabled(on);
    labelPrecision->setEnabled(on);
    labelSkip->setEnabled(on);
    labelFormatLabel->setEnabled(on);
    labelPrecisionLabel->setEnabled(on);
    labelSkipLabel->setEnabled(on);
    textProps->setEnabled(on);
}

void ViewAxis::fadeMinTick() {
    uStart->setDisabled(startOpt->isChecked());
}

void ViewAxis::fadeMaxTick() {
    uStop->setDisabled(stopOpt->isChecked());
}


ViewAxisText::ViewAxisText(MainWindow *parent) :
    Dialog(parent, "Axis Text", true)
{
    editAxis = makeAxisSelector();

}

void ViewAxisText::updateDialog() {

}

void ViewAxisText::applyDialog() {

}



ViewAxisTicks::ViewAxisTicks(MainWindow *parent) :
    Dialog(parent, "Axis Ticks & Gridlines", true)
{
    editAxis = makeAxisSelector();

}

void ViewAxisTicks::updateDialog() {

}

void ViewAxisTicks::applyDialog() {

}

