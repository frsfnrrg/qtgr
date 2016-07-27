#ifndef SETS_H
#define SETS_H

#include "menu.h"

class SetsEdit;
class SetsKAD;
class SetsMCS;
class SetsJoin;
class SetsSplit;

/*
 This menu contains all whole-set operations:
 Join, split, kill, activate, deactivate, etc.
 */
class SetsMenu : public Menu
{
    Q_OBJECT
public:
    explicit SetsMenu(MainWindow* m);

    SetsEdit* editDialog;
    SetsKAD* kadDialog;
    SetsMCS* mcsDialog;
    SetsJoin* joinDialog;
    SetsSplit* splitDialog;

    void populateMenu(QMenu*);

protected:
    void populateToolBar(QToolBar*);

private slots:
    void edit();
    void kad();
    void mcs();
    void split();
    void join();

private:
    void createActions();

    QAction* editAct;
    QAction* kadAct;
    QAction* mcsAct;
    QAction* splitAct;
    QAction* joinAct;
};

#endif // SETS_H
