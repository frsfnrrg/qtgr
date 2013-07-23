/****************************************************************************

****************************************************************************/

#ifndef MENUTOOLS_H
#define MENUTOOLS_H

#include <QtGui>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class ToolsMenu : public QMenu
{
    Q_OBJECT

public:
    ToolsMenu(MainWindow* );

protected:
   

private slots:
    void autoScale();
    

private:
    MainWindow *mainWindow;
    void createMenus();
    void createActions();
    QAction *autoScaleAct;
    QAction *worldAct;
//     QAction *viewAct;

   
};

#endif
