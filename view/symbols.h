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
    QComboBox* lineWidth;
    QComboBox* lineStyle;
    QComboBox* lineColor;
    QLineEdit* legendS;
    QComboBox* fillFill;
    QComboBox* fillColor;
    QComboBox* fillPattern;
    
  public slots:
    void updateDialog();
   
  private slots:	
    void applyDialog();
};

#endif
