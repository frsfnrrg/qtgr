#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <QtGui>
#include "mainwindow.h"
#include "view/symbols.h"
#include "view/ticks.h"
#include "view/world.h"
#include "view/graphtype.h"
#include "view/legends.h"
#include "view/viewport.h"
#include "view/title.h"
#include "view/frame.h"
#include "menu.h"

class ViewMenu : public Menu
{
    Q_OBJECT
    
public:
    ViewMenu(MainWindow* );
    
    ViewSymbols* symbolsDialog;
    ViewTicks*   ticksDialog;
    ViewWorld*   worldDialog;
    ViewGraphType* graphTypesDialog;
    ViewLegends* legendsDialog;
    ViewView* viewDialog;
    ViewTitle* titleDialog;
    ViewFrame* frameDialog;

    void populateMenu(QMenu* q);

    void updateSymbolsLegend();
    void updateIndividualLegend(int cset);
protected:
    void populateToolBar(QToolBar*);
  
public slots:
    void world();
    void symbols();
    void ticks();
    void legends();
    void graphTypes();
    void view();
    void title();
    void frame();

private slots:
   
private:
    void createMenus();
    void createActions();
    
    QAction *viewAct;
    QAction *worldAct;
    QAction *titleAct;
    QAction *ticksAct;
    QAction *symbolsAct;
    QAction *legendsAct;
    QAction *graphTypesAct;
    QAction *frameAct;
};

#endif
