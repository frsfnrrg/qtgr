#ifndef MENUEDIT_H
#define MENUEDIT_H

#include <QtGui>
#include "menu.h"

class EditMenu : public Menu
{
    Q_OBJECT

public:
    EditMenu(MainWindow* );
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;

    void populateMenu(QMenu*);
    QToolBar* createToolBar();

protected:
   

private slots:

private:
    void createActions();
};

#endif
