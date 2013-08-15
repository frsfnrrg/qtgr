#ifndef VIEW_LEGENDS_H
#define VIEW_LEGENDS_H

#include <QtGui>
#include "dialog.h"
#include "base/globals.h"

class ViewLegendsEdit;

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
    ViewLegendsEdit* legendsEditDialog;
signals:

public slots:
    void updateDialog();
    void applyDialog();

private slots:
    void placeLegends();
    void legendsEdit();
};

class ViewLegendsEdit : public Dialog
{
    Q_OBJECT
public:
    explicit ViewLegendsEdit(MainWindow* mainWin);

    QLineEdit* setLabels[MAXPLOT];
private:

signals:

public slots:
    void updateDialog();
    void applyDialog();

private slots:
};



#endif // VIEW_LEGENDS_H
