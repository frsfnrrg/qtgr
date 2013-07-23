#ifndef MENUVIEWWORLD_H
#define MENUVIEWWORLD_H

#include <QtGui>
#include "mainwindow.h"

class ViewWorld : public QDialog
{
  Q_OBJECT
  
  public:	
    ViewWorld(MainWindow* mainWin);
    
  private:
    MainWindow *mainWindow;
    
    QLineEdit *xMin;
    QLineEdit *xMax;
    QLineEdit *yMin;
    QLineEdit *yMax;
    QLineEdit *xMajTic;
    QLineEdit *xMinTic;    
    QLineEdit *yMajTic;
    QLineEdit *yMinTic;  
    
 public slots:
    void updateWorld();
   
 private slots:
   
    void applyWorld();
    void doneWorld();
  
};

#endif