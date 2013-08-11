#ifndef MENUFILE_H
#define MENUFILE_H

#include <QtGui>
#include "menu.h"

class FileMenu : public Menu
{
    Q_OBJECT

public:
    FileMenu(MainWindow* );

    void populateMenu(QMenu*);

public slots:
    void open_set();
    void open_param();
    void open_block();

    void write_set();
    void write_param();
    void write_block();

    void reset();
    void print();
    void save_as();

protected:
    void populateToolBar(QToolBar*);

private:
    void createActions();
    QAction *readSetAct;
    QAction *readParaAct;
    QAction *readBlockAct;
    QAction *writeSetAct;
    QAction *writeParaAct;
    QAction *writeBlockAct;
    QAction *resetAct;
    QAction *printAct;
    QAction *exportAct;
    QAction *exitAct;
};

#endif
