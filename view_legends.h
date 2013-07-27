#ifndef VIEW_LEGENDS_H
#define VIEW_LEGENDS_H

#include <QtGui>
#include "mainwindow.h"

class ViewLegends : public QDialog
{
    Q_OBJECT
public:
    static const int maxsets = 16; // FIXME

    explicit ViewLegends(MainWindow* mainWin);
    MainWindow* mainWindow;
    QLineEdit* legendX;
    QLineEdit* legendY;

private:

    QComboBox* locType;
    QCheckBox* showLegend;
    QDialog* legendsEditDialog;

    QLineEdit* setLabels[ViewLegends::maxsets];
signals:
    
public slots:
    void updateDialog();
    void applyDialog();

private slots:
    void doneDialog();
    void cancelDialog();

    void placeLegends();
    void legendsEdit();
    void updateLegendsEdit();
    void applyLegendsEdit();
    void doneLegendsEdit();
};

#endif // VIEW_LEGENDS_H
