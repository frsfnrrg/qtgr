#ifndef MENUFILE_H
#define MENUFILE_H

#include "menu.h"

class FileOpenSet;
class QFileDialog;

class FileMenu : public Menu
{
    Q_OBJECT

public:
    FileMenu(MainWindow* );

    void populateMenu(QMenu*);

public slots:
    void open_file();
    void read_set();
    void open_param();
    void open_block();

    void write_set();
    void write_param();
    void save();
    void save_as();


    void reset();
    void print();
    void export_file();

protected:
    void populateToolBar(QToolBar*);

private:
    void createActions();
    QAction *openAct;
    QAction *readSetAct;
    QAction *readParaAct;
    QAction *readBlockAct;
    QAction *writeSetAct;
    QAction *writeParaAct;
    QAction *saveAsAct;
    QAction *saveAct;
    QAction *resetAct;
    QAction *printAct;
    QAction *exportAct;
    QAction *exitAct;

    FileOpenSet* opensetDialog;
    QFileDialog* exportDialog;
    QFileDialog* saveallDialog;
};

#endif
