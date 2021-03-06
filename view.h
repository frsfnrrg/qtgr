#ifndef MENUVIEW_H
#define MENUVIEW_H

#include "menu.h"

class ViewAxis;
class ViewLegend;
class ViewTitle;
class ViewFrame;
class ViewSymbols;
class ViewDimensions;
class ViewText;

class MainWindow;

class ViewMenu : public Menu
{
    Q_OBJECT
    
public:
    ViewMenu(MainWindow* );

    void populateMenu(QMenu* q);

    void updateSymbolsLegend();
    void updateIndividualLegend(int cset);

    void axis(int axis);
protected:
    void populateToolBar(QToolBar*);
  
public slots:
    void symbols();
    void axis();
    void legends();
    void title();
    void frame();
    void dims();
    void text();

private slots:
   
private:
    void createMenus();
    void createActions();
    
    QAction *titleAct;
    QAction *axisAct;
    QAction *symbolsAct;
    QAction *legendsAct;
    QAction *frameAct;
    QAction* dimsAct;
    QAction* textAct;

    ViewDimensions* dimsDialog;
    ViewLegend* legendsDialog;
    ViewTitle* titleDialog;
    ViewFrame* frameDialog;
    ViewSymbols* symbolsDialog;
    ViewAxis*   ticksDialog;
    ViewText* textDialog;
};

#endif
