#include <iostream>
#include "view/symbols.h"
#include "view.h"
#include "base/globals.h"
#include "choosers.h"
#include "prop.h"

ViewSymbols::ViewSymbols(MainWindow* mainWin) :
    Dialog(mainWin, "Symbols", true)
{
    //make input fields
    setNumber = new SetComboBox();
    connect(setNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));
    
    // symbols inputs
    symbolSymbol = new QComboBox();
    symbolSymbol->addItem("None");
    symbolSymbol->addItem("Dot");
    symbolSymbol->addItem("Circle");
    symbolSymbol->addItem("Square");
    symbolSymbol->addItem("Diamond");
    symbolSymbol->addItem("Triangle up");
    symbolSymbol->addItem("Triangle left");
    symbolSymbol->addItem("Triangle down");
    symbolSymbol->addItem("Triangle right");
    symbolSymbol->addItem("Plus");
    symbolSymbol->addItem("X");
    symbolSymbol->addItem("Star");
    connect(symbolSymbol, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSymbolFade()));

    symbolFill = new QComboBox();
    symbolFill->addItem("None");
    symbolFill->addItem("Filled");
    symbolFill->addItem("Opaque");
    
    symbolSize = new DoubleSpinBox();
    symbolSize->setMinimum(0.0);
    symbolSize->setMaximum(4.0);
    symbolSize->setDecimals(2);
    symbolSize->setSingleStep(0.1);

    symbolSkip = new QLineEdit();

    // line inputs
    lineStyle = makeLineStyler();
    connect(lineStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(updateLineFade()));

    lineWidth = makeWidthSelector();

    lineColor = new ColorComboBox();

    // fill inputs
    fillFill = new QComboBox();
    fillFill->addItem(tr("None"));
    fillFill->addItem(tr("As polygon"));
    fillFill->addItem(tr("To Y=0"));
    fillFill->addItem(tr("To X=0"));
    fillFill->addItem(tr("To X-min"));
    fillFill->addItem(tr("To X-max"));
    fillFill->addItem(tr("To Y-max"));
    fillFill->addItem(tr("To Y-min"));
    connect(fillFill, SIGNAL(currentIndexChanged(int)), this, SLOT(updateFillFade()));

    fillColor = new ColorComboBox();
    
    fillPattern = new PatternComboBox();
    
    legendS = new QLineEdit();
    legendS->setMaximumWidth(300); 

    autoHook(fillColor);
    autoHook(legendS);
    autoHook(fillColor);
    autoHook(fillFill);
    autoHook(lineColor);
    autoHook(lineWidth);
    autoHook(lineStyle);
    autoHook(symbolFill);
    autoHook(symbolSymbol);
    autoHook(symbolSize);
    autoHook(symbolSkip);

    symbolFillLabel = makeLabel("Fill:");
    symbolSizeLabel = makeLabel("Size:");
    symbolSkipLabel = makeLabel("Skip:");
    lineWidthLabel = makeLabel("Width:");
    lineColorLabel = makeLabel("Color:");
    fillColorLabel = makeLabel("Color:");
    fillPatternLabel = makeLabel("Pattern:");

    updateFillFade();
    updateLineFade();
    updateSymbolFade();

    QGridLayout* layout = new QGridLayout();
	
    layout->addWidget(new QLabel("Select Set:"),0,0);
    layout->addWidget(setNumber,0,1);

    layout->setRowMinimumHeight(1, 8);
    
    layout->addWidget(new QLabel("Symbols"),2,0,1,2,Qt::AlignHCenter);
    layout->addWidget(new QLabel("Lines"),2,3,1,2,Qt::AlignHCenter);
    layout->addWidget(new QLabel("Fills"),2,6,1,2,Qt::AlignHCenter);
    
    //symbols details
    layout->addWidget(new QLabel("Symbol:"),3,0);
    layout->addWidget(symbolFillLabel,4,0);
    layout->addWidget(symbolSizeLabel,5,0);
    layout->addWidget(symbolSkipLabel,6,0);
    
    layout->addWidget(symbolSymbol,3,1);
    layout->addWidget(symbolFill,4,1);
    layout->addWidget(symbolSize,5,1);
    layout->addWidget(symbolSkip,6,1);

    // horizontal spacer
    layout->setColumnMinimumWidth(2, 22);
    
    //lines details
    layout->addWidget(new QLabel("Style"),3,3);
    layout->addWidget(lineWidthLabel,4,3);
    layout->addWidget(lineColorLabel,5,3);
    layout->addWidget(lineStyle,3,4);
    layout->addWidget(lineWidth,4,4);
    layout->addWidget(lineColor,5,4);
    
    // horizontal spacer
    layout->setColumnMinimumWidth(5, 22);
    
    //fills details
    layout->addWidget(new QLabel("Fill"),3,6);
    layout->addWidget(fillColorLabel,4,6);
    layout->addWidget(fillPatternLabel,5,6);
    layout->addWidget(fillFill,3,7);
    layout->addWidget(fillColor,4,7);
    layout->addWidget(fillPattern,5,7);

    layout->setRowMinimumHeight(7, 12);

    // where should this go??
    layout->addWidget(new QLabel("Legend:"),8,0);
    layout->addWidget(legendS,8,1,1,3);

    this->setDialogLayout(layout);
}  
  
void ViewSymbols::updateDialog()
{
    int gno,cset,iv;
    gno = cg; // current graph only 
      
    cset = setNumber->currentIndex();
    
    iv = 100.0 * g[gno].p[cset].symsize;
    symbolSymbol->setCurrentIndex(g[gno].p[cset].sym);
    symbolFill->setCurrentIndex(g[gno].p[cset].symfill);
    symbolSize->setValue(g[gno].p[cset].symsize);
    symbolSkip->setText(QString::number(g[gno].p[cset].symskip,'g',9));

    lineStyle->setCurrentIndex(g[gno].p[cset].lines);
    lineWidth->setCurrentIndex(g[gno].p[cset].linew-1);
    lineColor->setCurrentIndex(g[gno].p[cset].color);
    
    legendS->setText(QString::fromLocal8Bit(g[gno].l.str[cset].s));

    fillFill->setCurrentIndex(g[gno].p[cset].fill);
    if (g[gno].p[cset].fillusing == COLOR) {
        fillPattern->setCurrentIndex(0);
    } else {
        fillPattern->setCurrentIndex(g[gno].p[cset].fillpattern);
    }
    fillColor->setCurrentIndex(g[gno].p[cset].fillcolor);
}
  

void ViewSymbols::updateLegend() {
    int gno = cg;
    int cset = setNumber->currentIndex();
    legendS->setText(QString::fromLocal8Bit(g[gno].l.str[cset].s));
}

void ViewSymbols::applyDialog()
{
    int cset, sym, symskip=0, symfill, style, color, wid, fill, fillpat, fillusing, fillcol;
    double symsize;
    
    cset = setNumber->currentIndex();

    sym     = symbolSymbol->currentIndex();
    symfill = symbolFill->currentIndex();
    symsize = symbolSize->value();

    double val;
    if (leVal(symbolSkip, &val) && val >= 0)
        symskip = val;
    else
        symskip = g[cg].p[cset].symskip;

    wid   = lineWidth->currentIndex()+1;
    style = lineStyle->currentIndex();
    color = lineColor->currentIndex();

    fill = fillFill->currentIndex();
    fillpat = fillPattern->currentIndex();
    if (fillpat == 0) {
        fillusing = COLOR;
    } else {
        fillusing = PATTERN;
    }
    fillcol = fillColor->currentIndex();
    strcpy((char*)g[cg].l.str[cset].s,legendS->text().toAscii().data());		

    // Note: there is an apply-to-all-sets option
    // in XVGR

    printf("fill %i %i %i %i\n", fill, fillusing, fillcol, fillpat);

    set_prop(cg, SET,
	     SETNUM, cset,
	     SYMBOL, TYPE, sym,
	     SYMBOL, FILL, symfill,
         SYMBOL, SIZE, symsize,
         SKIP, symskip,
	     LINESTYLE, style,
	     LINEWIDTH, wid,
	     COLOR, color,
         FILL, TYPE, fill,
         FILL, WITH, fillusing,
         FILL, COLOR, fillcol,
         FILL, PATTERN, fillpat,
	     0); 

    drawgraph();

    //update set selection dialogs
    SetsSender::send();
    mainWindow->viewMenu->updateIndividualLegend(cset);
}

void ViewSymbols::updateSymbolFade() {
    bool on = symbolSymbol->currentIndex() != 0;
    bool ss = lineStyle->currentIndex() != 0;
    symbolFill->setEnabled(on);
    symbolSize->setEnabled(on);
    symbolSkip->setEnabled(on);
    symbolFillLabel->setEnabled(on);
    symbolSizeLabel->setEnabled(on);
    symbolSkipLabel->setEnabled(on);
    lineColor->setEnabled(on || ss);
    lineColorLabel->setEnabled(on || ss);
}

void ViewSymbols::updateLineFade() {
    bool on = lineStyle->currentIndex() != 0;
    bool ff = symbolSymbol->currentIndex() != 0;
    lineWidth->setEnabled(on);
    lineWidthLabel->setEnabled(on);
    lineColor->setEnabled(on || ff);
    lineColorLabel->setEnabled(on || ff);
}

void ViewSymbols::updateFillFade() {
    bool on = fillFill->currentIndex() != 0;
    fillColor->setEnabled(on);
    fillPattern->setEnabled(on);
    fillColorLabel->setEnabled(on);
    fillPatternLabel->setEnabled(on);
}
