#ifndef SETS_H
#define SETS_H

#include <QtGui>
#include "mainwindow.h"
#include "sets/kad.h"
#include "sets/sedit.h"

/*
 This menu contains all whole-set operations:
 Join, split, kill, activate, deactivate, etc.
 */
class SetsMenu : public QMenu
{
    Q_OBJECT
public:
    explicit SetsMenu(MainWindow* m);

    SetsEdit* editDialog;
    SetsKAD* kadDialog;

    void populateMenu(QMenu* q);
    QToolBar* createToolBar();
signals:
    
public slots:
    void updateEdit();
    void updateKAD();

private slots:
    void edit();
    void kad();


private:
    void createActions();

    MainWindow *mainWindow;
    QAction* editAct;
    QAction* kadAct;
    QAction* moveAct;
    QAction* copyAct;
    QAction* splitAct;
    QAction* joinAct;
};

#endif // SETS_H
