#ifndef SETS_H
#define SETS_H

#include <QtGui>
#include "menu.h"
#include "sets/kad.h"
#include "sets/sedit.h"
#include "sets/mcs.h"

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
    void* joinDialog;
    void* splitDialog;

    void populateMenu(QMenu* q);
    QToolBar* createToolBar();
signals:

public slots:

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
