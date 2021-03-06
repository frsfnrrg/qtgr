#ifndef MENU_H
#define MENU_H

#include <QMenu>

class QAction;
class QToolBar;
class MainWindow;
class Dialog;

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

    QToolBar* createToolBar(bool show=false);

protected:
    // is this the problem
    QAction* makeAction(const char* name, const char* desc, const char* shortcut,
              const char* slot);
    virtual void populateToolBar(QToolBar*);
signals:
    
public slots:
    
};

#endif // MENU_H
