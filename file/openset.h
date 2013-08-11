#ifndef OPENSET_H
#define OPENSET_H

#include <QtGui>
#include "mainwindow.h"

class FileOpenSet : public QFileDialog
{
    Q_OBJECT
public:
    explicit FileOpenSet(MainWindow *mwin);
    MainWindow* mainWindow;
private:
    QComboBox* fileType;
    QComboBox* graphNum;
    QRadioButton* fromFile;
    QRadioButton* fromPipe;

public slots:
    void accept();
};

#endif // OPENSET_H
