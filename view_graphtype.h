#ifndef VIEW_GRAPHTYPE_H
#define VIEW_GRAPHTYPE_H

#include <QtGui>
#include "mainwindow.h"
#include "dialog.h"

// Hey... you could subclass QDialog, have reqed. apply, done, update, cancel
class ViewGraphType : public Dialog
{
    Q_OBJECT
public:
    explicit ViewGraphType(MainWindow* mainWin);
private:
    QComboBox* setNumbers;
    QComboBox* graphTypes;

signals:
    
public slots:
    void updateDialog();

private slots:
    void applyDialog();
};

#endif // VIEW_GRAPHTYPE_H
