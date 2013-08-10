#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui>
#include "mainwindow.h"
#include "util.h"

// TODO: wrap in a legend list generator, that hooks things up well.
// Or, subclass again!
class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(MainWindow* mainWin, const char* title);
    MainWindow* mainWindow;

    void setDialogLayout(QLayout* layout);
// we could abstract these out, so only the main pane
// gets changed

protected:
    QLabel* makeLabel(const char* text, Qt::Alignment align = Qt::AlignCenter);

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
