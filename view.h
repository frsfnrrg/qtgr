#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <QtGui>
#include "mainwindow.h"
#include "view_symbols.h"
#include "view_ticks.h"
#include "view_world.h"
#include "view_graphtype.h"
#include "view_legends.h"
#include "view_view.h"

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
    ViewLegends* legendsDialog;
    ViewView* viewDialog;

   // QLineEdit* legendX;
  //  QLineEdit* legendY;

    void updateSymbols();
    void updateTicks();
    void updateWorld();
    void updateLegends();
    void updateGraphTypes();
    void updateView();
    
protected:
  
  
public slots:
    void world();
    void symbols();
    void ticks();
    void legends();
    void graphTypes();
    void view();


private slots:
   
private:

    void createMenus();
    void createActions();
   
    int set_mode; // not implemented yet
    
    QAction *viewAct;
    QAction *worldAct;
    QAction *titleAct;
    QAction *ticksAct;
    QAction *symbolsAct;
    QAction *legendsAct;
    QAction *graphTypesAct;
};

#endif
