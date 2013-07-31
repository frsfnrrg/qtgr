#ifndef MENUEDIT_H
#define MENUEDIT_H

#include <QtGui>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

/*
 This menu holds modification stuff,
 as well as copy-to-clipboard and paste-from-clipboard

 Adding points, deleting points, and changing set points are done from
 here
 */
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
