#ifndef MENUVIEWTICKS_H
#define MENUVIEWTICKS_H

#include <QtGui>
#include "dialog.h"

class ViewTicks : public Dialog
{
  Q_OBJECT
  
  public:	
    ViewTicks(MainWindow* mainWin);
    
    QComboBox* editAxis;
    
    QDialog* labelPropsDialog;

  public slots:
    void updateDialog();
    
  private:
    
    QLineEdit *axisLabel;
    QLineEdit *majTic;
    QLineEdit *minTic;  
    
    QComboBox* labelFormat;
    QComboBox* labelPrecision;
    
    QLabel* axisName;
    
 private slots:
    void applyDialog();

    void labelProps();
    void updateLabelProps();
    void applyLabelProps();
    void doneLabelProps();
};

#endif
