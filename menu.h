#ifndef MENU_H
#define MENU_H

#include <QtGui>
#include "dialog.h"
#include "util.h"

class Menu : public QMenu
{
    Q_OBJECT
public:
    explicit Menu(MainWindow* mainWin, const char* title, bool tearoff=true);

    MainWindow* mainWindow;

    /**
     * UpdateDialog: pointer passed in may be null
     */
    void updateDialog(Dialog*);

    virtual QToolBar* createToolBar() {return new QToolBar();}
protected:
    // is this the problem
    QAction* makeAction(const char* name, const char* desc, const char* shortcut,
              const char* slot);

signals:
    
public slots:
    
};

#endif // MENU_H
