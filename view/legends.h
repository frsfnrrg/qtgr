#ifndef VIEW_LEGENDS_H
#define VIEW_LEGENDS_H

#include <QtGui>
#include "dialog.h"
#include "base/globals.h"

class ViewLegendsEdit;
class ViewLegendsFrame;

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

    QComboBox* styleFont;
    QComboBox* styleColor;
    DoubleSpinBox* styleSize;
    QComboBox* styleWidth;
    QComboBox* styleSpacing;
    QComboBox* styleFrame;

    ViewLegendsEdit* legendsEditDialog;
    ViewLegendsFrame* legendsFrameDialog;
signals:

public slots:
    void updateDialog();
    void applyDialog();

private slots:
    void placeLegends();
    void legendsEdit();
    void legendsFrame();
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

class ViewLegendsFrame : public Dialog
{
    Q_OBJECT
public:
    explicit ViewLegendsFrame(MainWindow* mainWin);

private:
    QComboBox* frameColor;
    QComboBox* frameWidth;
    QComboBox* frameStyle;
    QCheckBox* frameFill;
    QComboBox* frameFillColor;
    QComboBox* frameFillPattern;
    QLabel* frameFillColorLabel;
    QLabel* frameFillPatternLabel;

signals:

public slots:
    void resetFill();
    void updateDialog();
    void applyDialog();

private slots:
};



#endif // VIEW_LEGENDS_H
