#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QtGui>
#include "mainwindow.h"
#include "dialog.h"

class TransformMenu : public QMenu
{
    Q_OBJECT
public:
    explicit TransformMenu(MainWindow* mainWin);

    MainWindow* mainWindow;
    
    QToolBar* createToolBar();

private:
    void createActions();
    void createMenus();
    QAction* integrateAct;
    QAction* differentiateAct;
    QAction* evaluateAct;
    Dialog* integrateDialog;
    Dialog* differentiateDialog;
    Dialog* evaluateDialog;

signals:
    
public slots:
    void evaluate();
    void integrate();
    void differentiate();

private slots:
};

#endif // TRANSFORM_H
