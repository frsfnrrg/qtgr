#include "view/axis.h"
#include "choosers.h"
#include "util.h"
#include "base/globals.h"
#include "prop.h"
#include "mainwindow.h"
#include "view.h"

#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>

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
    setTip(editAxis, "Choose an axis to configure");

    axisLabel = new QLineEdit();
    axisLabel->setMinimumWidth(300);
    setTip(axisLabel, "Label for the entire axis");

    uMinLabel = makeLabel("W Min");
    uMaxLabel = makeLabel("W Max");
    uMin = new QLineEdit();
    uMax = new QLineEdit();
    setTip(uMinLabel, uMin, "Minimum value shown on the graph");
    setTip(uMaxLabel, uMax, "Maximum value shown on the graph");

    majTic = new QLineEdit();
    minTic = new QLineEdit();
    setTip(majTic, "Spacing for the major ticks and their tick labels");
    setTip(minTic, "Spacing for minor ticks");

    startOpt = new QCheckBox(tr("Min Tick"));
    connect(startOpt, SIGNAL(stateChanged(int)), this, SLOT(fadeMinTick()));
    uStart = new QLineEdit();
    setTip(startOpt, uStart, "At which value to start the major ticks and tick labels; default is axis minimum");

    stopOpt = new QCheckBox(tr("Max Tick"));
    connect(stopOpt, SIGNAL(stateChanged(int)), this, SLOT(fadeMaxTick()));
    uStop = new QLineEdit();
    setTip(stopOpt, uStop, "At which value to stop the major ticks and tick labels; default is axis maximum");

    loadDimensionsDialog = new QPushButton(tr("Dimension Properties..."));
    connect(loadDimensionsDialog, SIGNAL(clicked()), this->mainWindow->viewMenu, SLOT(dims()));

    labelFormat = new QComboBox();
    labelFormat->addItem("Decimal");
    labelFormat->addItem("Exponential");
    labelFormat->addItem("Power");
    labelFormat->addItem("General");

    labelPrecision = new QComboBox;
    for (int i=0; i<10; i++) {
        labelPrecision->addItem(QString::number(i));
    }
    labelPrecision->setCurrentIndex(1);

    labelSkip = new IntegerSpinBox();
    labelSkip->setMinimum(0);
    labelSkip->setMaximum(10);

    labelFormatLabel = makeLabel("Format");
    labelPrecisionLabel = makeLabel("Precision");
    labelSkipLabel = makeLabel("Skip");
    setTip(labelFormatLabel, labelFormat, "How to represent tick axis numbers");
    setTip(labelPrecisionLabel, labelPrecision, "Number of significant figures given after the first");
    setTip(labelSkipLabel, labelSkip, "Interval of labels not displayed");

    textSide = makeSideSelector(true);
    connect(textSide, SIGNAL(currentIndexChanged(int)), this, SLOT(fadeText()));
    setTip(textSide, "On which graph side the axis label and tick labels should go");
    textProps = makeButton("Text Properties...", SLOT(loadText()));
    setTip(textProps, "Configure the axis label and tick labels");
    textDialog = NULL;

    tickSide = makeSideSelector(false);
    setTip(tickSide, "On which graph side the major and minor ticks should go");
    tickProps = makeButton("Tick Properties...", SLOT(loadTicks()));
    setTip(tickProps, "Control gridlines and axis bar ticks");
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

    QGroupBox* scrb = makeGroupBox("Scale");
    QGridLayout* scr = makeBoxLayout(scrb);
    addPair(scr, 0, uMinLabel, uMin);
    addPair(scr, 1, uMaxLabel, uMax);
    scr->setRowMinimumHeight(2, 6);
    addPair(scr, 3, makeLabel("Major Tick", majTic), majTic);
    addPair(scr, 4, makeLabel("Minor Tick", minTic), minTic);
    // TODO: clarify the start/stop type: use two lines??
    scr->setRowMinimumHeight(5, 8);
    scr->addWidget(startOpt, 6, 0, Qt::AlignRight | Qt::AlignVCenter);
    scr->addWidget(uStart, 6, 1);
    scr->addWidget(stopOpt, 7, 0, Qt::AlignRight | Qt::AlignVCenter);
    scr->addWidget(uStop, 7, 1);
    scr->setRowMinimumHeight(8, 8);
    scr->addWidget(loadDimensionsDialog, 9, 0, 1, 2, Qt::AlignRight | Qt::AlignVCenter);

    QGroupBox* lblb = makeGroupBox("Labels");
    QGridLayout* lbl = makeBoxLayout(lblb);
    addPair(lbl, 0, makeLabel("Side", textSide), textSide);
    lbl->setRowMinimumHeight(1, 4);
    addPair(lbl, 2, labelFormatLabel, labelFormat);
    addPair(lbl, 3, labelPrecisionLabel, labelPrecision);
    addPair(lbl, 4, labelSkipLabel, labelSkip);
    lbl->setRowMinimumHeight(5, 4);
    lbl->addWidget(textProps, 6, 0, 1, 2);

    QGroupBox* lnsb = makeGroupBox("Ticks, Gridlines");
    QGridLayout* lns = makeBoxLayout(lnsb);
    addPair(lns, 0, makeLabel("Side", tickSide), tickSide);
    lns->addWidget(tickProps, 1, 0, 1, 2);

    QGridLayout* tp = new QGridLayout();
    addPair(tp, 0, makeLabel("Edit", editAxis), editAxis);
    tp->addWidget(makeLabel("Axis Label", axisLabel), 1, 0);
    tp->addWidget(axisLabel, 1, 1, 1, 2);
    tp->setRowMinimumHeight(2, 8);

    tp->setColumnStretch(0, 0);
    tp->setColumnStretch(1, 0);
    tp->setColumnStretch(2, 2);

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

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addLayout(tp);
    layout->addLayout(mdiv);

    this->setDialogLayout(layout);

    axisLabel->setFocus();
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

    axisLabel->setText(QString::fromUtf8(t.label.s));

    majTic->setText(QString::number(t.tmajor,'g',9));
    minTic->setText(QString::number(t.tminor,'g',9));

    startOpt->setChecked(t.tl_starttype == TYPE_AUTO);
    stopOpt->setChecked(t.tl_stoptype == TYPE_AUTO);
    uStart->setText(QString::number(t.tl_start, 'g',9));
    uStop->setText(QString::number(t.tl_stop, 'g',9));

    int ftype = get_format_index(t.tl_format);
    labelFormat->setCurrentIndex(ftype);
    labelPrecision->setCurrentIndex(t.tl_prec);
    labelSkip->setValue(t.tl_skip);

    if (t.tl_flag == FALSE) {
        textSide->setCurrentIndex(0);
    } else {
        if (t.tl_op == PLACE_BOTH) {
            textSide->setCurrentIndex(3);
        } else if (axis % 2 == Y_AXIS) {
            textSide->setCurrentIndex(t.tl_op == PLACE_LEFT ? 1 : 2);
        } else {
            textSide->setCurrentIndex(t.tl_op == PLACE_BOTTOM ? 1 : 2);
        }
    }

    // note: sync with ticks sub-dialog; should be doable (pass in constructor)
    if (t.t_op == PLACE_BOTH) {
        tickSide->setCurrentIndex(2);
    } else if (axis % 2 == Y_AXIS) {
        tickSide->setCurrentIndex(t.t_op == PLACE_LEFT ? 0 : 1);
    } else {
        tickSide->setCurrentIndex(t.t_op == PLACE_BOTTOM ? 0 : 1);
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

    if (t.label.s) free(t.label.s);
    const char* lt = axisLabel->text().toUtf8().data();
    int llen = strlen(lt);
    t.label.s = (char*)malloc(llen+1);
    strncpy(t.label.s, lt, llen+1);

    if (leVal(majTic, &val)) t.tmajor = val;
    if (leVal(minTic, &val)) t.tminor = val;

    t.tl_starttype = startOpt->isChecked() ? TYPE_AUTO : TYPE_SPEC;
    t.tl_stoptype = stopOpt->isChecked() ? TYPE_AUTO : TYPE_SPEC;

    if (leVal(uStart, &val)) t.tl_start = val;
    if (leVal(uStop, &val)) t.tl_stop = val;

    t.tl_format = format_types[labelFormat->currentIndex()];
    t.tl_prec = labelPrecision->currentIndex();
    t.tl_skip = labelSkip->value();

    indx = textSide->currentIndex();
    if (indx == 0) {
        t.tl_flag = FALSE;
    } else {
        t.tl_flag = TRUE;
        if (indx == 3) {
            t.tl_op = PLACE_BOTH;
        } else if (axis % 2 == Y_AXIS) {
            t.tl_op = (indx == 1) ? PLACE_LEFT : PLACE_RIGHT;
        } else {
            t.tl_op = (indx == 1) ? PLACE_BOTTOM : PLACE_TOP;
        }
    }

    indx = tickSide->currentIndex();
    if (indx == 2) {
        t.t_op = PLACE_BOTH;
    } else if (axis % 2 == Y_AXIS) {
        t.t_op = (indx == 0) ? PLACE_LEFT : PLACE_RIGHT;
    } else {
        t.t_op = (indx == 0) ? PLACE_BOTTOM : PLACE_TOP;
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
    Dialog(parent, "Axis Labels", true)
{
    editAxis = makeAxisSelector();
    connect(editAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    tickFont = new FontComboBox();
    tickColor = new ColorComboBox();
    tickSize = makeTextSizer();

    tickLayout = new QComboBox();
    tickLayout->addItem("Horizontal");
    tickLayout->addItem("Vertical");
    tickLayout->addItem("Angle...");
    tickLayout->setCurrentIndex(0);
    connect(tickLayout, SIGNAL(currentIndexChanged(int)), this, SLOT(fadeAngle()));

    tickAngleLabel = makeLabel("Angle");
    tickAngleLabel->setEnabled(false);
    tickAngle = new IntegerRangeSelector(0, 360, 30);
    tickAngle->setEnabled(false);

    tickSpacing = new DoubleRangeSelector(0.0, 2.0, 1, 0.2);

    axisFont = new FontComboBox();
    axisColor = new ColorComboBox();
    axisSize = makeTextSizer();

    axisLayout = new QComboBox();
    axisLayout->addItem("Parallel");
    axisLayout->addItem("Perpendicular");

    autoHook(tickFont);
    autoHook(tickColor);
    autoHook(tickSize);
    autoHook(tickLayout);
    autoHook(tickAngle);
    autoHook(tickSpacing);
    autoHook(axisFont);
    autoHook(axisColor);
    autoHook(axisSize);
    autoHook(axisLayout);

    QGridLayout* tp = new QGridLayout();
    addPair(tp, 0, makeLabel("Edit"), editAxis);
    tp->setRowMinimumHeight(1, 8);
    tp->setColumnStretch(0, 0);
    tp->setColumnStretch(1, 0);
    tp->setColumnStretch(2, 2);

    QGroupBox* tbx = makeGroupBox("Ticks");
    QGridLayout* tickla = makeBoxLayout(tbx);
    addPair(tickla, 0, makeLabel("Font"), tickFont);
    addPair(tickla, 1, makeLabel("Color"), tickColor);
    addPair(tickla, 2, makeLabel("Size"), tickSize);
    tickla->setRowMinimumHeight(3, 8);
    addPair(tickla, 4, makeLabel("Layout"), tickLayout);
    addPair(tickla, 5, tickAngleLabel, tickAngle);
    addPair(tickla, 6, makeLabel("Spacing"), tickSpacing);
    tickla->setColumnMinimumWidth(1, 200);

    QGroupBox* abx = makeGroupBox("Axis");
    QGridLayout* axisla = makeBoxLayout(abx);
    addPair(axisla, 0, makeLabel("Font"), axisFont);
    addPair(axisla, 1, makeLabel("Color"), axisColor);
    addPair(axisla, 2, makeLabel("Size"), axisSize);
    axisla->setRowMinimumHeight(3, 8);
    addPair(axisla, 4, makeLabel("Layout"), axisLayout);
    axisla->setColumnStretch(0, 0);
    axisla->setColumnStretch(1, 1);

    QVBoxLayout* tbl = new QVBoxLayout();
    tbl->addWidget(tbx);
    tbl->addStretch(2);

    QVBoxLayout* abl = new QVBoxLayout();
    abl->addWidget(abx);
    abl->addStretch(2);

    QHBoxLayout* ov = new QHBoxLayout();
    ov->addLayout(tbl, 2);
    ov->addLayout(abl, 1);

    QVBoxLayout* main = new QVBoxLayout();
    main->addLayout(tp);
    main->addLayout(ov);

    this->setDialogLayout(main);
}

void ViewAxisText::updateDialog() {
    int axis = editAxis->currentIndex();
    tickmarks t = g[cg].t[axis];

    axisFont->setCurrentIndex(t.label.font);
    axisColor->setCurrentIndex(t.label.color);
    axisSize->setValue(t.label.charsize);
    axisLayout->setCurrentIndex(t.label_layout == LAYOUT_PARALLEL ? 0 : 1);

    tickFont->setCurrentIndex(t.tl_font);
    tickColor->setCurrentIndex(t.tl_color);
    tickSize->setValue(t.tl_charsize);

    if (t.tl_layout == TYPE_SPEC) {
        tickLayout->setCurrentIndex(2);
    } else {
        tickLayout->setCurrentIndex(t.tl_layout == TICKS_HORIZONTAL ? 0 : 1);
    }
    tickAngle->setValue(t.tl_angle);

    if (axis % 2 == Y_AXIS) {
        tickSpacing->setValue(t.tl_hgap);
    } else {
        tickSpacing->setValue(t.tl_vgap);
    }
}

void ViewAxisText::applyDialog() {
    int axis = editAxis->currentIndex();
    tickmarks t = g[cg].t[axis];

    t.label.font = axisFont->currentIndex();
    t.label.color = axisColor->currentIndex();
    t.label.charsize = axisSize->value();
    t.label_layout = axisLayout->currentIndex() == 0 ? LAYOUT_PARALLEL : LAYOUT_PERPENDICULAR;

    t.tl_font = tickFont->currentIndex();
    t.tl_color = tickColor->currentIndex();
    t.tl_charsize = tickSize->value();

    if (tickLayout->currentIndex() == 2) {
        t.tl_layout = TYPE_SPEC;
    } else {
        t.tl_layout = tickLayout->currentIndex() == 0 ? TICKS_HORIZONTAL : TICKS_VERTICAL;
    }
    t.tl_angle = tickAngle->value() % 360;

    if (axis % 2 == Y_AXIS) {
        t.tl_hgap = tickSpacing->value();
    } else {
        t.tl_vgap = tickSpacing->value();
    }

    g[cg].t[axis] = t;
    drawgraph();
}

void ViewAxisText::fadeAngle() {
    bool on = tickLayout->currentIndex() == 2;
    tickAngleLabel->setEnabled(on);
    tickAngle->setEnabled(on);
}



ViewAxisTicks::ViewAxisTicks(MainWindow *parent) :
    Dialog(parent, "Axis Ticks & Gridlines", true)
{
    editAxis = makeAxisSelector();
    connect(editAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    // TODO: fill out _all_ the options available for the ticks
    // currently some things act oddly. This dialog may
    // need a second restructuring

    frameProps = new QPushButton(tr("Frame Properties..."));
    connect(frameProps, SIGNAL(clicked()), this->mainWindow->viewMenu, SLOT(frame()));

    tickBox = makeGroupBox("Ticks", true);
    connect(tickBox, SIGNAL(toggled(bool)), this, SLOT(fadeTickBox()));

    axisBarBox = makeGroupBox("Axis Bar", true);
    connect(axisBarBox, SIGNAL(toggled(bool)), this, SLOT(fadeAxisBarBox()));

    majGridBox = makeGroupBox("Major Gridlines", true);
    connect(majGridBox, SIGNAL(toggled(bool)), this, SLOT(fadeMajGridBox()));

    minGridBox = makeGroupBox("Minor Gridlines", true);
    connect(minGridBox, SIGNAL(toggled(bool)), this, SLOT(fadeMinGridBox()));

    tickDirection = new QComboBox();
    tickDirection->addItem("In");
    tickDirection->addItem("Out");
    tickDirection->addItem("Both");

    tickMajLength = new DoubleRangeSelector(0.0, 4.0, 2, 1.0);
    tickMinLength = new DoubleRangeSelector(0.0, 4.0, 2, 1.0);

    axisBarWidth = makeWidthSelector();
    axisBarColor = new ColorComboBox();
    axisBarStyle = makeLineStyler();

    majGridWidth = makeWidthSelector();
    majGridColor = new ColorComboBox();
    majGridStyle = makeLineStyler();

    minGridWidth = makeWidthSelector();
    minGridColor = new ColorComboBox();
    minGridStyle = makeLineStyler();

    autoHook(tickBox);
    autoHook(tickDirection);
    autoHook(tickMajLength);
    autoHook(tickMinLength);

    autoHook(axisBarBox);
    autoHook(axisBarWidth);
    autoHook(axisBarColor);
    autoHook(axisBarStyle);

    autoHook(majGridBox);
    autoHook(majGridWidth);
    autoHook(majGridColor);
    autoHook(majGridStyle);

    autoHook(minGridBox);
    autoHook(minGridWidth);
    autoHook(minGridColor);
    autoHook(minGridStyle);

    tickDirectionLabel = makeLabel("Direction");
    tickMajLengthLabel = makeLabel("Minor Length");
    tickMinLengthLabel = makeLabel("Major Length");

    axisBarStyleLabel = makeLabel("Style");
    axisBarWidthLabel = makeLabel("Width");
    axisBarColorLabel = makeLabel("Color");

    majGridStyleLabel = makeLabel("Style");
    majGridWidthLabel = makeLabel("Width");
    majGridColorLabel = makeLabel("Color");

    minGridStyleLabel = makeLabel("Style");
    minGridWidthLabel = makeLabel("Width");
    minGridColorLabel = makeLabel("Color");


    QGridLayout* tickla = makeBoxLayout(tickBox);
    addPair(tickla, 0, tickDirectionLabel, tickDirection);
    addPair(tickla, 1, tickMajLengthLabel, tickMajLength);
    addPair(tickla, 2, tickMinLengthLabel, tickMinLength);
    tickla->setColumnMinimumWidth(1, 150);

    QGridLayout* axisla = makeBoxLayout(axisBarBox);
    addPair(axisla, 0, axisBarStyleLabel, axisBarStyle);
    addPair(axisla, 1, axisBarWidthLabel, axisBarWidth);
    addPair(axisla, 2, axisBarColorLabel, axisBarColor);
    axisla->setColumnMinimumWidth(1, 150);

    QGridLayout* majgla = makeBoxLayout(majGridBox);
    addPair(majgla, 0, majGridStyleLabel, majGridStyle);
    addPair(majgla, 1, majGridWidthLabel, majGridWidth);
    addPair(majgla, 2, majGridColorLabel, majGridColor);

    QGridLayout* mingla = makeBoxLayout(minGridBox);
    addPair(mingla, 0, minGridStyleLabel, minGridStyle);
    addPair(mingla, 1, minGridWidthLabel, minGridWidth);
    addPair(mingla, 2, minGridColorLabel, minGridColor);

    QGridLayout* tp = new QGridLayout();
    addPair(tp, 0, makeLabel("Edit"), editAxis);
    tp->addWidget(frameProps, 0, 3);
    tp->setRowMinimumHeight(1, 8);
    tp->setColumnStretch(0, 0);
    tp->setColumnStretch(1, 0);
    tp->setColumnStretch(2, 2);
    tp->setColumnStretch(3, 0);

    QVBoxLayout* lhs = new QVBoxLayout();
    lhs->addWidget(tickBox);
    lhs->addWidget(axisBarBox);
    lhs->addStretch(2);

    QVBoxLayout* rhs = new QVBoxLayout();
    rhs->addWidget(majGridBox);
    rhs->addWidget(minGridBox);
    rhs->addStretch(2);

    QHBoxLayout* ov = new QHBoxLayout();
    ov->addLayout(lhs, 1);
    ov->addLayout(rhs, 1);

    QVBoxLayout* main = new QVBoxLayout();
    main->addLayout(tp);
    main->addLayout(ov);

    this->setDialogLayout(main);
}

void ViewAxisTicks::updateDialog() {
    int axis = editAxis->currentIndex();
    tickmarks t = g[cg].t[axis];

    tickBox->setChecked((t.t_flag == TRUE || t.t_mflag == TRUE));

    if (t.t_inout == TICKS_BOTH) {
        tickDirection->setCurrentIndex(2);
    } else {
        tickDirection->setCurrentIndex(t.t_inout == TICKS_IN ? 0 : 1);
    }

    tickMajLength->setValue(t.t_size);
    tickMinLength->setValue(t.t_msize);

    axisBarBox->setChecked(t.t_drawbar == TRUE);
    axisBarStyle->setCurrentIndex(t.t_drawbarlines);
    axisBarColor->setCurrentIndex(t.t_drawbarcolor);
    axisBarWidth->setCurrentIndex(t.t_drawbarlinew - 1);

    majGridBox->setChecked(t.t_gridflag == TRUE);
    majGridStyle->setCurrentIndex(t.t_lines);
    majGridColor->setCurrentIndex(t.t_color);
    majGridWidth->setCurrentIndex(t.t_linew - 1);

    minGridBox->setChecked(t.t_mgridflag == TRUE);
    minGridStyle->setCurrentIndex(t.t_mlines);
    minGridColor->setCurrentIndex(t.t_mcolor);
    minGridWidth->setCurrentIndex(t.t_mlinew - 1);
}

void ViewAxisTicks::applyDialog() {
    int axis = editAxis->currentIndex();
    int tm;
    tickmarks t = g[cg].t[axis];

    tm = tickBox->isChecked() ? TRUE : FALSE;
    t.t_mflag = tm;
    t.t_flag = tm;

    if (tickDirection->currentIndex() == 2) {
        t.t_inout = TICKS_BOTH;
    } else {
        t.t_inout = tickDirection->currentIndex() == 0 ? TICKS_IN : TICKS_OUT;
    }

    t.t_size = tickMajLength->value();
    t.t_msize = tickMinLength->value();

    t.t_drawbar = axisBarBox->isChecked() ? TRUE : FALSE;
    t.t_drawbarcolor = axisBarColor->currentIndex();
    t.t_drawbarlines = axisBarStyle->currentIndex();
    t.t_drawbarlinew = axisBarWidth->currentIndex() + 1;

    t.t_gridflag = majGridBox->isChecked() ? TRUE : FALSE;
    t.t_color = majGridColor->currentIndex();
    t.t_lines = majGridStyle->currentIndex();
    t.t_linew = majGridWidth->currentIndex() + 1;

    t.t_mgridflag = minGridBox->isChecked() ? TRUE : FALSE;
    t.t_mcolor = minGridColor->currentIndex();
    t.t_mlines = minGridStyle->currentIndex();
    t.t_mlinew = minGridWidth->currentIndex() + 1;

    g[cg].t[axis] = t;
    drawgraph();
}

void ViewAxisTicks::fadeTickBox() {
    bool on = (tickBox->isChecked());
    tickDirection->setEnabled(on);
    tickMajLength->setEnabled(on);
    tickMinLength->setEnabled(on);
    tickDirectionLabel->setEnabled(on);
    tickMajLengthLabel->setEnabled(on);
    tickMinLengthLabel->setEnabled(on);
}

void ViewAxisTicks::fadeAxisBarBox() {
    bool on = (axisBarBox->isChecked());
    axisBarWidth->setEnabled(on);
    axisBarColor->setEnabled(on);
    axisBarStyle->setEnabled(on);
    axisBarWidthLabel->setEnabled(on);
    axisBarColorLabel->setEnabled(on);
    axisBarStyleLabel->setEnabled(on);
}

void ViewAxisTicks::fadeMajGridBox() {
    bool on = (majGridBox->isChecked());
    majGridWidth->setEnabled(on);
    majGridColor->setEnabled(on);
    majGridStyle->setEnabled(on);
    majGridWidthLabel->setEnabled(on);
    majGridColorLabel->setEnabled(on);
    majGridStyleLabel->setEnabled(on);
}

void ViewAxisTicks::fadeMinGridBox() {
    bool on = (minGridBox->isChecked());
    minGridWidth->setEnabled(on);
    minGridColor->setEnabled(on);
    minGridStyle->setEnabled(on);
    minGridWidthLabel->setEnabled(on);
    minGridColorLabel->setEnabled(on);
    minGridStyleLabel->setEnabled(on);
}

