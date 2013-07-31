#ifndef SETS_H
#define SETS_H

#include <QtGui>
#include "mainwindow.h"

/*
 This menu contains all whole-set operations:
 Join, split, kill, activate, deactivate, etc.
 */
class SetsMenu : public QMenu
{
    Q_OBJECT
public:
    explicit SetsMenu(MainWindow* m);

signals:
    
public slots:


private slots:


private:
    MainWindow *mainWindow;
    
};

#endif // SETS_H
