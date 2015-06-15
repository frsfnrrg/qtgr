#include "view/legend.h"
#include "base/globals.h"
#include "graphwidget.h"
#include "mainwindow.h"
#include "view.h"
#include "prop.h"
#include "choosers.h"

ViewLegend::ViewLegend(MainWindow* mainWin) :
    Dialog(mainWin, "Legend", this)
{
    propDialog = NULL;
    SetsSender::add(this);

    legendX = new QLineEdit();
    legendY = new QLineEdit();

    locType = new QComboBox();
    locType->addItem("World");
    locType->addItem("View");

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
    QWidget* opl = new QWidget();
    QGridLayout* intern = new QGridLayout();

    for (int i=0;i<MAXPLOT;i++) {
        setLabels[i] = new QLineEdit();
        setLabels[i]->setMaxLength(50);
        setLabelLabels[i] = new QLabel(QString("Set ")+QString::number(i));
        intern->addWidget(setLabelLabels[i],i,0);
        intern->addWidget(setLabels[i],i,1);
        autoHook(setLabels[i]);
    }

    intern->setColumnMinimumWidth(1, 200);
    intern->setColumnStretch(0, 0);
    intern->setColumnStretch(1, 3);

    opl->setLayout(intern);
    scrollArea->setWidget(opl);
    scrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

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

void ViewLegend::updateDialog() {
    showLegend->setChecked(g[cg].l.active == ON);

    locType->setCurrentIndex(g[cg].l.loctype == VIEW ? 0 : 1);

    for (int i=0; i<MAXPLOT; i++) {
       setLabels[i]->setText(QString::fromLocal8Bit(g[cg].l.str[i].s));
       setLabelLabels[i]->setDisabled(g[cg].p[i].active == OFF && g[cg].p[i].deact == 0);
    }

    legendX->setText(QString::number(g[cg].l.legx, 'g', 9));
    legendY->setText(QString::number(g[cg].l.legy, 'g', 9));
}


// only the on/off updates
void ViewLegend::updateSets() {
    for (int i=0; i<MAXPLOT; i++) {
       setLabelLabels[i]->setDisabled(g[cg].p[i].active == OFF && g[cg].p[i].deact == 0);
    }
}

void ViewLegend::applyDialog() {

    g[cg].l.active = showLegend->isChecked() ? ON : OFF;

    g[cg].l.loctype = locType->currentIndex() == 0 ? VIEW : WORLD;

    g[cg].l.legx = legendX->text().toDouble();
    g[cg].l.legy = legendY->text().toDouble();

    for (int i=0;i<MAXPLOT;i++) {
        strcpy((char*)g[cg].l.str[i].s,setLabels[i]->text().toAscii().data());
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

    void mouse( int x, int y, int w, int h )
    {
        view->mainWindow->gwidget->mouseClickCall = NULL;
        view->mainWindow->gwidget->unsetCursor();
        view->mainWindow->statusBar()->clearMessage();
        view->applyLegendPos(double(x)/double(w), 1.0 - double(y)/double(h));
    }
} legendPlacer;


void ViewLegend::applyLegendPos(double x, double y) {
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
    setLabels[cset]->setText(QString::fromLocal8Bit(g[cg].l.str[cset].s));
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
    for (int i=0;i<8;i++) {
        styleWidth->addItem(QString::number(i+1));
    }
    styleSpacing = new QComboBox();
    for (int i=0;i<4;i++) {
        styleSpacing->addItem(QString::number(i+1));
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
    styleSpacing->setCurrentIndex(g[cg].l.vgap - 1);
    styleWidth->setCurrentIndex(g[cg].l.len - 1);

    frame->setChecked(g[cg].l.box == ON);

    frameColor->setCurrentIndex(g[cg].l.boxlcolor);
    frameWidth->setCurrentIndex(g[cg].l.boxlinew);
    frameStyle->setCurrentIndex(g[cg].l.boxlines);

    frameFill->setChecked(g[cg].l.boxfill == ON);
    frameFillColor->setCurrentIndex(g[cg].l.boxfillcolor);
    frameFillPattern->setCurrentIndex(g[cg].l.boxfillpat);
}

void ViewLegendProp::applyDialog() {
    g[cg].l.font = styleFont->currentIndex();
    g[cg].l.color = styleColor->currentIndex();
    g[cg].l.charsize = styleSize->value();
    g[cg].l.vgap = styleSpacing->currentIndex() + 1;
    g[cg].l.len = styleWidth->currentIndex() + 1;

    g[cg].l.box = frame->isChecked() ? ON : OFF;

    g[cg].l.boxlcolor = frameColor->currentIndex();
    g[cg].l.boxlinew = frameWidth->currentIndex();
    g[cg].l.boxlines = frameStyle->currentIndex();

    g[cg].l.boxfill = frameFill->isChecked() ? ON : OFF;
    g[cg].l.boxfillcolor = frameFillColor->currentIndex();
    g[cg].l.boxfillpat = frameFillPattern->currentIndex();
    g[cg].l.boxfillusing = frameFillColor->currentIndex() == 1 ? PATTERN : COLOR;

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
