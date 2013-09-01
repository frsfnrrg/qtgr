#include "view/ticks.h"
#include "base/globals.h"
#include "choosers.h"
#include "prop.h"
#include "util.h"

QComboBox* makeEditAxis() {
    QComboBox* editAxis = new QComboBox();
    editAxis->addItem("X axis");
    editAxis->addItem("Y axis");
    editAxis->addItem("Zero X axis");
    editAxis->addItem("Zero Y axis");
    editAxis->addItem("Alternate X axis");
    editAxis->addItem("Alternate Y axis");
    return editAxis;
}

ViewTicks::ViewTicks(MainWindow* mainWin) :
    Dialog(mainWin, "Ticks/Tick Labels", true)
{  
    WorldDimProp::add(this);

    labelPropsDialog = NULL;
    axisLabelDialog = NULL;
    ticksDialog = NULL;
    barDialog = NULL;
    majDialog = NULL;
    minDialog = NULL;

    // make input fields
    editAxis = makeEditAxis();
    connect(editAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));	
    
    // make line edits
    axisLabel = new QLineEdit();
    axisLabel->setMinimumWidth(300); 
    
    majTic = new QLineEdit();
    minTic = new QLineEdit();

    majGrid = new QCheckBox("Major grid");
    minGrid = new QCheckBox("Minor grid");
    
    // make radio buttons
    tickLabels = new QCheckBox("Tick labels");
    tickMarks  = new QCheckBox("Tick marks");
    axisBar = new QCheckBox("Axis bar");

    autoHook(axisLabel);
    autoHook(majTic);
    autoHook(minTic);
    autoHook(majGrid);
    autoHook(minGrid);
    autoHook(tickLabels);
    autoHook(tickMarks);
    autoHook(axisBar);

    QPushButton* labelPropsButton = makeButton(
                "Label props", SLOT(labelProps()));
    
    QPushButton* markProps  = makeButton(
                "Mark props", SLOT(ticks()));

    QPushButton* barProps = makeButton("Axis Bar props",
                                       SLOT(bar()));

    QPushButton* minGridProps = makeButton("Props",
                                           SLOT(minGridProps()));

    QPushButton* majGridProps = makeButton("Props",
                                           SLOT(majGridProps()));

    QPushButton* titleProps = makeButton("Props", SLOT(axisLabelProps()));

    QGridLayout* layout = new QGridLayout();
	
    layout->addWidget(new QLabel("Edit:"),0,0);
    layout->addWidget(editAxis,0,1);
    
    layout->addWidget(new QLabel(""),1,0);
    
    layout->addWidget(new QLabel("Axis label"),2,0);
    layout->addWidget(axisLabel,2,1,1,3);
    layout->addWidget(titleProps, 2, 4);
    
    layout->addWidget(new QLabel(""),3,0);
    
    layout->addWidget(new QLabel("Major tics"),4,0);
    layout->addWidget(new QLabel("Minor tics"),5,0);
    layout->addWidget(majTic,4,1);
    layout->addWidget(minTic,5,1);
    layout->addWidget(majGrid,4,3);
    layout->addWidget(minGrid,5,3);
    layout->addWidget(majGridProps, 4, 4);
    layout->addWidget(minGridProps, 5, 4);
    
    layout->addWidget(new QLabel(""),6,0);
    
    layout->addWidget(tickLabels,7,0);
    layout->addWidget(tickMarks,8,0);
    layout->addWidget(axisBar,9,0);
    layout->addWidget(labelPropsButton,7,1);
    layout->addWidget(markProps,8,1);
    layout->addWidget(barProps,9,1);

    layout->setColumnMinimumWidth(2, 50);
    layout->setColumnStretch(1, -3);

    this->setDialogLayout(layout);
}

void ViewTicks::updateDialog()
{
    int gno,axis; 
    
    gno = cg; // current graph only 
    axis = editAxis->currentIndex();
    //printf("UPDATE %d\n", axis);

    //printf("U1 %d %d %d %d %d %d\n", g[gno].t[axis].t_gridflag, g[gno].t[axis].t_mgridflag,g[gno].t[axis].t_mflag,g[gno].t[axis].t_flag,g[gno].t[axis].tl_flag,g[gno].t[axis].t_drawbar);

    axisLabel->setText(QString::fromLocal8Bit(g[gno].t[axis].label.s));
    


    // voodoo code
    // these two (tm, tl) checkboxes trigger an applyDialog via an autoHook. How??
    tickMarks->blockSignals(true);
    tickLabels->blockSignals(true);
    majGrid->blockSignals(true);
    minGrid->blockSignals(true);

    majGrid->setChecked(g[gno].t[axis].t_gridflag == ON);
    minGrid->setChecked(g[gno].t[axis].t_mgridflag == ON);

    tickMarks->setChecked((g[gno].t[axis].t_flag == ON) || (g[gno].t[axis].t_mflag == ON));

    tickLabels->setChecked(g[gno].t[axis].tl_flag == ON);

    axisBar->setChecked(g[gno].t[axis].t_drawbar == ON);

    // voodoo code
    tickMarks->blockSignals(false);
    tickLabels->blockSignals(false);
    majGrid->blockSignals(false);
    minGrid->blockSignals(false);

    //printf("U2 %d %d %d %d %d %d\n", g[gno].t[axis].t_gridflag, g[gno].t[axis].t_mgridflag,g[gno].t[axis].t_mflag,g[gno].t[axis].t_flag,g[gno].t[axis].tl_flag,g[gno].t[axis].t_drawbar);

    updateWorldDimensions(NULL);
}

void ViewTicks::updateWorldDimensions(QObject* sender)
{
    if (sender == this) return;
    int gno = cg;
    int axis = editAxis->currentIndex();
    majTic->setText(QString::number(g[gno].t[axis].tmajor,'g',9));
    minTic->setText(QString::number(g[gno].t[axis].tminor,'g',9));
}
  
void ViewTicks::applyDialog()
{
    int gno,axis; 
    char * label;
    
    gno = cg; // current graph only 
    axis = editAxis->currentIndex();
    //printf("APPLY %d\n", axis);

    //printf("A1 %d %d %d %d %d %d\n", g[gno].t[axis].t_gridflag, g[gno].t[axis].t_mgridflag,g[gno].t[axis].t_mflag,g[gno].t[axis].t_flag,g[gno].t[axis].tl_flag,g[gno].t[axis].t_drawbar);

    label = axisLabel->text().toAscii().data();

    strcpy(g[gno].t[axis].label.s, label);
    g[gno].t[axis].tmajor = majTic->text().toDouble();
    g[gno].t[axis].tminor = minTic->text().toDouble();

    g[gno].t[axis].t_gridflag = majGrid->isChecked() ? ON : OFF;
    g[gno].t[axis].t_mgridflag = minGrid->isChecked() ? ON : OFF;
    
    int tm = tickMarks->isChecked() ? ON : OFF;
    g[gno].t[axis].t_mflag = tm;
    g[gno].t[axis].t_flag = tm;

    g[gno].t[axis].tl_flag = tickLabels->isChecked() ? ON : OFF;

    g[gno].t[axis].t_drawbar = axisBar->isChecked() ? ON : OFF;

    //printf("A2 %d %d %d %d %d %d\n", g[gno].t[axis].t_gridflag, g[gno].t[axis].t_mgridflag,g[gno].t[axis].t_mflag,g[gno].t[axis].t_flag,g[gno].t[axis].tl_flag,g[gno].t[axis].t_drawbar);

    drawgraph();  
    
    WorldDimProp::send(this);
}

void ViewTicks::labelProps()
{
    if (labelPropsDialog) {
        labelPropsDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        showDialog(labelPropsDialog);
    } else {
        labelPropsDialog = new ViewTicksLabels(mainWindow);
        labelPropsDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        loadDialog(labelPropsDialog);
    }
}

void ViewTicks::axisLabelProps()
{
    if (axisLabelDialog) {
        axisLabelDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        showDialog(axisLabelDialog);
    } else {
        axisLabelDialog = new ViewTicksAxisLabel(mainWindow);
        axisLabelDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        loadDialog(axisLabelDialog);
    }
}

void ViewTicks::ticks()
{
    if (ticksDialog) {
        ticksDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        showDialog(ticksDialog);
    } else {
        ticksDialog = new ViewTicksMarks(mainWindow);
        ticksDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        loadDialog(ticksDialog);
    }
}

void ViewTicks::bar()
{
    if (barDialog) {
        barDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        showDialog(barDialog);
    } else {
        barDialog = new ViewTicksBar(mainWindow);
        barDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        loadDialog(barDialog);
    }
}

void ViewTicks::majGridProps()
{
    if (majDialog) {
        majDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        showDialog(majDialog);
    } else {
        majDialog = new ViewTicksMajGrid(mainWindow);
        majDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        loadDialog(majDialog);
    }
}

void ViewTicks::minGridProps()
{
    if (minDialog) {
        minDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        showDialog(minDialog);
    } else {
        minDialog = new ViewTicksMinGrid(mainWindow);
        minDialog->editAxis->setCurrentIndex(editAxis->currentIndex());
        loadDialog(minDialog);
    }
}


ViewTicksLabels::ViewTicksLabels(MainWindow* mwin) :
    Dialog(mwin, "Edit tick labels", true)
{
    editAxis = makeEditAxis();
    connect(editAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    textFont = new FontComboBox();
    textColor = new ColorComboBox();
    textSize = makeTextSizer();

    // make input fields
    labelFormat = new QComboBox();
    labelFormat->addItem("Decimal");
    labelFormat->addItem("Exponential");
    labelFormat->addItem("Power");

    labelPrecision = new QComboBox;
    for (int i=0; i<10; i++) {
        labelPrecision->addItem(QString::number(i));
    }
    labelPrecision->setCurrentIndex(1);

    startType = new QComboBox();
    startType->addItem(tr("Graph Min"));
    startType->addItem(tr("Specify..."));
    startType->setCurrentIndex(0);
    connect(startType, SIGNAL(currentIndexChanged(int)), this, SLOT(resetStart()));

    stopType = new QComboBox();
    stopType->addItem(tr("Graph Max"));
    stopType->addItem(tr("Specify..."));
    stopType->setCurrentIndex(0);
    connect(stopType, SIGNAL(currentIndexChanged(int)), this, SLOT(resetStop()));

    layoutType = new QComboBox();
    layoutType->addItem("Horizontal");
    layoutType->addItem("Vertical");
    layoutType->addItem("Angle...");
    layoutType->setCurrentIndex(0);
    connect(layoutType, SIGNAL(currentIndexChanged(int)), this, SLOT(resetLayout()));

    editStartAt = new QLineEdit();
    editStartAt->setEnabled(false);
    editStartLabel = makeLabel("Value:");
    editStartLabel->setEnabled(false);

    editStopAt = new QLineEdit();
    editStopAt->setEnabled(false);
    editStopLabel = makeLabel("Value:");
    editStopLabel->setEnabled(false);

    layoutAngleBox = new QSpinBox();
    layoutAngleBox->setSingleStep(15);
    layoutAngleBox->setMaximum(360);
    layoutAngleBox->setMinimum(0);
    layoutAngleBox->setEnabled(false);
    connect(layoutAngleBox, SIGNAL(editingFinished()), this, SLOT(updateAngleSlider()));

    layoutAngle = new QSlider(Qt::Horizontal);
    layoutAngle->setEnabled(false);
    layoutAngle->setRange(0, 360);
    layoutAngle->setTickInterval(30);
    layoutAngle->setValue(0);
    layoutAngle->setTickPosition(QSlider::TicksAbove);
    layoutAngle->setSingleStep(5);
    layoutAngle->setPageStep(30);
    connect(layoutAngle, SIGNAL(valueChanged(int)), this, SLOT(updateAngleBox()));

    QHBoxLayout* layoutEdit = new QHBoxLayout();
    layoutEdit->addWidget(layoutAngleBox);
    layoutEdit->addWidget(layoutAngle);

    layoutAngleLabel = makeLabel("Angle");
    layoutAngleLabel->setEnabled(false);

    stagger = new QSpinBox();
    stagger->setMinimum(0);
    stagger->setMaximum(19);

    skipEvery = new QSpinBox();
    skipEvery->setMinimum(0);
    skipEvery->setMaximum(19);

    drawSide = new QComboBox();
    drawSide->addItem(tr("Normal"));
    drawSide->addItem(tr("Opposite"));
    drawSide->addItem(tr("Both"));

    labelSpacing = new QSlider(Qt::Horizontal);
    labelSpacing->setRange(0, 20);
    labelSpacing->setValue(10);
    labelSpacing->setTickInterval(4);
    labelSpacing->setSingleStep(2);
    labelSpacing->setPageStep(4);
    labelSpacing->setTickPosition(QSlider::TicksAbove);
    connect(labelSpacing, SIGNAL(valueChanged(int)), this, SLOT(updateSpacingBox()));

    labelSpacingBox = new QDoubleSpinBox();
    labelSpacingBox->setSingleStep(0.2);
    labelSpacingBox->setMaximum(2.0);
    labelSpacingBox->setMinimum(0.0);
    labelSpacingBox->setDecimals(1);
    connect(labelSpacingBox, SIGNAL(editingFinished()), this, SLOT(updateSpacingSlider()));

    QHBoxLayout* labelSpacingEdit = new QHBoxLayout();
    labelSpacingEdit->addWidget(labelSpacingBox);
    labelSpacingEdit->addWidget(labelSpacing);

    autoHook(labelFormat);
    autoHook(labelPrecision);
    autoHook(textFont);
    autoHook(textColor);
    autoHook(textSize);
    autoHook(stagger);
    autoHook(skipEvery);
    autoHook(startType);
    autoHook(stopType);
    autoHook(layoutType);
    autoHook(editStartAt);
    autoHook(editStopAt);
    autoHook(layoutAngle);
    autoHook(drawSide);
    autoHook(labelSpacing);

    // LAYOUT

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(makeLabel("Axis: "),0,0);
    layout->addWidget(editAxis,0,1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(makeLabel("Font: "),2,0);
    layout->addWidget(textFont, 2, 1);

    layout->addWidget(makeLabel("Color"),3,0);
    layout->addWidget(textColor, 3, 1);

    layout->addWidget(makeLabel("Size:"),4,0);
    layout->addWidget(textSize, 4, 1);

    layout->setRowMinimumHeight(5, 12);

    layout->addWidget(makeLabel("Format:"),6,0);
    layout->addWidget(labelFormat,6,1);

    layout->addWidget(makeLabel("Stagger:"),7,0);
    layout->addWidget(stagger, 7, 1);

    layout->addWidget(makeLabel("Precision:"),8,0);
    layout->addWidget(labelPrecision,8,1);

    layout->setRowMinimumHeight(9, 12);

    layout->addWidget(makeLabel("Skip every:"),10,0);
    layout->addWidget(skipEvery, 10, 1);

    layout->addWidget(makeLabel("Start labels at:"),11,0);
    layout->addWidget(startType, 11, 1);
    layout->addWidget(editStartLabel, 12, 0);
    layout->addWidget(editStartAt, 12, 1);

    layout->addWidget(makeLabel("Stop labels at:"),13,0);
    layout->addWidget(stopType, 13, 1);
    layout->addWidget(editStopLabel, 14, 0);
    layout->addWidget(editStopAt, 14, 1);

    layout->setRowMinimumHeight(15, 12);

    layout->addWidget(makeLabel("Layout:"), 16, 0);
    layout->addWidget(layoutType, 16, 1);
    layout->addWidget(layoutAngleLabel, 17, 0);
    layout->addLayout(layoutEdit, 17, 1);

    layout->addWidget(makeLabel("Draw side:"), 18, 0);
    layout->addWidget(drawSide, 18, 1);

    layout->addWidget(makeLabel("Spacing"), 19, 0);
    layout->addLayout(labelSpacingEdit, 19, 1);

    layout->setColumnMinimumWidth(1, 200);

    this->setDialogLayout(layout);
}

void ViewTicksLabels::resetStart() {
    bool on = (startType->currentIndex() == 1);
    editStartAt->setEnabled(on);
    editStartLabel->setEnabled(on);
}

void ViewTicksLabels::resetStop() {
    bool on = (stopType->currentIndex() == 1);
    editStopAt->setEnabled(on);
    editStopLabel->setEnabled(on);
}

void ViewTicksLabels::resetLayout() {
    bool on = (layoutType->currentIndex() == 2);
    layoutAngle->setEnabled(on);
    layoutAngleBox->setEnabled(on);
    layoutAngleLabel->setEnabled(on);
}

void ViewTicksLabels::updateAngleBox() {
    layoutAngleBox->setValue(layoutAngle->value());
}

void ViewTicksLabels::updateAngleSlider() {
    layoutAngle->setValue(layoutAngleBox->value());
}

void ViewTicksLabels::updateSpacingBox() {
    labelSpacingBox->setValue(labelSpacing->value() * 0.1);
}

void ViewTicksLabels::updateSpacingSlider() {
    labelSpacing->setValue((int)(labelSpacingBox->value() * 10.0 + 0.5));
}

void ViewTicksLabels::updateDialog()
{
    int axis,gno;
    
    gno = cg; // current graph only 
    axis = editAxis->currentIndex();

    tickmarks t = g[gno].t[axis];
  
    labelFormat->setCurrentIndex(get_format_index(t.tl_format));
    labelPrecision->setCurrentIndex(t.tl_prec);

    textColor->setCurrentIndex(t.tl_color);
    textFont->setCurrentIndex(t.tl_font);
    textSize->setValue(t.tl_charsize);

    stagger->setValue(t.tl_staggered);
    startType->setCurrentIndex(t.tl_starttype == AUTO ? 0 : 1);
    stopType->setCurrentIndex(t.tl_stoptype == AUTO ? 0 : 1);
    editStartAt->setText(QString::number(t.tl_start, 'g',9));
    editStopAt->setText(QString::number(t.tl_stop, 'g',9));

    skipEvery->setValue(t.tl_skip);

    if (t.tl_op == BOTH) {
        drawSide->setCurrentIndex(2);
    } else if (axis % 2 == Y_AXIS) {
        drawSide->setCurrentIndex(t.tl_op == LEFT ? 0 : 1);
    } else {
        drawSide->setCurrentIndex(t.tl_op == BOTTOM ? 0 : 1);
    }

    if (t.tl_layout == SPEC) {
        layoutType->setCurrentIndex(2);
    } else {
        layoutType->setCurrentIndex(t.tl_layout == HORIZONTAL ? 0 : 1);
    }
    layoutAngle->setValue(t.tl_angle);

    if (axis % 2 == Y_AXIS) {
        labelSpacing->setValue((int)(10.0 * t.tl_hgap + 0.5));
        labelSpacingBox->setValue(t.tl_hgap);
    } else {
        labelSpacing->setValue((int)(10.0 * t.tl_vgap + 0.5));
        labelSpacingBox->setValue(t.tl_vgap);
    }
}

void ViewTicksLabels::applyDialog()
{
    int gno,axis; 
    
    gno = cg; // current graph only 
    axis = editAxis->currentIndex();

    g[gno].t[axis].tl_format = format_types[labelFormat->currentIndex()];
    g[gno].t[axis].tl_prec   = labelPrecision->currentIndex();
    g[gno].t[axis].tl_color = textColor->currentIndex();
    g[gno].t[axis].tl_font = textFont->currentIndex();
    g[gno].t[axis].tl_charsize = textSize->value();
    g[gno].t[axis].tl_staggered = stagger->value();
    g[gno].t[axis].tl_starttype = startType->currentIndex() == 0 ? AUTO : SPEC;
    g[gno].t[axis].tl_stoptype = stopType->currentIndex() == 0 ? AUTO : SPEC;

    double v;
    if (leVal(editStartAt, &v)) g[gno].t[axis].tl_start = v;
    if (leVal(editStopAt, &v)) g[gno].t[axis].tl_stop = v;

    g[gno].t[axis].tl_skip = skipEvery->value();

    int indx = drawSide->currentIndex();
    if (indx == 2) {
        g[gno].t[axis].tl_op = BOTH;
    } else if (axis % 2 == Y_AXIS) {
        g[gno].t[axis].tl_op = indx == 0 ? LEFT : RIGHT;
    } else {
        g[gno].t[axis].tl_op = indx == 0 ? BOTTOM : TOP;
    }

    if (layoutType->currentIndex() == 2) {
        g[gno].t[axis].tl_layout = SPEC;
    } else {
        g[gno].t[axis].tl_layout = layoutType->currentIndex() == 0 ? HORIZONTAL : VERTICAL;
    }
    g[gno].t[axis].tl_angle = layoutAngle->value() % 360;

    if (axis % 2 == Y_AXIS) {
        g[gno].t[axis].tl_hgap = labelSpacingBox->value();
    } else {
        g[gno].t[axis].tl_vgap = labelSpacingBox->value();
    }

    drawgraph();  
}


ViewTicksAxisLabel::ViewTicksAxisLabel(MainWindow* mainWin) :
    Dialog(mainWin, "Axis Label", true)
{
    editAxis = makeEditAxis();
    connect(editAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    direction = new QComboBox();
    direction->addItem("Parallel");
    direction->addItem("Perpendicular");

    textFont = new FontComboBox();
    textColor = new ColorComboBox();
    textSize = makeTextSizer();

    autoHook(direction);
    autoHook(textFont);
    autoHook(textColor);
    autoHook(textSize);

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(makeLabel("Axis:"),0,0);
    layout->addWidget(editAxis,0,1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(makeLabel("Direction:"), 2, 0);
    layout->addWidget(direction, 2, 1);

    layout->setRowMinimumHeight(3, 8);

    layout->addWidget(makeLabel("Font:"),4,0);
    layout->addWidget(textFont, 4, 1);

    layout->addWidget(makeLabel("Color"),5,0);
    layout->addWidget(textColor, 5, 1);

    layout->addWidget(makeLabel("Size:"),6,0);
    layout->addWidget(textSize, 6, 1);

    this->setDialogLayout(layout);
}

void ViewTicksAxisLabel::updateDialog() {
    int gno = cg;
    int axis = editAxis->currentIndex();

    int color = g[gno].t[axis].label.color;
    int font = g[gno].t[axis].label.font;
    double scale = g[gno].t[axis].label.charsize;

    textSize->setValue(scale);
    textFont->setCurrentIndex(font);
    textColor->setCurrentIndex(color);

    direction->setCurrentIndex((g[gno].t[axis].label_layout == PARA) ? 0 : 1);
}

void ViewTicksAxisLabel::applyDialog() {
    int gno = cg;
    int axis = editAxis->currentIndex();

    g[gno].t[axis].label.color = textColor->currentIndex();
    g[gno].t[axis].label.charsize = textSize->value();
    g[gno].t[axis].label.font = textFont->currentIndex();
    g[gno].t[axis].label_layout = (direction->currentIndex() == 0) ? PARA : PERP;

    drawgraph();
}


ViewTicksMarks::ViewTicksMarks(MainWindow* mainWin) :
    Dialog(mainWin, "Tick Marks", true)
{
    editAxis = makeEditAxis();
    connect(editAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    direction = new QComboBox();
    direction->addItem("In");
    direction->addItem("Out");
    direction->addItem("Both");

    location = new QComboBox();
    location->addItem(tr("Normal"));
    location->addItem(tr("Opposite"));
    location->addItem(tr("Both"));

    majLength = new QSlider();
    majLength->setOrientation(Qt::Horizontal);
    majLength->setMinimum(0);
    majLength->setMaximum(400);
    majLength->setTickInterval(100);
    majLength->setTickPosition(QSlider::TicksAbove);
    majLength->setSingleStep(50);
    majLength->setPageStep(100);
    connect(majLength, SIGNAL(valueChanged(int)), this, SLOT(updateMaj()));

    minLength = new QSlider();
    minLength->setOrientation(Qt::Horizontal);
    minLength->setMinimum(0);
    minLength->setMaximum(400);
    minLength->setTickInterval(100);
    minLength->setTickPosition(QSlider::TicksAbove);
    minLength->setSingleStep(50);
    minLength->setPageStep(100);
    connect(minLength, SIGNAL(valueChanged(int)), this, SLOT(updateMin()));

    majReadout = new QLabel("0.0");
    minReadout = new QLabel("0.0");

    autoHook(majLength);
    autoHook(minLength);
    autoHook(direction);
    autoHook(location);

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(makeLabel("Axis:"),0,0);
    layout->addWidget(editAxis,0,1,1,2);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(makeLabel("Direction:"), 2, 0);
    layout->addWidget(direction, 2, 1,1,2);

    layout->addWidget(makeLabel("Location:"),3,0);
    layout->addWidget(location, 3, 1,1,2);

    layout->setRowMinimumHeight(4, 5);

    layout->addWidget(makeLabel("Major Length"),5,0);
    layout->addWidget(majReadout, 5, 1);
    layout->addWidget(majLength, 5, 2);

    layout->addWidget(makeLabel("Minor Length"),6,0);
    layout->addWidget(minReadout, 6, 1);
    layout->addWidget(minLength, 6, 2);

    layout->setColumnMinimumWidth(1, 50);

    this->setDialogLayout(layout);
}

void ViewTicksMarks::updateMaj() {
    majReadout->setText(QString::number(((double)majLength->value()) / 100.0));
}

void ViewTicksMarks::updateMin() {
    minReadout->setText(QString::number(((double)minLength->value()) / 100.0));
}

void ViewTicksMarks::updateDialog() {
    int gno = cg;
    int axis = editAxis->currentIndex();
    tickmarks t = g[gno].t[axis];

    if (t.t_inout == BOTH) {
        direction->setCurrentIndex(2);
    } else {
        direction->setCurrentIndex(t.t_inout == IN ? 0 : 1);
    }

    majLength->setValue((int)(t.t_size * 100.0));
    minLength->setValue((int)(t.t_msize * 100.0));

    if (t.t_op == BOTH) {
        location->setCurrentIndex(2);
    } else if (axis % 2 == Y_AXIS) {
        location->setCurrentIndex(t.t_op == LEFT ? 0 : 1);
    } else {
        location->setCurrentIndex(t.t_op == BOTTOM ? 0 : 1);
    }
}

void ViewTicksMarks::applyDialog() {
    int gno = cg;
    int axis = editAxis->currentIndex();

    if (direction->currentIndex() == 2) {
        g[gno].t[axis].t_inout = BOTH;
    } else {
        g[gno].t[axis].t_inout = direction->currentIndex() == 0 ? IN : OUT;
    }

    g[gno].t[axis].t_size = ((double)majLength->value()) / 100.0;
    g[gno].t[axis].t_msize = ((double)minLength->value()) / 100.0;

    int indx = location->currentIndex();
    if (indx == 2) {
        g[gno].t[axis].t_op = BOTH;
    } else if (axis % 2 == Y_AXIS) {
        g[gno].t[axis].t_op = indx == 0 ? LEFT : RIGHT;
    } else {
        g[gno].t[axis].t_op = indx == 0 ? BOTTOM : TOP;
    }

    drawgraph();
}

LineStyleDialog::LineStyleDialog(MainWindow* mainWin, const char* title)
    : Dialog(mainWin, title, true)
{
    editAxis = makeEditAxis();
    connect(editAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    widthB = makeWidthSelector();

    colorB = new ColorComboBox();

    styleB = makeLineStyler();

    autoHook(widthB);
    autoHook(colorB);
    autoHook(styleB);

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(makeLabel("Axis:"),0,0);
    layout->addWidget(editAxis,0,1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(makeLabel("Style"),2,0);
    layout->addWidget(styleB, 2, 1);

    layout->addWidget(makeLabel("Width:"),3,0);
    layout->addWidget(widthB, 3, 1);

    layout->addWidget(makeLabel("Color:"), 4, 0);
    layout->addWidget(colorB, 4, 1);

    this->setDialogLayout(layout);
}


ViewTicksBar::ViewTicksBar(MainWindow* mainWin) :
    LineStyleDialog(mainWin, "Axis Bar")
{
}

void ViewTicksBar::updateDialog() {
    int gno = cg;
    int axis = editAxis->currentIndex();
    tickmarks t = g[gno].t[axis];

    styleB->setCurrentIndex(t.t_drawbarlines);
    colorB->setCurrentIndex(t.t_drawbarcolor);
    widthB->setCurrentIndex(t.t_drawbarlinew - 1);
}

void ViewTicksBar::applyDialog() {
    int gno = cg;
    int axis = editAxis->currentIndex();

    g[gno].t[axis].t_drawbarcolor = colorB->currentIndex();
    g[gno].t[axis].t_drawbarlines = styleB->currentIndex();
    g[gno].t[axis].t_drawbarlinew = widthB->currentIndex() + 1;

    drawgraph();
}

ViewTicksMajGrid::ViewTicksMajGrid(MainWindow* mainWin) :
    LineStyleDialog(mainWin, "Major Gridlines")
{
}

void ViewTicksMajGrid::updateDialog() {
    int gno = cg;
    int axis = editAxis->currentIndex();
    tickmarks t = g[gno].t[axis];

    styleB->setCurrentIndex(t.t_lines);
    colorB->setCurrentIndex(t.t_color);
    widthB->setCurrentIndex(t.t_linew - 1);
}

void ViewTicksMajGrid::applyDialog() {
    int gno = cg;
    int axis = editAxis->currentIndex();

    g[gno].t[axis].t_color = colorB->currentIndex();
    g[gno].t[axis].t_lines = styleB->currentIndex();
    g[gno].t[axis].t_linew = widthB->currentIndex() + 1;

    drawgraph();
}

ViewTicksMinGrid::ViewTicksMinGrid(MainWindow* mainWin) :
    LineStyleDialog(mainWin, "Minor Gridlines")
{
}

void ViewTicksMinGrid::updateDialog() {
    int gno = cg;
    int axis = editAxis->currentIndex();
    tickmarks t = g[gno].t[axis];

    styleB->setCurrentIndex(t.t_mlines);
    colorB->setCurrentIndex(t.t_mcolor);
    widthB->setCurrentIndex(t.t_mlinew - 1);
}

void ViewTicksMinGrid::applyDialog() {
    int gno = cg;
    int axis = editAxis->currentIndex();

    g[gno].t[axis].t_mcolor = colorB->currentIndex();
    g[gno].t[axis].t_mlines = styleB->currentIndex();
    g[gno].t[axis].t_mlinew = widthB->currentIndex() + 1;

    drawgraph();
}
