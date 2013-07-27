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
    
private:
    void createActions();
    void createMenus();
    QAction* integrateAct;
    QAction* differentiateAct;
    Dialog* integrateDialog;
    Dialog* differentiateDialog;

signals:
    
public slots:
    void integrate();
    void differentiate();

private slots:
};

#endif // TRANSFORM_H
