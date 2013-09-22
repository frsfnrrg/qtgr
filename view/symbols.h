#ifndef VIEWSYMBOLS_H
#define VIEWSYMBOLS_H

#include <QtGui>
#include "dialog.h"

class ViewSymbols : public Dialog
{
  Q_OBJECT
  
  public:	
    ViewSymbols(MainWindow* mainWin);

    void updateLegend();

  private:
    QComboBox* setNumber;

    QComboBox* symbolSymbol;
    QComboBox* symbolFill;
    QLabel* symbolFillLabel;
    DoubleSpinBox* symbolSize;
    QLabel* symbolSizeLabel;
    IntegerSpinBox* symbolSkip;
    QLabel* symbolSkipLabel;

    QComboBox* lineStyle;
    QComboBox* lineWidth;
    QLabel* lineWidthLabel;
    QComboBox* lineColor;
    QLabel* lineColorLabel;

    QComboBox* fillFill;
    QComboBox* fillColor;
    QLabel* fillColorLabel;
    QComboBox* fillPattern;
    QLabel* fillPatternLabel;

    QLineEdit* legendS;
    
  public slots:
    void updateDialog();
   
  private slots:	
    void applyDialog();
    void updateSymbolFade();
    void updateLineFade();
    void updateFillFade();
};

#endif
