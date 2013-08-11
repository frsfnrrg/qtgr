#ifndef SAVEAS_H
#define SAVEAS_H

#include <QtGui>
#include "mainwindow.h"

class FileExport : public QFileDialog
{
    Q_OBJECT
public:
    explicit FileExport(MainWindow *mwin);
    MainWindow* mainWindow;

private:
    QFrame* options;
    QSpinBox* heightBox;
    QSpinBox* widthBox;
public slots:
    void accept();
};

#endif // SAVEAS_H
