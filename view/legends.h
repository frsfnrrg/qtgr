#ifndef VIEW_LEGENDS_H
#define VIEW_LEGENDS_H

#include <QtGui>
#include "dialog.h"

class ViewLegends : public Dialog
{
    Q_OBJECT
public:
    explicit ViewLegends(MainWindow* mainWin);
    QLineEdit* legendX;
    QLineEdit* legendY;

private:
    QComboBox* locType;
    QCheckBox* showLegend;
    QDialog* legendsEditDialog;

    // 30=MAXPLOT from core/defines.h; including it blows stuff up
    QLineEdit* setLabels[30];
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
