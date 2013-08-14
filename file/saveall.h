#ifndef SAVEALL_H
#define SAVEALL_H

#include <QtGui>
#include "mainwindow.h"

class FileSaveAll : public QFileDialog
{
public:
    explicit FileSaveAll(MainWindow *mwin);
    MainWindow* mainWindow;
private:

public slots:
    void accept();
};

#endif // SAVEALL_H
