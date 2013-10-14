#ifndef CHOOSERS_H
#define CHOOSERS_H

#include <QtGui>

class DoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit DoubleSpinBox();
public slots:
    void setValue(double, bool loud=false);
};

class IntegerSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    explicit IntegerSpinBox();
public slots:
    void setValue(int, bool loud=false);
};

class LongTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit LongTextEdit();
public slots:
    void setText(const QString &text, bool loud=false);
};

class Slider : public QSlider
{
    Q_OBJECT
public:
    explicit Slider(Qt::Orientation orient = Qt::Horizontal);
public slots:
    void setValue(int, bool loud=false);
};

/*
 * Select a font
 */
class FontComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit FontComboBox();

    QFont getCurrentFont();

    static QFont getFont(int index);

    static void initializeFonts();
private:
    static int serif;
    static int sans;
    static int mono;
};

/*
 * Select a set
 */
class SetComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit SetComboBox(bool and_all_active = false);

public slots:
    void updateSets();

private:
    int add;
};

/*
 * Select a fill pattern
 */
class PatternComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit PatternComboBox();

    static QPixmap getPattern(int index);
    static void initializePatterns();

private:
    static QPixmap* pxs[];
};

/*
 * Select a color
 */
class ColorComboBox : public QComboBox
{
  Q_OBJECT
public:
    explicit ColorComboBox();

    static QColor getColor(int index);
};

DoubleSpinBox* makeTextSizer();

QComboBox* makeWidthSelector();

QComboBox* makeLineStyler();

class IntegerRangeSelector : public QWidget
{
    Q_OBJECT
public:
    IntegerRangeSelector(int min, int max, int step);
    int value();
signals:
    void userChangedValue(int);
public slots:
    void setValue(int v);
    void setEnabled(bool);
    void setDisabled(bool);
private slots:
    void sliderValueUpdated(int);
    void boxValueUpdated(int);
private:
    Slider* slider;
    IntegerSpinBox* box;
};

class DoubleRangeSelector : public QWidget
{
    Q_OBJECT
public:
    // note: positive values are assumed
    DoubleRangeSelector(double min, double max, int prec, double step);
    double value();
signals:
    void userChangedValue(double);
public slots:
    void setValue(double v);
    void setEnabled(bool);
    void setDisabled(bool);
private slots:
    void sliderValueUpdated(int);
    void boxValueUpdated(double);
private:
    Slider* slider;
    DoubleSpinBox* box;
    double scale;
    double invscale;
};

DoubleSpinBox* getUnitDoubleSpinBox();

#endif // CHOOSERS_H
