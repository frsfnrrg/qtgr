#ifndef LEGEND_H
#define LEGEND_H

#include "dialog.h"

#include <QVector>
#include <QGridLayout>

class ViewLegendProp;

class ViewLegend : public Dialog
{
    Q_OBJECT
public:
    explicit ViewLegend(MainWindow* mwin);
    ~ViewLegend();

    void applyLegendPos(double, double);

    void updateLegendsField(int);
public slots:
    void updateSets();
    void updateDialog();

private:
    QComboBox* locType;

    QWidget* opl;
    QGridLayout* intern;

    QPushButton* placer;
    QPushButton* prop;

    QLineEdit* legendX;
    QLineEdit* legendY;

    QCheckBox* showLegend;

    QLabel* coordsLabel;
    QLabel* xLabel;
    QLabel* yLabel;

    ViewLegendProp* propDialog;

    QVector<QLineEdit*> setLabels;
    QVector<QLabel*> setLabelLabels;
private slots:

    void applyDialog();

    void placeLegend();
    void legendProp();

    void fadeOpts();
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

public slots:
    void updateDialog();

private slots:
    void applyDialog();
    void resetFill();

};

#endif // LEGEND_H
