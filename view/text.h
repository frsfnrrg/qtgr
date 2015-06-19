#ifndef TEXT_H
#define TEXT_H

#include "dialog.h"
#include "base/defines.h"

#include <QFrame>

class QScrollArea;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;

class ViewTextElement;
class ViewTextProperties;

class ViewText : public Dialog
{
    Q_OBJECT
public:
    explicit ViewText(MainWindow* mainWin);

    void addText(int id, float x, float y);

    void relocateText(int id);
    void setText(int id, float x, float y);

    void deleteText(int id);

    void scrollToField(int num);

    void loadTextProperties(int num);
private:
    QPushButton* placeTextButton;

    ViewTextElement* texts[MAXSTR];

    QVBoxLayout* textsLayout;

    QScrollArea* scrollBox;

    ViewTextProperties* propsDialog;

public slots:
    void updateDialog();

private slots:
    void applyDialog();

    void placeText();
};

class ViewTextElement : public QFrame
{
    Q_OBJECT
public:
    explicit ViewTextElement(ViewText* parent, int id);
    ~ViewTextElement();

    void setLocation(double x, double y, bool focus=false);

    void applyValues();
    void updateValues();

    int num;
private:
    DoubleSpinBox* xCoord;
    DoubleSpinBox* yCoord;

    QPushButton* relocateButton;
    QPushButton* moreButton;
    QPushButton* deleteButton;

    QHBoxLayout* layout;
    QGridLayout* rlayout;

    LongTextEdit* textArea;

    ViewText* par;

    QLabel* xLabel;
    QLabel* yLabel;

private slots:
    void reloc();
    void del();
    void prop();
};

class ViewTextProperties : public Dialog
{
    Q_OBJECT
public:
    explicit ViewTextProperties(MainWindow* mainWin);

    void addItem(int id);
    void setItem(int loc);
    void removeItem(int loc);
private:
    QComboBox* tNum;

    QComboBox* tFont;
    QComboBox* tColor;
    DoubleRangeSelector* tSize;

    QComboBox* tJust;
    IntegerRangeSelector* tAngle;

    QGroupBox* tSet;

    QPushButton* tApplyTextStyle;

    int getID();

public slots:
    void updateDialog();

private slots:
    void applyDialog();

    void spreadTextStyle();
};
#endif // TEXT_H
