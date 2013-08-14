#ifndef MENUVIEWTICKS_H
#define MENUVIEWTICKS_H

#include <QtGui>
#include "dialog.h"

class ViewTicksLabels;
class ViewTicksMarks;
class ViewTicksBar;
class ViewTicksAxisLabel;
class ViewTicksMajGrid;
class ViewTicksMinGrid;

class ViewTicks : public Dialog
{
  Q_OBJECT
  
  public:	
    ViewTicks(MainWindow* mainWin);
    
    QComboBox* editAxis;

    ViewTicksLabels* labelPropsDialog;
    ViewTicksAxisLabel* axisLabelDialog;
    ViewTicksMarks* ticksDialog;
    ViewTicksBar* barDialog;
    ViewTicksMajGrid* majDialog;
    ViewTicksMinGrid* minDialog;

  public slots:
    void updateDialog();
    void updateWorldDimensions();
    
  private:
    
    QLineEdit *axisLabel;
    QLineEdit *majTic;
    QLineEdit *minTic;  
    
    QCheckBox* majGrid;
    QCheckBox* minGrid;

    QCheckBox* tickLabels;
    QCheckBox* tickMarks;
    QCheckBox* axisBar;

    QLabel* axisName;
    
 private slots:
    void forceMaj();
    void applyDialog();

    void labelProps();
    void axisLabelProps();
    void ticks();
    void bar();
    void majGridProps();
    void minGridProps();
};

class ViewTicksLabels : public Dialog {
    Q_OBJECT
public:
    ViewTicksLabels(MainWindow* mainWin);
    QComboBox* editAxis;

public slots:
    void updateDialog();

private slots:
    void applyDialog();

    void resetStart();
    void resetStop();
    void resetLayout();
    void updateAngle();

private:
    QComboBox* labelFormat;
    QComboBox* labelPrecision;

    QComboBox* textFont;
    QComboBox* textColor;
    QDoubleSpinBox* textSize;

    QSpinBox* stagger;
    QSpinBox* skipEvery;

    QComboBox* startType;
    QComboBox* stopType;
    QComboBox* layoutType;

    QLabel* editStartLabel;
    QLabel* editStopLabel;
    QLineEdit *editStartAt;
    QLineEdit *editStopAt;

    QSlider* layoutAngle;
    QLabel* layoutAngleLabel;

    QComboBox* drawSide;
};

class ViewTicksAxisLabel : public Dialog {
    Q_OBJECT
public:
    ViewTicksAxisLabel(MainWindow* mainWin);
    QComboBox* editAxis;

public slots:
    void updateDialog();

private slots:
    void applyDialog();

private:
    QComboBox* direction;
    QComboBox* textFont;
    QComboBox* textColor;
    QDoubleSpinBox* textSize;
};

class ViewTicksMarks : public Dialog {
    Q_OBJECT
public:
    ViewTicksMarks(MainWindow* mainWin);
    QComboBox* editAxis;

public slots:
    void updateDialog();

private slots:
    void updateMaj();
    void updateMin();
    void applyDialog();

private:
    QComboBox* direction;
    QComboBox* location;
    QSlider* majLength;
    QSlider* minLength;
    QLabel* majReadout;
    QLabel* minReadout;
};

class LineStyleDialog : public Dialog {
    Q_OBJECT
public:
    LineStyleDialog(MainWindow* mainWin, const char* title);
    QComboBox* editAxis;
protected:
    QComboBox* widthB;
    QComboBox* colorB;
    QComboBox* styleB;
};

class ViewTicksBar : public LineStyleDialog {
    Q_OBJECT
public:
    ViewTicksBar(MainWindow* mainWin);

public slots:
    void updateDialog();

private slots:
    void applyDialog();
};

class ViewTicksMajGrid : public LineStyleDialog {
    Q_OBJECT
public:
    ViewTicksMajGrid(MainWindow* mainWin);

public slots:
    void updateDialog();

private slots:
    void applyDialog();
};

class ViewTicksMinGrid : public LineStyleDialog {
    Q_OBJECT
public:
    ViewTicksMinGrid(MainWindow* mainWin);

public slots:
    void updateDialog();

private slots:
    void applyDialog();
};



#endif
