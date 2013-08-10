#ifndef MENUFILE_H
#define MENUFILE_H

#include <QtGui>
#include "menu.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class FileMenu : public Menu
{
    Q_OBJECT

public:
    FileMenu(MainWindow* );

    void populateMenu(QMenu*);

public slots:
    void open();
    void clear();
    void print();

protected:
    void populateToolBar(QToolBar*);

private slots:
    void exportProc();

private:
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
