#include "view/legend.h"
#include "base/globals.h"
#include "graphwidget.h"
#include "mainwindow.h"
#include "view.h"
#include "prop.h"
#include "choosers.h"
#include "util.h"

#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QGroupBox>

ViewLegend::ViewLegend(MainWindow* mainWin) :
    Dialog(mainWin, "Legend", this)
{
    propDialog = NULL;
    SetsSender::add(this);

    legendX = new QLineEdit();
    legendY = new QLineEdit();

    locType = new QComboBox();
    locType->addItem("View");
    locType->addItem("World");

    showLegend = new QCheckBox("Show Legend");
    showLegend->setChecked(true);
    connect(showLegend, SIGNAL(toggled(bool)), this, SLOT(fadeOpts()));

    prop = makeButton("Properties", SLOT(legendProp()));
    placer = makeButton("Place", SLOT(placeLegend()));
    setButtonBold(placer);
    placer->setMinimumWidth(100);

    coordsLabel = makeLabel("Coords");

    xLabel = makeLabel("X");
    yLabel = makeLabel("Y");

    autoHook(showLegend);
    autoHook(locType);
    autoHook(legendX);
    autoHook(legendY);

    QScrollArea* scrollArea = new QScrollArea();
    opl = new QWidget();
    intern = new QGridLayout();

    // TODO: realloc
    setLabels = QVector<QLineEdit*>(g[cg].maxplot);
    setLabelLabels = QVector<QLabel*>(g[cg].maxplot);

    for (int i=0;i<g[cg].maxplot;i++) {
        setLabels[i] = new QLineEdit();
        setLabels[i]->setMaxLength(256);
        setLabelLabels[i] = new QLabel(QString("Set ")+QString::number(i));
        intern->addWidget(setLabelLabels[i],i,0);
        intern->addWidget(setLabels[i],i,1);
        intern->setRowStretch(i, 0);
        autoHook(setLabels[i]);
    }

    intern->setColumnMinimumWidth(1, 200);
    intern->setColumnStretch(0, 0);
    intern->setColumnStretch(1, 3);
    intern->setRowStretch(g[cg].maxplot, 1);

    opl->setLayout(intern);
    scrollArea->setWidget(opl);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidgetResizable(true);

    QHBoxLayout* over = new QHBoxLayout();

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(showLegend, 0,0,1,2);
    layout->addWidget(prop, 1,0,1,2);

    layout->setRowMinimumHeight(2, 8);

    layout->addWidget(coordsLabel, 3, 0);
    layout->addWidget(locType, 3, 1);

    layout->addWidget(xLabel, 4, 0);
    layout->addWidget(yLabel, 5, 0);

    layout->addWidget(legendX, 4, 1);
    layout->addWidget(legendY, 5, 1);

    layout->addWidget(placer, 6, 0, 1, 2, Qt::AlignRight | Qt::AlignVCenter);

    layout->setRowStretch(7,2);

    over->addLayout(layout, 1);
    over->addStrut(12);
    over->addWidget(scrollArea, 3);

    this->setDialogLayout(over);
}

ViewLegend::~ViewLegend() {
}

void ViewLegend::fadeOpts() {
    bool on = showLegend->isChecked();
    placer->setEnabled(on);
    prop->setEnabled(on);
    locType->setEnabled(on);
    legendX->setEnabled(on);
    legendY->setEnabled(on);
    coordsLabel->setEnabled(on);
    xLabel->setEnabled(on);
    yLabel->setEnabled(on);
}

void handleColoring(QLineEdit* label, QLabel* labelLabel, int i) {
    bool dead = g[cg].p[i].active == FALSE && g[cg].p[i].deact == 0;
   bool deact_or_dead = g[cg].p[i].active == FALSE || g[cg].p[i].deact == 1;
   labelLabel->setDisabled(deact_or_dead);
   QPalette p = label->palette();
   p.setColor(QPalette::Text, dead ? Qt::gray : Qt::black);
   label->setPalette(p);
}

void ViewLegend::updateDialog() {
    showLegend->setChecked(g[cg].l.active == TRUE);

    locType->setCurrentIndex(g[cg].l.loctype == COORD_VIEW ? 0 : 1);

    while (setLabels.count() > g[cg].maxplot) {
        // todo: test me
        setLabels.pop_back();
        setLabelLabels.pop_back();
    }
    while (setLabels.count() < g[cg].maxplot) {
        setLabels.append(new QLineEdit());
        setLabels.last()->setMaxLength(256);
        int i = setLabelLabels.count();
        setLabelLabels.append(new QLabel(QString("Set ")+QString::number(i)));
        intern->addWidget(setLabelLabels.last(),i,0);
        intern->addWidget(setLabels.last(),i,1);
        intern->setRowStretch(i, 0);
        intern->setRowStretch(i+1, 1);
        autoHook(setLabels.last());
        opl->setMinimumSize(opl->sizeHint());
    }
    for (int i=0; i<g[cg].maxplot; i++) {
       setLabels[i]->setText(QString::fromUtf8(g[cg].p[i].lstr));
       handleColoring(setLabels[i], setLabelLabels[i], i);
    }

    legendX->setText(QString::number(g[cg].l.legx, 'g', 9));
    legendY->setText(QString::number(g[cg].l.legy, 'g', 9));
}


// only the on/off updates
void ViewLegend::updateSets() {
    if (setLabels.count() != g[cg].maxplot) {
        updateDialog();
    }
    for (int i=0; i<g[cg].maxplot; i++) {
       handleColoring(setLabels[i], setLabelLabels[i], i);
    }
}

void ViewLegend::applyDialog() {

    g[cg].l.active = showLegend->isChecked() ? TRUE : FALSE;

    g[cg].l.loctype = locType->currentIndex() == 0 ? COORD_VIEW : COORD_WORLD;

    g[cg].l.legx = legendX->text().toDouble();
    g[cg].l.legy = legendY->text().toDouble();

    for (int i=0;i<g[cg].maxplot;i++) {
        strncpy((char*)g[cg].p[i].lstr,setLabels[i]->text().toUtf8().data(), 256);
    }

    SetsSender::send();
    drawgraph();
    this->mainWindow->viewMenu->updateSymbolsLegend();
}

class LegendPlacingThingy : public MouseCallBack
{
private:
    ViewLegend* view;
public:
    void set(ViewLegend* t, QString txt) {
        view = t;
        view->mainWindow->gwidget->mouseClickCall = this;
        view->mainWindow->gwidget->setCursor(Qt::CrossCursor);
        view->mainWindow->statusBar()->showMessage(txt);
    }

    void mouse( double vx, double vy )
    {
        view->mainWindow->gwidget->mouseClickCall = NULL;
        view->mainWindow->gwidget->unsetCursor();
        view->mainWindow->statusBar()->clearMessage();
        view->applyLegendPos(vx,vy);
    }
} legendPlacer;


void ViewLegend::applyLegendPos(double vx, double vy) {
    double x, y;
    if (locType->currentIndex() == 0) {
        g[cg].l.loctype = COORD_VIEW;
        x = vx;
        y = vy;
    } else {
        g[cg].l.loctype = COORD_WORLD;
        view2world(vx, vy, &x, &y);
    }

    legendX->setText(QString::number(x, 'g', 3));
    legendY->setText(QString::number(y, 'g', 3));

    g[cg].l.legx = x;
    g[cg].l.legy = y;

    drawgraph();
}

void ViewLegend::placeLegend() {
    legendPlacer.set(this, tr("Click to place legend"));
}

void ViewLegend::updateLegendsField(int cset) {
    setLabels[cset]->setText(QString::fromLocal8Bit(g[cg].p[cset].lstr));
}

void ViewLegend::legendProp() {
    if (showDialog(propDialog)) return;
    propDialog = new ViewLegendProp(mainWindow);
    loadDialog(propDialog);
}

ViewLegendProp::ViewLegendProp(MainWindow* mainWin) :
    Dialog(mainWin, "Legend Properties", true)
{

    styleFont = new FontComboBox();
    styleColor = new ColorComboBox();
    styleSize = makeTextSizer();
    // abstract it!; makeNumberedComboBox
    styleWidth = new QComboBox();
    for (int i=0;i<15;i++) {
        styleWidth->addItem(QString::number(i*0.5+1.0));
    }
    styleSpacing = new QComboBox();
    for (int i=0;i<7;i++) {
        styleSpacing->addItem(QString::number(i*0.5+1.0));
    }

    frameColor = new ColorComboBox();
    frameWidth = makeWidthSelector();
    frameStyle = makeLineStyler();

    frameFill = new QCheckBox(tr("Fill frame"));
    connect(frameFill, SIGNAL(toggled(bool)), this, SLOT(resetFill()));

    frameFillColor = new ColorComboBox();
    connect(frameFillColor, SIGNAL(currentIndexChanged(int)), this, SLOT(resetFill()));
    frameFillPattern = new PatternComboBox();
    frameFillColorLabel = makeLabel("Fill Color");
    frameFillPatternLabel = makeLabel("Fill Pattern");
    resetFill();

    frame = makeGroupBox("Frame", true);
    style = makeGroupBox("Style");

    autoHook(styleFont);
    autoHook(styleColor);
    autoHook(styleSize);
    autoHook(styleWidth);
    autoHook(styleSpacing);
    autoHook(frame);
    autoHook(frameColor);
    autoHook(frameWidth);
    autoHook(frameStyle);
    autoHook(frameFill);
    autoHook(frameFillColor);
    autoHook(frameFillPattern);

    QGridLayout* stl = makeBoxLayout(style);

    stl->addWidget(makeLabel("Font"), 0, 0);
    stl->addWidget(styleFont, 0, 1);
    stl->addWidget(makeLabel("Text Color"), 1, 0);
    stl->addWidget(styleColor, 1, 1);
    stl->addWidget(makeLabel("Text Size"), 2, 0);
    stl->addWidget(styleSize, 2, 1);
    stl->addWidget(makeLabel("Width"), 3, 0);
    stl->addWidget(styleWidth, 3, 1);
    stl->addWidget(makeLabel("Spacing"), 4, 0);
    stl->addWidget(styleSpacing, 4, 1);

    QGridLayout* frl = makeBoxLayout(frame);
    addPair(frl, 0, makeLabel("Line Color"), frameColor);
    addPair(frl, 1, makeLabel("Line Width"), frameWidth);
    addPair(frl, 2, makeLabel("Line Style"), frameStyle);
    frl->addWidget(frameFill, 3, 0, 1, 2, Qt::AlignRight);
    addPair(frl, 4, frameFillColorLabel, frameFillColor);
    addPair(frl, 5, frameFillPatternLabel, frameFillPattern);

    QHBoxLayout* hrz = new QHBoxLayout();
    hrz->addWidget(style);
    hrz->addStrut(8);
    hrz->addWidget(frame);

    this->setDialogLayout(hrz);
}

void ViewLegendProp::updateDialog() {
    styleFont->setCurrentIndex(g[cg].l.font);
    styleColor->setCurrentIndex(g[cg].l.color);
    styleSize->setValue(g[cg].l.charsize);
    styleSpacing->setCurrentIndex((int)(2.0*g[cg].l.vgap) - 2);
    styleWidth->setCurrentIndex((int)(2.0*g[cg].l.len) - 2);

    frame->setChecked(g[cg].l.box == TRUE);

    frameColor->setCurrentIndex(g[cg].l.boxlcolor);
    frameWidth->setCurrentIndex(g[cg].l.boxlinew);
    frameStyle->setCurrentIndex(g[cg].l.boxlines);

    frameFill->setChecked(g[cg].l.boxfill == TRUE);
    frameFillColor->setCurrentIndex(g[cg].l.boxfillcolor == PTNFILLED);
    frameFillPattern->setCurrentIndex(g[cg].l.boxfillpat);
}

void ViewLegendProp::applyDialog() {
    g[cg].l.font = styleFont->currentIndex();
    g[cg].l.color = styleColor->currentIndex();
    g[cg].l.charsize = styleSize->value();
    g[cg].l.vgap = styleSpacing->currentIndex()*0.5 + 1.0;
    g[cg].l.len = styleWidth->currentIndex()*0.5 + 1.0;

    g[cg].l.box = frame->isChecked() ? TRUE : FALSE;

    g[cg].l.boxlcolor = frameColor->currentIndex();
    g[cg].l.boxlinew = frameWidth->currentIndex();
    g[cg].l.boxlines = frameStyle->currentIndex();

    g[cg].l.boxfill = frameFill->isChecked() ? TRUE : FALSE;
    g[cg].l.boxfillcolor = frameFillColor->currentIndex();
    g[cg].l.boxfillpat = frameFillPattern->currentIndex();
    g[cg].l.boxfillusing = frameFillColor->currentIndex() == 1 ? PTNFILLED : CLRFILLED;

    drawgraph();
}

void ViewLegendProp::resetFill() {
    bool fillOn = frameFill->isChecked();
    frameFillColor->setEnabled(fillOn);
    frameFillColorLabel->setEnabled(fillOn);
    bool patternOn = fillOn && frameFillColor->currentIndex() == 1;
    frameFillPattern->setEnabled(patternOn);
    frameFillPatternLabel->setEnabled(patternOn);
}
