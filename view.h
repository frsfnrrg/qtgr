/****************************************************************************

****************************************************************************/

#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <QtGui>
#include "mainwindow.h"
#include "view_symbols.h"
#include "view_ticks.h"
#include "view_world.h"
#include "view_graphtype.h"

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
    ViewGraphType* graphTypesDialog;

    QLineEdit* legendX;
    QLineEdit* legendY;   

    void updateSymbols();
    void updateTicks();
    void updateWorld();
    void updateGraphTypes();
    
protected:
  
  
public slots:
    void world();
    void symbols();
    void ticks();
    void legends();
    void graphTypes();
    void applyLegends();


private slots:

//     void updateSymbols();
//     void applySymbols();
//     void doneSymbols();

    // todo: bring into another class
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
    QAction *graphTypesAct;

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
