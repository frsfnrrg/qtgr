#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui>
#include "mainwindow.h"

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(MainWindow* mainWin);
    MainWindow* mainWindow;

    void setDialogLayout(QLayout* layout);
// we could abstract these out, so only the main pane
// gets changed

private:
    QVBoxLayout* layout;
signals:
    
public slots:
    virtual void updateDialog() = 0;
    virtual void applyDialog() = 0;

private slots:
    void doneDialog();
    void cancelDialog();
};

#endif // DIALOG_H
