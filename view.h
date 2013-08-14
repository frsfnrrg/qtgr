#ifndef MENUVIEW_H
#define MENUVIEW_H

#include "mainwindow.h"
#include "menu.h"

class ViewTicks;
class ViewWorld;
class ViewGraphType;
class ViewLegends;
class ViewView;
class ViewTitle;
class ViewFrame;
class ViewSymbols;

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

    ViewWorld*   worldDialog;
    ViewGraphType* graphTypesDialog;
    ViewLegends* legendsDialog;
    ViewView* viewDialog;
    ViewTitle* titleDialog;
    ViewFrame* frameDialog;
    ViewSymbols* symbolsDialog;
};

#endif
