#ifndef VIEWSYMBOLS_H
#define VIEWSYMBOLS_H

#include <QtGui>
#include "mainwindow.h"

class ViewSymbols : public QDialog
{
  Q_OBJECT
  
  public:	
    ViewSymbols(MainWindow* mainWin);
    
  private:
    MainWindow *mainWindow;
    
    QComboBox* setNumber;
    QComboBox* symbolSymbol;
    QComboBox* symbolFill;
    QComboBox* lineWidth;
    QComboBox* lineStyle;
    QComboBox* lineColor;
    QLineEdit* legendS;
    
  public slots:
    void updateSymbols();   
   
  private slots:	
    void applySymbols();
    void doneSymbols();
  
};

#endif