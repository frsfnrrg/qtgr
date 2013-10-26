#ifndef AXIS_H
#define AXIS_H

#include <QtGui>
#include "dialog.h"

class ViewAxisText;
class ViewAxisTicks;

class ViewAxis : public Dialog
{
    Q_OBJECT
public:
    explicit ViewAxis(MainWindow*);

    QComboBox* editAxis;

private:

    QLineEdit* axisLabel;

    QLabel* uMinLabel;
    QLabel* uMaxLabel;

    QLineEdit* uMin;
    QLineEdit* uMax;
    QLineEdit* majTic;
    QLineEdit* minTic;
    QCheckBox* startOpt;
    QLineEdit* uStart;
    QCheckBox* stopOpt;
    QLineEdit* uStop;

    QPushButton* loadDimensionsDialog;

    QComboBox* labelFormat;
    QComboBox* labelPrecision;
    IntegerSpinBox* labelSkip;

    QLabel* labelFormatLabel;
    QLabel* labelPrecisionLabel;
    QLabel* labelSkipLabel;

    QComboBox* textSide;
    QPushButton* textProps;
    ViewAxisText* textDialog;

    QComboBox* tickSide;
    QPushButton* tickProps;
    ViewAxisTicks* tickDialog;
    
public slots:
    void updateDialog();

    void updateWorldDimensions(QObject*);

private slots:
    void applyDialog();


    void loadText();
    void loadTicks();

    void fadeText();

    void fadeMinTick();
    void fadeMaxTick();
};

class ViewAxisText : public Dialog {
    Q_OBJECT
public:
    explicit ViewAxisText(MainWindow*);

    QComboBox* editAxis;
private:

    QComboBox* tickFont;
    QComboBox* tickColor;
    DoubleSpinBox* tickSize;
    QComboBox* tickLayout;
    IntegerRangeSelector* tickAngle;
    QLabel* tickAngleLabel;
    DoubleRangeSelector* tickSpacing;

    QComboBox* axisFont;
    QComboBox* axisColor;
    DoubleSpinBox* axisSize;
    QComboBox* axisLayout;

public slots:
    void updateDialog();

private slots:
    void applyDialog();

    void fadeAngle();

};

class ViewAxisTicks : public Dialog {
    Q_OBJECT
public:
    explicit ViewAxisTicks(MainWindow*);

    QComboBox* editAxis;
private:
    QPushButton* frameProps;

    QGroupBox* tickBox;
    QComboBox* tickDirection;
    DoubleRangeSelector* tickMajLength;
    DoubleRangeSelector* tickMinLength;
    QLabel* tickDirectionLabel;
    QLabel* tickMajLengthLabel;
    QLabel* tickMinLengthLabel;

    QGroupBox* axisBarBox;
    QComboBox* axisBarWidth;
    QComboBox* axisBarColor;
    QComboBox* axisBarStyle;
    QLabel* axisBarWidthLabel;
    QLabel* axisBarColorLabel;
    QLabel* axisBarStyleLabel;

    QGroupBox* majGridBox;
    QComboBox* majGridWidth;
    QComboBox* majGridColor;
    QComboBox* majGridStyle;
    QLabel* majGridWidthLabel;
    QLabel* majGridColorLabel;
    QLabel* majGridStyleLabel;

    QGroupBox* minGridBox;
    QComboBox* minGridWidth;
    QComboBox* minGridColor;
    QComboBox* minGridStyle;
    QLabel* minGridWidthLabel;
    QLabel* minGridColorLabel;
    QLabel* minGridStyleLabel;

public slots:
    void updateDialog();

private slots:
    void applyDialog();

    void fadeTickBox();
    void fadeAxisBarBox();
    void fadeMajGridBox();
    void fadeMinGridBox();
};

#endif // AXIS_H
