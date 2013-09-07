#include "view/legends.h"
#include "base/globals.h"
#include "prop.h"
#include "view.h"
#include "choosers.h"
#include "graphwidget.h"
#include "util.h"

ViewLegends::ViewLegends(MainWindow* mainWin) :
    Dialog(mainWin, "Legends", this)
{
    legendsEditDialog = NULL;
    legendsFrameDialog = NULL;

    // make input fields
    locType = new QComboBox;
    locType->addItem(tr("Viewport"));
    locType->addItem(tr("World"));

    legendX = new QLineEdit();
    legendY = new QLineEdit();
    legendX->setMaximumWidth(100);
    legendY->setMaximumWidth(100);

    showLegend = new QCheckBox("Show Legend");

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
    styleFrame = new QComboBox();
    styleFrame->addItem("None");
    styleFrame->addItem("Enabled");

    autoHook(showLegend);
    autoHook(legendX);
    autoHook(legendY);
    autoHook(locType);

    autoHook(styleFont);
    autoHook(styleColor);
    autoHook(styleSize);
    autoHook(styleWidth);
    autoHook(styleSpacing);
    autoHook(styleFrame);

    QPushButton* editLegend = makeButton("Edit Legend Text", SLOT(legendsEdit()));

    QPushButton* place  = makeButton("Place", SLOT(placeLegends()));

    QPushButton* frame = makeButton("Frame Props", SLOT(legendsFrame()));

    QGridLayout* layout = new QGridLayout();

    QHBoxLayout* top = new QHBoxLayout();
    top->addWidget(showLegend);
    top->addSpacing(4);
    top->addWidget(editLegend);

    layout->addLayout(top, 0, 0, 1, 4, Qt::AlignLeft);


    // box for main settings??
    layout->setRowMinimumHeight(1, 12);

    const int sp = 0;
    const int sm = sp+1;

    const int pp = 3;
    const int pm = pp+1;


    layout->addWidget(makeLabel("Location"), 2, pp, 1, 2, Qt::AlignHCenter);
    layout->addWidget(makeLabel("Coord Type"), 3, pp);
    layout->addWidget(locType, 3, pm);
    layout->addWidget(makeLabel("X Pos"), 4, pp);
    layout->addWidget(legendX, 4, pm);
    layout->addWidget(makeLabel("Y Pos"), 5, pp);
    layout->addWidget(legendY, 5, pm);
    place->setMinimumWidth(80);
    layout->addWidget(place, 6, pm, Qt::AlignHCenter);

    layout->setColumnMinimumWidth(2, 20);

    layout->addWidget(makeLabel("Style"), 2, sp, 1, 2, Qt::AlignHCenter);
    layout->addWidget(makeLabel("Font"), 3, sp);
    layout->addWidget(styleFont, 3, sm);
    layout->addWidget(makeLabel("Text Color"), 4, sp);
    layout->addWidget(styleColor, 4, sm);
    layout->addWidget(makeLabel("Text Size"), 5, sp);
    layout->addWidget(styleSize, 5, sm);
    layout->addWidget(makeLabel("Width"), 6, sp);
    layout->addWidget(styleWidth, 6, sm);
    layout->addWidget(makeLabel("Spacing"), 7, sp);
    layout->addWidget(styleSpacing, 7, sm);
    layout->addWidget(makeLabel("Frame"), 8, sp);
    layout->addWidget(styleFrame, 8, sm);
    frame->setMinimumWidth(80);
    layout->addWidget(frame, 9, sm, Qt::AlignHCenter);

    layout->setColumnMinimumWidth(0, 80);
    layout->setColumnMinimumWidth(1, 100);

    layout->setColumnMinimumWidth(3, 80);
    layout->setColumnMinimumWidth(4, 100);

    layout->setColumnStretch(5, 0);

    this->setDialogLayout(layout);
}

void ViewLegends::updateDialog() {
    int gno;
     legend leg;

    gno = cg; // current graph only

    get_graph_legend(gno,&leg);

    showLegend->setChecked(g[gno].l.active == ON);
    if (g[gno].l.loctype == VIEW) {
        locType->setCurrentIndex(0);
    } else {
        locType->setCurrentIndex(1);
    }
    legendX->setText(QString::number(g[gno].l.legx,'g',9));
    legendY->setText(QString::number(g[gno].l.legy,'g',9));

    styleFont->setCurrentIndex(g[gno].l.font);
    styleColor->setCurrentIndex(g[gno].l.color);
    styleSize->setValue(g[gno].l.charsize);
    styleSpacing->setCurrentIndex(g[gno].l.vgap - 1);
    styleWidth->setCurrentIndex(g[gno].l.hgap - 1);
    styleFrame->setCurrentIndex(g[gno].l.box == ON ? 1 : 0);
}

void ViewLegends::applyDialog() {
    int gno,axis;
    legend leg;

    gno = cg; // current graph only

    get_graph_legend(gno,&leg);

  //     printf("ApplyLegends %i %f %f\n",leg.active == ON, leg.legx, leg.legy);

    if (showLegend->isChecked()) {
        g[gno].l.active = ON;
    } else {
        g[gno].l.active = OFF;
    }

    if (locType->currentIndex() == 0) {
        g[gno].l.loctype = VIEW;
    } else {
        g[gno].l.loctype = WORLD;
    }

    g[gno].l.legx = legendX->text().toDouble();
    g[gno].l.legy = legendY->text().toDouble();

    g[gno].l.font = styleFont->currentIndex();
    g[gno].l.color = styleColor->currentIndex();
    g[gno].l.charsize = styleSize->value();
    g[gno].l.vgap = styleSpacing->currentIndex() + 1;
    g[gno].l.hgap = styleWidth->currentIndex() + 1;
    g[gno].l.box = styleFrame->currentIndex() == 0 ? OFF : ON;

    drawgraph();
}


class MouseClickCall : public MouseCallBack
{
public:
    ViewLegends* view;

    void mouse( int x, int y, int w, int h )
    {
    printf("mouse_callback %f %f \n" ,double(x)/w,1.0-double(y)/h);
    view->mainWindow->gwidget->mouseClickCall = NULL;
    view->mainWindow->gwidget->unsetCursor();
    view->mainWindow->statusBar()->clearMessage();

    // TODO: make this depend on world coords/view coords
    // based on the options
    view->legendX->setText(QString::number(double(x)/w,'g',3));
    view->legendY->setText(QString::number(1.0-double(y)/h,'g',3));
    view->applyDialog();

    }
} mouseClick;

void ViewLegends::placeLegends()
{
    mouseClick.view = this;
    mainWindow->gwidget->mouseClickCall =  &mouseClick;
    mainWindow->gwidget->setCursor(Qt::CrossCursor);
    mainWindow->statusBar()->showMessage(tr("Click to place legend"));
}

void ViewLegends::updateLegendsField(int cset) {
    if (legendsEditDialog) {
        int gno = cg;
        legendsEditDialog->setLabels[cset]->setText(QString::fromLocal8Bit(g[gno].l.str[cset].s));
    }
}


void ViewLegends::legendsEdit()
{
    if (showDialog(legendsEditDialog)) return;
    legendsEditDialog = new ViewLegendsEdit(mainWindow);
    loadDialog(legendsEditDialog);
}

void ViewLegends::legendsFrame()
{
    if (showDialog(legendsFrameDialog)) return;
    legendsFrameDialog = new ViewLegendsFrame(mainWindow);
    loadDialog(legendsFrameDialog);
}

ViewLegendsEdit::ViewLegendsEdit(MainWindow *mainWin) :
    Dialog(mainWin, "Edit legend labels", true)
{
    this->setMaximumHeight(300);
    this->setMinimumWidth(400);

    // central widget for legend labels
    QScrollArea* scrollArea = new QScrollArea;
    QWidget* widget = new QWidget();
    QGridLayout* layout = new QGridLayout();

    for (int i=0; i<MAXPLOT; i++) {
        setLabels[i] = new QLineEdit();
        setLabels[i]->setMinimumWidth(240);
        layout->addWidget(new QLabel(QString("Set ")+QString::number(i)),i,0);
        layout->addWidget(setLabels[i],i,1);
        autoHook(setLabels[i]);
    }

    widget->setLayout(layout);
    scrollArea->setWidget(widget);

    // put everything together
    QGridLayout* lay = new QGridLayout();
    lay->addWidget(scrollArea,0,0,1,5);

    layout->addWidget(new QLabel(""),1,0);

    layout->setColumnMinimumWidth(0,80);
    layout->setColumnMinimumWidth(1,80);
    layout->setColumnMinimumWidth(2,80);
    layout->setColumnMinimumWidth(3,80);
    layout->setColumnMinimumWidth(4,80);

    this->setDialogLayout(lay);
}

void ViewLegendsEdit::updateDialog()
{
    int gno;

    gno = cg; // current graph only

    for (int i=0; i<MAXPLOT; i++) {
       setLabels[i]->setText(QString::fromLocal8Bit(g[gno].l.str[i].s));
    }
}

void ViewLegendsEdit::applyDialog()
{
    int gno;

    gno = cg; // current graph only

    for (int i=0; i<MAXPLOT; i++) {
        strcpy((char*)g[gno].l.str[i].s,setLabels[i]->text().toAscii().data());
    }

    drawgraph();

    // send update to set selectors
    SetsSender::send();

    this->mainWindow->viewMenu->updateSymbolsLegend();
}


ViewLegendsFrame::ViewLegendsFrame(MainWindow *mainWin) :
    Dialog(mainWin, "Legend Frame", true)
{
    frameColor = new ColorComboBox();
    frameWidth = makeWidthSelector();
    frameStyle = makeLineStyler();

    frameFill = new QCheckBox(tr("Fill frame"));
    connect(frameFill, SIGNAL(toggled(bool)), this, SLOT(resetFill()));

    frameFillColor = new ColorComboBox();
    frameFillPattern = new PatternComboBox();
    frameFillColorLabel = makeLabel("Fill Color");
    frameFillPatternLabel = makeLabel("Fill Pattern");
    resetFill();

    autoHook(frameColor);
    autoHook(frameWidth);
    autoHook(frameStyle);
    autoHook(frameFill);
    autoHook(frameFillColor);
    autoHook(frameFillPattern);

    QGridLayout* layout = new QGridLayout();
    addPair(layout, 0, makeLabel("Line Color"), frameColor);
    addPair(layout, 1, makeLabel("Line Width"), frameWidth);
    addPair(layout, 2, makeLabel("Line Style"), frameStyle);
    layout->addWidget(frameFill, 3, 0, 1, 2, Qt::AlignRight);
    addPair(layout, 4, frameFillColorLabel, frameFillColor);
    addPair(layout, 5, frameFillPatternLabel, frameFillPattern);

    setDialogLayout(layout);
}

void ViewLegendsFrame::resetFill() {
    bool on = frameFill->isChecked();
    frameFillColor->setEnabled(on);
    frameFillPattern->setEnabled(on);
    frameFillColorLabel->setEnabled(on);
    frameFillPatternLabel->setEnabled(on);
}

void ViewLegendsFrame::updateDialog() {
    int gno = cg;
    frameColor->setCurrentIndex(g[gno].l.boxlcolor);
    frameWidth->setCurrentIndex(g[gno].l.boxlinew);
    frameStyle->setCurrentIndex(g[gno].l.boxlines);

    frameFill->setChecked(g[gno].l.boxfill == ON);
    frameFillColor->setCurrentIndex(g[gno].l.boxfillcolor);
    frameFillPattern->setCurrentIndex(g[gno].l.boxfillpat);
}


void ViewLegendsFrame::applyDialog() {
    int gno = cg;

    g[gno].l.boxlcolor = frameColor->currentIndex();
    g[gno].l.boxlinew = frameWidth->currentIndex();
    g[gno].l.boxlines = frameStyle->currentIndex();

    g[gno].l.boxfill = frameFill->isChecked() ? ON : OFF;
    g[gno].l.boxfillcolor = frameFillColor->currentIndex();
    g[gno].l.boxfillpat = frameFillPattern->currentIndex();
    g[gno].l.boxfillusing = frameFillPattern->currentIndex() == 0 ? COLOR : PATTERN;

    drawgraph();
}

