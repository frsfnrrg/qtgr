#ifndef MENUVIEW_H
#define MENUVIEW_H

#include "mainwindow.h"
#include "menu.h"

class ViewTicks;
class ViewLegends;

class ViewTitle;
class ViewFrame;
class ViewSymbols;

class ViewGraphType;
class ViewWorld;
class ViewView;

class ViewDimensions;

class ViewMenu : public Menu
{
    Q_OBJECT
    
public:
    ViewMenu(MainWindow* );

    ViewTicks*   ticksDialog;

    void populateMenu(QMenu* q);

    void updateSymbolsLegend();
    void updateIndividualLegend(int cset);
protected:
    void populateToolBar(QToolBar*);
  
public slots:
    void symbols();
    void ticks();
    void legends();
    void title();
    void frame();

//    void world();
//    void graphTypes();
//    void view();

    void dims();

private slots:
   
private:
    void createMenus();
    void createActions();
    
    QAction *titleAct;
    QAction *ticksAct;
    QAction *symbolsAct;
    QAction *legendsAct;
    QAction *frameAct;

    QAction* dimsAct;

//    QAction *viewAct;
//    QAction *worldAct;
//    QAction *graphTypesAct;

//    ViewWorld*   worldDialog;
//    ViewView* viewDialog;
//    ViewGraphType* graphTypesDialog;

    ViewDimensions* dimsDialog;

    ViewLegends* legendsDialog;
    ViewTitle* titleDialog;
    ViewFrame* frameDialog;
    ViewSymbols* symbolsDialog;
};

#endif
