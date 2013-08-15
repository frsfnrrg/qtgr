#ifndef CHOOSERS_H
#define CHOOSERS_H

#include <QtGui>

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

QDoubleSpinBox* makeTextSizer();

QComboBox* makeWidthSelector();

QComboBox* makeLineStyler();

#endif // CHOOSERS_H
