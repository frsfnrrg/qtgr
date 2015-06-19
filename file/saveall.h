#ifndef SAVEALL_H
#define SAVEALL_H

#include <QFileDialog>

class MainWindow;

class FileSaveAll : public QFileDialog
{
    Q_OBJECT
public:
    explicit FileSaveAll(MainWindow *mwin);
    MainWindow* mainWindow;

public slots:
    void accept();
};

#endif // SAVEALL_H
