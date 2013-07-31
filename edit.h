#ifndef MENUEDIT_H
#define MENUEDIT_H

#include <QtGui>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

// NOTE: set ops (activ, deactiv) should be put in?
class EditMenu : public QMenu
{
    Q_OBJECT

public:
    EditMenu(MainWindow* );
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;

protected:
   

private slots:

private:
    MainWindow *mainWindow;
    void createMenus();
    void createActions();


   
};

#endif
