#ifndef VIEW_LEGENDS_H
#define VIEW_LEGENDS_H

#include <QtGui>
#include "dialog.h"
#include "base/globals.h"

class ViewLegends : public Dialog
{
    Q_OBJECT
public:
    explicit ViewLegends(MainWindow* mainWin);
    QLineEdit* legendX;
    QLineEdit* legendY;
    void updateLegendsField(int cset);

private:
    QComboBox* locType;
    QCheckBox* showLegend;
    QDialog* legendsEditDialog;

    QLineEdit* setLabels[MAXPLOT];
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
