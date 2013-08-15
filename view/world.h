#ifndef MENUVIEWWORLD_H
#define MENUVIEWWORLD_H

#include <QtGui>
#include "mainwindow.h"
#include "dialog.h"

class ViewWorld : public Dialog
{
  Q_OBJECT
  
  public:	
    ViewWorld(MainWindow* mainWin);

  private:
    QLineEdit *xMin;
    QLineEdit *xMax;
    QLineEdit *yMin;
    QLineEdit *yMax;
    QLineEdit *xMajTic;
    QLineEdit *xMinTic;    
    QLineEdit *yMajTic;
    QLineEdit *yMinTic;  
    
 public slots:
    void updateWorldDimensions(QObject*);
    void updateDialog();
   
 private slots:
    void applyDialog();
};

#endif
