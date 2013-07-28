#include <iostream>
#include "view/symbols.h"
#include "view.h"
#include "core/globals.h"

ViewSymbols::ViewSymbols(MainWindow* mainWin) : Dialog(mainWin, tr("Symbols"))
{
    const int maxwidths = 9; //FIXME
    const int maxpatterns = 16; //FIXME
    const int maxcolors = 16; //FIXME
	       
    //make input fields
    setNumber = new QComboBox;
    for (int i=0; i<MAXPLOT; i++) {
      setNumber->addItem(QString::number(i));
    }
    connect(setNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));
    
    // symbols inputs
    symbolSymbol = new QComboBox;
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
    symbolFill = new QComboBox;
    symbolFill->addItem("None");
    symbolFill->addItem("Filled");
    
    // line inputs
    lineStyle = new QComboBox;
    lineStyle->addItem("None");
    lineStyle->addItem("Solid");
    lineStyle->addItem("Dashed");
    lineStyle->addItem("Dotted");
    lineStyle->addItem("Dash-Dot");
    lineStyle->addItem("Dash-DotDot");
    lineWidth = new QComboBox;
    for (int i=1; i<=maxwidths; i++) {
      lineWidth->addItem(QString::number(i));
    }
    
    QIcon colorIcon;
    QPixmap colorPix = QPixmap(20,20);
    colorPix.fill(this->mainWindow->gwidget->cmscolors[0]);
    colorIcon.addPixmap(colorPix);
    
    lineColor = new QComboBox;
    for (int i=0; i<maxcolors; i++) {
      colorPix.fill(this->mainWindow->gwidget->cmscolors[i]);
      colorIcon.addPixmap(colorPix);
      lineColor->addItem(colorIcon,"");
    }

    // fill inputs
    QComboBox* fillFill = new QComboBox;
    QComboBox* fillStyle = new QComboBox;
    QComboBox* fillColor = new QComboBox;
    
    QComboBox* fillPattern = new QComboBox;
    for (int i=0; i<maxpatterns; i++) {
      fillPattern->addItem(QString::number(i));
    }
    
    legendS = new QLineEdit();
    legendS->setMaximumWidth(300); 

    QGridLayout* layout = new QGridLayout();
	
    layout->addWidget(new QLabel("Select Set:"),0,0);
    layout->addWidget(setNumber,0,1);
    layout->addWidget(new QLabel(""),1,0);
    
    layout->addWidget(new QLabel("Symbols"),2,0,1,2,Qt::AlignHCenter);
    layout->addWidget(new QLabel("Lines"),2,3,1,2,Qt::AlignHCenter);
    layout->addWidget(new QLabel("Fills"),2,6,1,2,Qt::AlignHCenter);
    
    //symbols details
    layout->addWidget(new QLabel("Symbol:"),3,0);
    layout->addWidget(new QLabel("Fill:"),4,0);
    layout->addWidget(new QLabel("Size:"),5,0);
    layout->addWidget(new QLabel("Char:"),6,0);
    layout->addWidget(new QLabel("Skip:"),7,0);
    layout->addWidget(new QLabel("Legend:"),8,0);
    
    layout->addWidget(symbolSymbol,3,1);
    layout->addWidget(symbolFill,4,1);
    
    layout->addWidget(legendS,8,1,1,3);
    
    
    // horizontal spacer
    layout->addWidget(new QLabel(" "),3,2,1,1);
    
    //lines details
    layout->addWidget(new QLabel("Style"),3,3);
    layout->addWidget(new QLabel("Width"),4,3);
    layout->addWidget(new QLabel("Color"),5,3);
    layout->addWidget(lineStyle,3,4);
    layout->addWidget(lineWidth,4,4);
    layout->addWidget(lineColor,5,4);
    
    // horizontal spacer
    layout->addWidget(new QLabel(" "),3,5,1,1);
    
    //fills details
    layout->addWidget(new QLabel("Fill"),3,6);
    layout->addWidget(new QLabel("Style"),4,6);
    layout->addWidget(new QLabel("Color"),5,6);
    layout->addWidget(new QLabel("Pattern"),6,6);
    layout->addWidget(fillFill,3,7);
    layout->addWidget(fillStyle,4,7);
    layout->addWidget(fillColor,5,7);
    layout->addWidget(fillPattern,6,7);

    this->setDialogLayout(layout);
  
    // are these necessary?? Should be called from the outside...
    // or, should all things show on construction?
//    this->show();

//    updateDialog();
}  
  
void ViewSymbols::updateDialog()
{
  
    int gno,cset,iv; 
    gno = cg; // current graph only 
      
//      printf("updateSymbols %i %i\n",g[gno].p[cset].linew,g[gno].p[cset].lines);
    cset = setNumber->currentIndex();
    
    iv = 100.0 * g[gno].p[cset].symsize;
    symbolSymbol->setCurrentIndex(g[gno].p[cset].sym);
    symbolFill->setCurrentIndex(g[gno].p[cset].symfill);
// 	xv_set(symsize_item, PANEL_VALUE, iv, NULL);
// 	xv_set(toggle_symset_item, PANEL_VALUE, value, NULL);
// 	xv_set(symskip_item, PANEL_VALUE, g[gno].p[value].symskip, NULL);
// 	if (g[gno].p[value].symchar > ' ' && g[gno].p[value].symchar < 127) {
// 	    s[0] = g[gno].p[value].symchar;
// 	    s[1] = 0;
// 	} else {
// 	    s[0] = 0;
// 	}
// 	xv_set(symchar_item, PANEL_VALUE, s, NULL);
// 	xv_set(toggle_symbols_item, PANEL_VALUE, getsetplotsym(gno, value), NULL);

    lineStyle->setCurrentIndex(g[gno].p[cset].lines);
    lineWidth->setCurrentIndex(g[gno].p[cset].linew-1);
    lineColor->setCurrentIndex(g[gno].p[cset].color);
    
    legendS->setText(QString::fromLocal8Bit(g[gno].l.str[cset].s));
// 	xv_set(toggle_fill_item, PANEL_VALUE, g[gno].p[value].fill, NULL);
// 	xv_set(toggle_fillusing_item, PANEL_VALUE, g[gno].p[value].fillusing == COLOR ? 0 : 1, NULL);
// 	xv_set(toggle_fillcol_item, PANEL_VALUE, g[gno].p[value].fillcolor, NULL);
// 	xv_set(toggle_fillpat_item, PANEL_VALUE, g[gno].p[value].fillpattern, NULL);
// 	updatelegendstr(gno);
// 	updateerrbar(gno, value);
    
    update();
}
  
void ViewSymbols::applyDialog()
{
    int cset, sym, symchar, symskip, symfill, style, color, wid, fill, fillpat, fillusing, fillcol, i;
    double symsize;
    char s[30];
    
    cset = setNumber->currentIndex();
    
//     int value = (int) xv_get(symsize_item, PANEL_VALUE);
// 
//     symsize = value / 100.0;
    sym     = symbolSymbol->currentIndex();
    symfill = symbolFill->currentIndex();
//     pen = (int) xv_get(toggle_color_item, PANEL_VALUE);
    wid   = lineWidth->currentIndex()+1;
    style = lineStyle->currentIndex();
    color = lineColor->currentIndex();
//     fill = (int) xv_get(toggle_fill_item, PANEL_VALUE);
//     fillusing = (int) xv_get(toggle_fillusing_item, PANEL_VALUE) ? PATTERN : COLOR;
//     fillpat = (int) xv_get(toggle_fillpat_item, PANEL_VALUE);
//     fillcol = (int) xv_get(toggle_fillcol_item, PANEL_VALUE);
//     symskip = (int) xv_get(symskip_item, PANEL_VALUE);
    strcpy((char*)g[cg].l.str[cset].s,legendS->text().toAscii().data());		
//     symchar = s[0];
//     load_ledit(cg, cset);
//     if (set_mode == 0) {
// 	setno = cset;
//     } else {
// 	setno = -1;
//     }

    set_prop(cg, SET,
	     SETNUM, cset,
	     SYMBOL, TYPE, sym,
	     SYMBOL, FILL, symfill,
// 	     SYMBOL, SIZE, symsize,
// 	     SYMBOL, CHAR, symchar,
// 	     SKIP, symskip,
	     LINESTYLE, style,
	     LINEWIDTH, wid,
	     COLOR, color,
// 	     FILL, TYPE, fill,
// 	     FILL, WITH, fillusing,
// 	     FILL, COLOR, fillcol,
// 	     FILL, PATTERN, fillpat,
	     0);
   // updatesymbols(cg, cset);
    
    
    drawgraph();    
}
