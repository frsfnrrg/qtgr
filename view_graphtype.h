#ifndef VIEW_GRAPHTYPE_H
#define VIEW_GRAPHTYPE_H

#include <QtGui>
#include "mainwindow.h"

// Hey... you could subclass QDialog, have reqed. apply, done, update, cancel
class ViewGraphType : public QDialog
{
    Q_OBJECT
public:
    ViewGraphType(MainWindow* mainWin);
private:
    MainWindow* mainWindow;
    QComboBox* setNumbers;
    QComboBox* graphTypes;

signals:
    
public slots:
    void updateDialog();

private slots:
    void applyDialog();
    
    void doneDialog();

    void cancelDialog();
};

#endif // VIEW_GRAPHTYPE_H
