#ifndef VIEW_LEGENDS_H
#define VIEW_LEGENDS_H

#include <QtGui>
#include "mainwindow.h"
#include "dialog.h"

class ViewLegends : public Dialog
{
    Q_OBJECT
public:
    static const int maxsets = 16; // FIXME

    explicit ViewLegends(MainWindow* mainWin);
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
    void placeLegends();
    void legendsEdit();
    void updateLegendsEdit();
    void applyLegendsEdit();
    void doneLegendsEdit();
};

#endif // VIEW_LEGENDS_H
