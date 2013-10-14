#ifndef TEXT_H
#define TEXT_H

#include "dialog.h"
#include "base/defines.h"

class ViewTextElement;

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
private:
    QPushButton* placeTextButton;

    ViewTextElement* texts[MAXSTR];

    QVBoxLayout* textsLayout;

    QScrollArea* scrollBox;

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
    int num;

    QLabel* xLabel;
    QLabel* yLabel;

private slots:
    void reloc();
    void del();
};

#endif // TEXT_H
