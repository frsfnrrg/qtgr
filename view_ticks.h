#ifndef MENUVIEWTICKS_H
#define MENUVIEWTICKS_H

#include <QtGui>
#include "mainwindow.h"

class ViewTicks : public QDialog
{
  Q_OBJECT
  
  public:	
    ViewTicks(MainWindow* mainWin);
    
    QComboBox* editAxis;
    
    QDialog* labelPropsDialog;

    
  public slots:
    void updateTicks();
    
  private:
    MainWindow *mainWindow;
    
    QLineEdit *axisLabel;
    QLineEdit *majTic;
    QLineEdit *minTic;  
    
    QComboBox* labelFormat;
    QComboBox* labelPrecision;
    
    QLabel* axisName;
    
 private slots:
    void applyTicks();
    void doneTicks();
    
    void labelProps();
    void updateLabelProps();
    void applyLabelProps();
    void doneLabelProps();
  
};

#endif