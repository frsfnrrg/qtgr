#ifndef LEGEND_H
#define LEGEND_H

#include <QtGui>
#include "dialog.h"

#define MAXPLOT 30

class ViewLegendProp;

class ViewLegend : public Dialog
{
    Q_OBJECT
public:
    explicit ViewLegend(MainWindow* mwin);

    void applyLegendPos(double, double);

    void updateLegendsField(int);
public slots:
    void updateSets();

private:
    QComboBox* locType;

    QPushButton* placer;
    QPushButton* prop;

    QLineEdit* legendX;
    QLineEdit* legendY;

    QCheckBox* showLegend;

    ViewLegendProp* propDialog;

    QLineEdit* setLabels[MAXPLOT];
    QLabel* setLabelLabels[MAXPLOT];
private slots:
    void updateDialog();
    void applyDialog();

    void placeLegend();
    void legendProp();
};


class ViewLegendProp : public Dialog
{
    Q_OBJECT
public:
    explicit ViewLegendProp(MainWindow* mwin);

private:
    QGroupBox* style;
    QComboBox* styleFont;
    QComboBox* styleColor;
    DoubleSpinBox* styleSize;
    QComboBox* styleWidth;
    QComboBox* styleSpacing;

    QGroupBox* frame;
    QComboBox* frameColor;
    QComboBox* frameWidth;
    QComboBox* frameStyle;
    QCheckBox* frameFill;
    QComboBox* frameFillColor;
    QComboBox* frameFillPattern;
    QLabel* frameFillColorLabel;
    QLabel* frameFillPatternLabel;

private slots:
    void updateDialog();
    void applyDialog();
    void resetFill();

};

#endif // LEGEND_H
