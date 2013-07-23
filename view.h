/****************************************************************************

****************************************************************************/

#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <QtGui>
#include "mainwindow.h"
#include "view_symbols.h"
#include "view_ticks.h"
#include "view_world.h"


QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class ViewMenu : public QMenu
{
    Q_OBJECT
    
    static const int maxsets = 16; //FIXME


public:
    MainWindow *mainWindow;
    ViewMenu(MainWindow* );
    
    ViewSymbols* symbolsDialog;
    ViewTicks*   ticksDialog;
    ViewWorld*   worldDialog;

    QLineEdit* legendX;
    QLineEdit* legendY;   

    void updateSymbols();
    void updateTicks();
    void updateWorld();
    
protected:
  
  
public slots:
    void world();
    void symbols();
    void ticks();
    void legends();
    void applyLegends();


private slots:

//     void updateSymbols();
//     void applySymbols();
//     void doneSymbols();

 
    void doneLegends();
    void placeLegends();
    void legendsEdit();
    void applyLegendsEdit();
    void doneLegendsEdit();
   


private:

    void createMenus();
    void createActions();
   
    int set_mode;
    
    QAction *worldAct;
    QAction *titleAct;
    QAction *ticksAct;
    QAction *symbolsAct;
    QAction *legendsAct;
    

    
    
// //     QDialog* symbolsDialog;
//     QComboBox* setNumber;
//     QComboBox* symbolSymbol;
//     QComboBox* symbolFill;
//     QComboBox* lineWidth;
//     QComboBox* lineStyle;
//     QComboBox* lineColor;
//     QLineEdit* legendS;


    
    QDialog* legendsDialog;
    QCheckBox* showLegend;
    QComboBox *locType;

    void updateLegends();
    
    QDialog* legendsEditDialog;
    QLineEdit* setLabels[ViewMenu::maxsets];
    void updateLegendsEdit();
   
};

#endif
