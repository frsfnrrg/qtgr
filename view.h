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

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class ViewMenu : public QMenu
{
    Q_OBJECT
    
public:
    MainWindow *mainWindow;
    ViewMenu(MainWindow* );
    
    ViewSymbols* symbolsDialog;
    ViewTicks*   ticksDialog;
    ViewWorld*   worldDialog;
    ViewGraphType* graphTypesDialog;
    ViewLegends* legendsDialog;
    ViewView* viewDialog;
    ViewTitle* titleDialog;

    void updateSymbols();
    void updateTicks();
    void updateWorld();
    void updateLegends();
    void updateGraphTypes();
    void updateView();
    void updateTitle();

    void populateMenu(QMenu* q);

    void updateSymbolsLegend();
    void updateIndividualLegend(int cset);

    QToolBar* createToolBar();
protected:
  
  
public slots:
    void world();
    void symbols();
    void ticks();
    void legends();
    void graphTypes();
    void view();
    void title();

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
