#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QtGui>
#include "mainwindow.h"

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

signals:
    
public slots:


private slots:
};

#endif // TRANSFORM_H
