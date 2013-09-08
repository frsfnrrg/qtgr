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

public slots:
    void updateDialog();

private slots:
    void applyDialog();

};

class ViewAxisTicks : public Dialog {
    Q_OBJECT
public:
    explicit ViewAxisTicks(MainWindow*);

    QComboBox* editAxis;
private:

public slots:
    void updateDialog();

private slots:
    void applyDialog();

};

#endif // AXIS_H
