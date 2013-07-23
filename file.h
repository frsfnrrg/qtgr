/****************************************************************************

****************************************************************************/

#ifndef MENUFILE_H
#define MENUFILE_H

#include <QtGui>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class FileMenu : public QMenu
{
    Q_OBJECT

public:
    FileMenu(MainWindow* );

protected:
   

private slots:
    void open();
    void clear();
    void print();
    void exportProc();
    

private:
    MainWindow *mainWindow;
    void createMenus();
    void createActions();
    QAction *readSetAct;
    QAction *readParaAct;
    QAction *readBlockAct;
    QAction *writeSetAct;
    QAction *writeParaAct;
    QAction *saveAllAct;
    QAction *clearAct;
    QAction *printAct;
    QAction *exportAct;
    QAction *printSetupAct;
    QAction *exitAct;
   
};

#endif
