#ifndef VIEWSYMBOLS_H
#define VIEWSYMBOLS_H

#include <QtGui>
#include "mainwindow.h"
#include "dialog.h"

class ViewSymbols : public Dialog
{
  Q_OBJECT
  
  public:	
    ViewSymbols(MainWindow* mainWin);

  private:
    QComboBox* setNumber;
    QComboBox* symbolSymbol;
    QComboBox* symbolFill;
    QComboBox* lineWidth;
    QComboBox* lineStyle;
    QComboBox* lineColor;
    QLineEdit* legendS;
    
  public slots:
    void updateDialog();
   
  private slots:	
    void applyDialog();
};

#endif
